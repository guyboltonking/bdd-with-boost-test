#pragma once

/* Given/When/Then macros for developing BDD-style tests */

#include "detail/given-when-then.hpp"

#define Scenario_(x) GWT_PREFIXED_FIXTURE_TEST_SUITE(SCENARIO_, x, before_each)

#define Given_(x) GWT_PREFIXED_FIXTURE_TEST_SUITE(given_, x, before_each)
#define When_(x) GWT_PREFIXED_FIXTURE_TEST_SUITE(when_, x, before_each)

#define Then_(x) GWT_PREFIXED_FIXTURE_TEST_CASE(then_, x, before_each)
#define And_(x) GWT_PREFIXED_FIXTURE_TEST_CASE(and_, x, before_each)
