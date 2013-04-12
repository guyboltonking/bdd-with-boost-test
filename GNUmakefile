all: run-stack-spec-catch

run-boost-range: boost-range
	./boost-range

run-stack-spec: stack_spec
	./stack_spec --log_level=test_suite

stack_spec: stack_spec.cpp
	g++ -Iboost_1_53_0 -o stack_spec stack_spec.cpp

run-stack-spec-catch: stack_spec_catch
	./stack_spec_catch -s

stack_spec_catch: stack_spec_catch.cpp
	clang++ -std=c++0x -I. -Iboost_1_53_0 -o stack_spec_catch stack_spec_catch.cpp

boost-range: boost-range.cpp
	clang++ -std=c++0x -Iboost_1_53_0 -o boost-range boost-range.cpp
