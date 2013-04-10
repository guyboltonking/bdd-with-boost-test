#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>


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
