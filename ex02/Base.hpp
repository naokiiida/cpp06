#ifndef BASE_HPP
#define BASE_HPP

class Base {
public:
  virtual ~Base();
  static Base *generate(void);
  static void identify(Base *basePtr);
  static void identify(Base &baseRef);
};
#endif
