#include <iostream>
#include <new>
// virtual inheritance

class Creature {
public:
  int life;
  virtual void eat();
};

// Two classes virtually inheriting Creature:
class Mammal : public virtual Creature {
public:
  virtual void breathe();
};

class WingedCreature : public virtual Creature {
public:
  virtual void flap();
};

// Inherited from classes with the same base
class Bat : public Mammal, public WingedCreature {
public:
  int simaInt;
private:
  const static int staticInt = 0;
};

// function pointers

class Animal
{
public:

  typedef Animal*(*NewAnimalFunction)(void);

  virtual void makeNoise()
  {
    std::cout << "M00f!" << std::endl;
  }
};

class Dog : public Animal
{
public:

  typedef void(Dog::*BarkFunction)(void);

  typedef Dog*(*NewDogFunction)(void);

  Dog () {}

  static Dog* newDog()
  {
    return new Dog;
  }

  virtual void makeNoise ()
  {
    std::cout << "Woof!" << std::endl;
  }
};

// new operator

struct A { // struct without overloaded new operator

};
struct X { // struct with overloaded new operator
  static void* operator new(std::size_t sz)
  {
    std::cout << "custom new for size " << sz << '\n';
    return ::operator new(sz);
  }
  static void* operator new[](std::size_t sz)
  {
    std::cout << "custom new for size " << sz << '\n';
    return ::operator new(sz);
  }
};

int main(int argc, char* argv[])
{
  // new operator

  A* a = new A;
  int* alma = new int(5);
  X* p1 = new X;
  delete p1;
  X* p2 = new X[10];
  delete[] p2;

  // Call member function via method pointer
  Dog* pDog = new Dog ();
  Dog::BarkFunction pBark = &Dog::makeNoise;

  (pDog->*pBark)();

  // Construct instance via factory method
  Dog::NewDogFunction pNew = &Dog::newDog;

  Animal* pAnimal = (*pNew)();

  pAnimal->makeNoise();

  Dog::NewDogFunction newFuncPointer = *pNew;

  return 0;
}

// declaration here
int someIntFunction(int fst, std::string snd);

// definition here
int someIntFunction(int fst, std::string snd)
{
  // calculate now
  int result = 2 + fst;
  return result;
}

// lambda

void someOtherFunction()
{
  auto factorial = [](int i, int j) {return i * j;};

  typedef int (*func)();
  func f = [] () -> int { return 2; };
  f();

}

class Bird : public WingedCreature 
{
  public:
    int wing;
    int tweet(){}
    virtual void eat() override{}
};

void virtualCallTest()
{
  Bird b;
  b.eat();
  Creature * c = &b;
  c -> eat();
}

void polymorphicCallTest(Animal* animal)
{
  animal->makeNoise();
}

struct VA
{
  virtual void f() { std::cout << "VA::f()" << std::endl; }
};

struct VB : VA
{
  void f() { std::cout << "VB::f()" << std::endl; }
};

void getDefinitionVirtualCallTest()
{
  VB b;
  VA& a = b;
  a.f(); 
  
  VA aa = b;
  aa.f(); 
  
  VA *va = new VA();
  va->f();
  
  b.f();    
}
