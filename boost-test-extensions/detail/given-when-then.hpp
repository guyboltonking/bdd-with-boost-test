#pragma once

/* Shared support for given-when-then and specs macros */

//=============================================================================
// Shared helpers

#define GWT_TEST_SUITE(test) \
  BOOST_AUTO_TEST_SUITE(test); \
  typedef before_each outer_before_each;

#define GWT_TEST_CASE(test) \
  BOOST_FIXTURE_TEST_CASE(test, before_each)

#define End_ BOOST_AUTO_TEST_SUITE_END()

#define Before_each_(x) struct before_each: outer_before_each { \
   before_each() { x; } \
};

//=============================================================================
// Dummy before_each definition local to each compilation unit.  This allows
// us to write GIVEN_/WHEN_/THEN_ or DESCRIBE_/IT_ without having to specify
// an initial before_each, as well as nesting GIVEN_ as much as we like.
namespace {
   struct before_each {};
}
