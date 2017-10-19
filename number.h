#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "term.h"
using std::string;

class Number : public Term{
public:
    Number (double);
    string symbol() const;
    string value() const;
    bool match (Term &);
private:
    double _value;
};


#endif
