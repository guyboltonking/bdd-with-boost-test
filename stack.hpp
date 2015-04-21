#pragma once

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

