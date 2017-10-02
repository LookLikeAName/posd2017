#ifndef UTATOM_H
#define UTATOM_H
#include "atom.h"

TEST(Atom, first) {
  ASSERT_TRUE(true);
}

TEST(Atom, tom) {
  Atom tom("tom");
  ASSERT_EQ("tom", tom.symbol());
}

TEST(Atom, match_tom_and_jerry) {
  Atom tom("tom");
  Atom jerry("jerry");
  EXPECT_FALSE(tom.match(jerry));
  EXPECT_TRUE(tom.match(tom));
}

#endif
