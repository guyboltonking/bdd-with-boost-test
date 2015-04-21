#pragma once

/* Given/When/Then macros for developing BDD-style tests */

#include "detail/given-when-then.hpp"

#define SCENARIO_(x) GWT_PREFIXED_FIXTURE_TEST_SUITE(SCENARIO_, x, before_each)

#define GIVEN_(x) GWT_PREFIXED_FIXTURE_TEST_SUITE(given_, x, before_each)
#define WHEN_(x) GWT_PREFIXED_FIXTURE_TEST_SUITE(when_, x, before_each)

#define THEN_(x) GWT_PREFIXED_FIXTURE_TEST_CASE(then_, x, before_each)
#define AND_(x) GWT_PREFIXED_FIXTURE_TEST_CASE(and_, x, before_each)
