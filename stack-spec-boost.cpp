#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/included/unit_test.hpp>

#include "boost-test-extensions/spec-logger.hpp"

bool init_unit_test()
{
  boost_test_extensions::SpecLogFormatter::Register();
  return true;
}

//=============================================================================

#include "stack.hpp"

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(Raw_boost_test_example)

struct a_stack_ {
  Stack<int> stack;
};

BOOST_FIXTURE_TEST_SUITE(a_stack, a_stack_)
  BOOST_AUTO_TEST_SUITE(when_initialised)
    BOOST_AUTO_TEST_CASE(should_be_empty)
    {
      BOOST_CHECK(stack.empty());
    }
  BOOST_AUTO_TEST_SUITE_END()

  BOOST_AUTO_TEST_SUITE(pop)

    struct on_an_empty_stack_: a_stack_ {
      on_an_empty_stack_() {
        BOOST_REQUIRE(stack.empty());
      }
    };

    BOOST_FIXTURE_TEST_SUITE(on_an_empty_stack, on_an_empty_stack_)
      BOOST_AUTO_TEST_CASE(should_have_no_effect)
      {
        stack.pop();
        BOOST_CHECK(stack.empty());
      }
    BOOST_AUTO_TEST_SUITE_END()

    struct on_a_stack_with_a_single_member_: a_stack_ {
      on_a_stack_with_a_single_member_() {
        stack.push(1);
        BOOST_REQUIRE_EQUAL(stack.size(), 1);
      }
    };

    BOOST_FIXTURE_TEST_SUITE(on_a_stack_with_a_single_member, 
                             on_a_stack_with_a_single_member_)
      BOOST_AUTO_TEST_CASE(should_result_in_an_empty_stack)
      {
        stack.pop();
        BOOST_CHECK(stack.empty());
      }

      BOOST_AUTO_TEST_CASE(should_reduce_the_stack_size_by_one)
      {
        std::size_t orig_size = stack.size();
        stack.pop();
        BOOST_CHECK_EQUAL(stack.size(), orig_size - 1);
      }
    BOOST_AUTO_TEST_SUITE_END()
  BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

//-----------------------------------------------------------------------------

#include "boost-test-extensions/specs.hpp"

BOOST_AUTO_TEST_SUITE(Specs_boost_test_example)

  DESCRIBE_(Stack)
    struct before_each {
      Stack<int> stack;
    };

    CONTEXT_(after_initialization)
      IT_(is_empty)
      {
        BOOST_CHECK(stack.empty());
      }
    END_
  
    DESCRIBE_(pop)

      CONTEXT_(on_an_empty_stack)
        BEFORE_EACH_(
          BOOST_REQUIRE(stack.empty())
        )
        IT_(has_no_effect)
        {
          stack.pop();
          BOOST_CHECK(stack.empty());
        }
      END_

      CONTEXT_(on_a_stack_with_a_single_member)
        BEFORE_EACH_(
          stack.push(1);
          BOOST_REQUIRE_EQUAL(stack.size(), 1);
        )
        IT_(gives_an_empty_stack)
        {
          stack.pop();
          BOOST_CHECK(stack.empty());
        }
        IT_(reduces_the_stack_size_by_1)
        {
          std::size_t orig_size = stack.size();
          stack.pop();
          BOOST_CHECK_EQUAL(stack.size(), orig_size - 1);
        }
      END_
    END_
  END_

BOOST_AUTO_TEST_SUITE_END()

//-----------------------------------------------------------------------------

#include "boost-test-extensions/given-when-then.hpp"

BOOST_AUTO_TEST_SUITE(BDD_boost_test_example)

  struct before_each {
    Stack<int> stack;
  };

  SCENARIO_(popping_an_empty_stack)

    GIVEN_(an_empty_stack)
      BEFORE_EACH_(BOOST_REQUIRE(stack.empty()))

      WHEN_(the_stack_is_popped)
        BEFORE_EACH_(stack.pop())
        THEN_(the_stack_remains_empty)
        {
          BOOST_CHECK(stack.empty());
        }
      END_
    END_

  END_

  SCENARIO_(popping_a_non_empty_stack)

    GIVEN_(a_stack_with_one_member)
      BEFORE_EACH_(stack.push(1))
      
      WHEN_(the_stack_is_popped)
        struct before_each: outer_before_each {
          std::size_t size_before_pop;
          before_each(): size_before_pop(stack.size()) {
            stack.pop();
          }
        };
        THEN_(the_stack_becomes_empty)
        {
          BOOST_CHECK(stack.empty());
        }
        AND_(the_stack_size_is_reduced_by_1)
        {
          BOOST_CHECK_EQUAL(stack.size(), size_before_pop - 1);
        }
      END_
    END_

  END_


BOOST_AUTO_TEST_SUITE_END()
