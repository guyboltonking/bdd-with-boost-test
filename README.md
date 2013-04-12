An example used in a lightning talk at ACCU 2013.

To run the C++ examples you'll need Boost 1.53, unzipped into the same
directory, and catch.hpp.

To run all the examples, run make.  The files are:

* stack_spec.rb: a simple RSpec test 
* stack_spec.cpp: an attempt to use
  Boost Test to build up a specification in an RSpec-style.
* stack_spec_catch.cpp: the right way to do it, using Phil Nash's
  catch framework.
