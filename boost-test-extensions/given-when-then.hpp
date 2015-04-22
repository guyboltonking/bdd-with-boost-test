#pragma once

/* Given/When/Then macros for developing BDD-style tests */

#include "detail/given-when-then.hpp"

#define Scenario_(x) GWT_TEST_SUITE(SCENARIO_ ## x)

#define Given_(x) GWT_TEST_SUITE(given_ ## x)
#define When_(x) GWT_TEST_SUITE(when_ ## x)

#define Then_(x) GWT_TEST_CASE(then_ ## x)
#define And_(x) GWT_TEST_CASE(and_ ## x)
