An example used in a lightning talk at ACCU 2013.

To run the C++ examples you'll need Boost 1.57, unzipped into the same
directory, and catch.hpp.

To run the ruby example you'll need a recent version of ruby.

To run all the examples, run make.  The files are:

* stack_spec.rb: a simple RSpec test
* stack_spec.cpp: uses boost-test-extensions/spec.hpp to do the same
* stack_spec_catch.cpp: a comparison using the Catch framework.
