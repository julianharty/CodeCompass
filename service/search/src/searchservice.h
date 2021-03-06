#ifndef SEARCHSERVICE_H
#define SEARCHSERVICE_H

#include <cstdio>
#include <memory>
#include <functional>
#include <mutex>
#include <odb/database.hxx>

#include "search-api/SearchService.h"
#include "core-api/result_types.h"

#include <model/file.h>

#include <boost/regex.hpp>
#include <boost/program_options/variables_map.hpp>

#include "serviceprocess.h"

namespace cc
{
namespace service
{
namespace search
{

class SearchServiceHandler : virtual public SearchServiceIf {
public:
  /**
   * @param db_ a database instance.
   * @param config_ command line parameters
   */
  SearchServiceHandler(
    std::shared_ptr<odb::database> db_,
    const boost::program_options::variables_map& config_
      = boost::program_options::variables_map());

  void search(
    core::SearchResult& _return,
    const SearchParams& params_) override;

  void searchFile(
    core::FileSearchResult& _return,
    const SearchParams&     params_);

  void getSearchTypes(std::vector<SearchType> & _return) override;

  void pleaseStop() override;

  void suggest(SearchSuggestions& _return,
    const SearchSuggestionParams& params_) override;

private:
  /**
   * Validates a regluar expression. If the expression is invalid then a thrift
   * excepion is thrown.
   *
   * @param regexp_ a regluar expression to validate.
   */
  static void validateRegexp(const std::string& regexp_);

  std::shared_ptr<odb::database> _db;

  std::unique_ptr<ServiceProcess> _javaProcess;
  std::mutex _javaProcessMutex;
};

} // search
} // service
} // cc


#endif


