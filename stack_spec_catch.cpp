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

SCENARIO("a stack", "[stack]") {
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
