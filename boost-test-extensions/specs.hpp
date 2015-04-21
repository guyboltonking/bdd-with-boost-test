#pragma once

/* Macros to support spec-style tests */

#include "detail/given-when-then.hpp"

#define DESCRIBE_(x) GWT_FIXTURE_TEST_SUITE(x ## _, before_each)
#define IT_(x) BOOST_FIXTURE_TEST_CASE(x, before_each)
