#pragma once

/* Macros to support spec-style tests */

#include "detail/given-when-then.hpp"

// The trailing _ after the expansion of x is to allow class names to
// be used without clashing with the actual class name
#define Describe_(x) GWT_TEST_SUITE(x ## _)
#define Context_(x) GWT_TEST_SUITE(x)
#define It_(x) GWT_TEST_CASE(x)
