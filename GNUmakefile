all: run-stack-spec-boost

run-stack-spec-boost: stack-spec-boost
	./stack-spec-boost --log_level=test_suite

stack-spec-boost: stack-spec-boost.cpp
	g++ -std=c++11 -Iboost_1_58_0 -o stack-spec-boost $^
