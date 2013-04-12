#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/included/unit_test.hpp>
#include <boost/algorithm/string.hpp>

//==============================================================================

class SpecLogFormatter: 
  public boost::unit_test::output::compiler_log_formatter {

public:
  SpecLogFormatter(): m_indent(0) {}

private:
  void test_unit_start(std::ostream &os, 
    boost::unit_test::test_unit const& tu) 
  {
    os << std::string(m_indent, ' ') << 
      boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
    m_indent += 2;
  }

  void test_unit_finish(std::ostream &os,
    boost::unit_test::test_unit const& tu, unsigned long elapsed)
  {
    m_indent -= 2;
  }

  int m_indent;
};

//==============================================================================

bool init_unit_test()
{
  boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
  return true;
}

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
