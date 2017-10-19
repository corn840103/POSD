#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include "term.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class Struct:public Term{
public:
  Struct(Atom const &,vector<Term*>);
  Atom const & name();
  Term * args(int) const;
  string symbol() const;
  string value() const;
  int size() const;
  bool match(Term&);
private:
  Atom _name;
  vector<Term *> _args;
};

#endif
