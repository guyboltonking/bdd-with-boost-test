#pragma once

#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/test/test_observer.hpp>
#include <boost/test/unit_test_suite_impl.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/utils/basic_cstring/basic_cstring.hpp>
#include <boost/test/utils/basic_cstring/io.hpp>

#include <boost/noncopyable.hpp>

#include <boost/algorithm/string.hpp>

namespace boost_test_extensions {

//-----------------------------------------------------------------------------
/*! If passed to framework::register_observer, tracks the current path of
    the unit test being executed to allow for trivial cut-and-paste to
    run_test option. */
class TestPathObserver: public boost::unit_test::test_observer {
public:
  // Used in combination with the implementation of test_observer to track
  // the full path of the current test.
  std::string current_test_path() const
  {
    return boost::join(test_units_, "/");
  }

private:
  std::vector<std::string> test_units_;

  //--------------------------------------------------------------------------
  // test_observer overrides

  void test_unit_start(boost::unit_test::test_unit const& tu) override
  {
    test_units_.push_back(tu.p_name.get());
  }

  void test_unit_finish(boost::unit_test::test_unit const&, unsigned long) override
  {
    test_units_.pop_back();
  }
};

//-----------------------------------------------------------------------------
/*! Hierarchical spec-style output logger for Boost Test */
class SpecLogFormatter:
    public boost::unit_test::output::compiler_log_formatter,
    public TestPathObserver {

public:
  SpecLogFormatter(): indent_(0) {}

  static SpecLogFormatter *get_formatter()
  {
    static SpecLogFormatter *formatter = 0;
    if (!formatter)
    {
      formatter = new SpecLogFormatter;
    }
    return formatter;
  }

  static void Register()
  {
    boost::unit_test::unit_test_log.set_formatter(get_formatter());
    boost::unit_test::framework::register_observer(*get_formatter());
  }

private:
  int indent_;

  void indent() 
  {
    indent_ += 2;
  }

  void dedent()
  {
    indent_ -= 2;
  }

  std::ostream &indented(std::ostream &os) const
  {
    return os << std::string(indent_, ' ');
  }

  void maybe_report_slow(std::ostream &os, unsigned long elapsed) const
  {
    if (elapsed > 100000) {
      indented(os) << "...SLOW: ";
      if(!(elapsed % 1000))
        os << elapsed/1000 << "ms" << std::endl;
      else
        os << elapsed << "mks" << std::endl;
    }
  }

  void show_human_readable_test_name(std::ostream &os, 
    std::string const &test_name) const
  {
    indented(os) << boost::replace_all_copy(test_name, "_", " ") << std::endl;
  }

  void maybe_show_current_test_path(std::ostream& os) const
  {
    auto path = current_test_path();
    if (!path.empty())
    {
      indented(os) << path << ":" << std::endl;
    }
  }

  //--------------------------------------------------------------------------
  // compiler_log_formatter overrides

  void test_unit_start(std::ostream &os,
    boost::unit_test::test_unit const& tu) override
  {
    show_human_readable_test_name(os, tu.p_name.get());
    indent();
  }

  void test_unit_finish(std::ostream &os,
    boost::unit_test::test_unit const&, unsigned long elapsed) override
  {
    maybe_report_slow(os, elapsed);
    dedent();
  }

  void log_entry_start(std::ostream& os, 
    boost::unit_test::log_entry_data const& entry_data, 
    log_entry_types let) override
  {
    if (let == BOOST_UTL_ET_ERROR || let == BOOST_UTL_ET_FATAL_ERROR)
    {
      indented(os) << "---" << std::endl;
      maybe_show_current_test_path(os);
    }
    compiler_log_formatter::log_entry_start(indented(os), entry_data, let);
  }

  void log_exception(std::ostream& os, 
    boost::unit_test::log_checkpoint_data const& checkpoint_data, 
    boost::execution_exception const& ex) override
  {
    indented(os) << "---" << std::endl;
    maybe_show_current_test_path(os);
    compiler_log_formatter::log_exception(os, checkpoint_data, ex);      
  }

};

}
