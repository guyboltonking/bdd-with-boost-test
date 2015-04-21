all: \
	run-stack-spec-catch \
	run-stack-spec-rspec \
	run-stack-spec

run-stack-spec-rspec:
	bundle install
	bundle exec rspec --format doc --color stack_spec.rb

run-stack-spec: stack_spec
	./stack_spec --log_level=test_suite

stack_spec: stack_spec.cpp
	g++ -Iboost_1_53_0 -o stack_spec stack_spec.cpp

run-stack-spec-catch: stack_spec_catch
	./stack_spec_catch -s

stack_spec_catch: stack_spec_catch.cpp
	clang++ -std=c++0x -I. -Iboost_1_53_0 -o stack_spec_catch stack_spec_catch.cpp
