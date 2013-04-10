all: stack_spec
	./stack_spec --log_level=test_suite

stack_spec: stack_spec.cpp
	g++ -Iboost_1_53_0 -o stack_spec stack_spec.cpp
