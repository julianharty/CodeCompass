#ifndef MODEL_METRICS_H_
#define MODEL_METRICS_H_

#include <string>

#include <odb/core.hxx>
#include <odb/lazy-ptr.hxx>
#include <odb/nullable.hxx>

#include <model/file.h>

namespace cc
{
namespace model
{

#pragma db object
struct Metrics
{
  enum Type
  {
    ORIGINAL_LOC = 1,
    NONBLANK_LOC = 2,
    CODE_LOC = 3,
    MCCABE = 4
  };

  #pragma db id auto
  uint64_t id;

  #pragma db not_null
  FileId file;
  
//  #pragma db not_null
//  std::string nodeid;

//  #pragma db not_null
//  bool isFileId;

  #pragma db not_null
  unsigned metric;
  
  #pragma db not_null
  Type type;

  friend class odb::access;
};

#pragma db view object(Metrics)
struct MetricsCount
{
  #pragma db column("count(" + Metrics::id + ")")
  std::size_t count;
};

} //model
} //cc
#endif
