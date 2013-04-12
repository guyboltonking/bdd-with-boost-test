//#define BOOST_TEST_ALTERNATIVE_INIT_API
//#include <boost/test/included/unit_test.hpp>
//#include <boost/algorithm/string.hpp>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

//==============================================================================

#include <stack>

template <typename T>
class Stack {
public:
  void push(const T &t) { m_stack.push(t); }

  void pop()
  {
    if (!m_stack.empty())
      m_stack.pop();
  }

  bool empty() const { return m_stack.empty(); }

  std::size_t size() const { return m_stack.size(); }
private:
  std::stack<T> m_stack;
};

//==============================================================================

TEST_CASE("a stack", "[stack]") {
  Stack<int> stack;

  SECTION("when initialised") {
    SECTION("should be empty") {
      REQUIRE(stack.empty());
    }
  }

  SECTION("pop") {
    SECTION("on an empty stack") {
      SECTION("should have no effect") {
        stack.pop();
        REQUIRE(stack.empty());
      }
    }

    SECTION("on a stack with a single member") {
      stack.push(1);

      SECTION("should reduce the stack size by one") {
        std::size_t orig_size = stack.size();
        stack.pop();
        REQUIRE(stack.size() == orig_size - 1);
      }
    }
  }

}

#if 0
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
#endif
