#include "number.h"
#include "variable.h"
#include "struct.h"
#include <sstream>
#include <iostream>
using std::stringstream;

Number::Number(double value):_value(value) {}

string Number::symbol() const { return value(); }
string Number::value() const {
   stringstream ss;
   ss << _value;
   return ss.str();
}

bool Number::match(Term & term) {
    if (dynamic_cast<Variable*>(&term) ||
        dynamic_cast<Struct*>(&term)) {
        return term.match(*this);
    }
    return value() == term.value();
}
