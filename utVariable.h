#ifndef UTVARIABLE_H
#define UTVARIABLE_H

#include "variable.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include <iostream>
using std::cout;

TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X.symbol());
}

TEST(Variable , matching){
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ( "tom", X.value());
}

TEST (Variable , haveValue){
  Atom tom ("tom");
  Atom jerry ("jerry");
  Variable X("X");
  tom.match(X);
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
  Variable X("X");
  Number E(2.7182);
  X.match(E);
  ASSERT_EQ("2.7182",X.value());
}

// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
  Variable X("X");
  Variable Y("Y");
  Number E(1);
  X.match(Y);
  X.match(E);
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1",Y.value());
}

// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
  Variable X("X");
  Variable Y("Y");
  Number E(1);
  X.match(Y);
  Y.match(E);
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1",X.value());
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
  Variable X("X");
  Number E(1);
  X.match(X);
  X.match(E);
  ASSERT_EQ("1",X.value());
}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
  Variable Y("Y");
  Variable X("X");
  Number E(1);
  ASSERT_TRUE(Y.match(E));
  ASSERT_TRUE(X.match(Y));
  ASSERT_TRUE(X.match(E));
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  Number E(1);
  ASSERT_TRUE(X.match(Y));
  ASSERT_TRUE(Y.match(Z));
  ASSERT_TRUE(Z.match(E));
  ASSERT_EQ("1",X.value());
  ASSERT_EQ("1",Y.value());
  ASSERT_EQ("1",Z.value());
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  Number E(1);
  X.match(Y);
  X.match(Z);
  Z.match(E);
  ASSERT_EQ("1",X.value());
  ASSERT_EQ("1",X.value());
  ASSERT_EQ("1",X.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {
  Variable X("X");
  std::vector<Term *> v ={&X};
  Struct s(Atom("s"), v);
  Variable Y("Y");
  Y.match(s);
  ASSERT_EQ("Y",Y.symbol());
  ASSERT_EQ("s(X)",Y.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
  Variable X("X");
  Variable Y("Y");
  Atom teddy("teddy");
  X.match(teddy);
  std::vector<Term *> v ={&X};
  Struct s(Atom("s"), v);
  Y.match(s);
  ASSERT_EQ("Y", Y.symbol());
  ASSERT_EQ("s(teddy)",Y.value());
}

#endif
