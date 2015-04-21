#pragma once

/* Macros to support spec-style tests */

#include "detail/given-when-then.hpp"

// The trailing _ after the expansion of x is to allow class names to
// be used without clashing with the actual class name
#define DESCRIBE_(x) GWT_FIXTURE_TEST_SUITE(x ## _, before_each)
#define CONTEXT_(x) GWT_FIXTURE_TEST_SUITE(x, before_each)
#define IT_(x) BOOST_FIXTURE_TEST_CASE(x, before_each)
