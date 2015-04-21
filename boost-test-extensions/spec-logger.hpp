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
   std::string CurrentTestPath() const
   {
      return boost::join(testUnits_, "/");
   }

private:
   std::vector<std::string> testUnits_;

   //--------------------------------------------------------------------------
   // test_observer overrides

   void test_unit_start(boost::unit_test::test_unit const& tu) override
   {
      testUnits_.push_back(tu.p_name.get());
   }

   void test_unit_finish(boost::unit_test::test_unit const&, unsigned long) override
   {
      testUnits_.pop_back();
   }
};

//-----------------------------------------------------------------------------
/*! Hierarchical spec-style output logger for Boost Test */
class SpecLogFormatter:
   public boost::unit_test::output::compiler_log_formatter,
   public TestPathObserver {

public:
   SpecLogFormatter(): indent_(0) {}

   static SpecLogFormatter *GetFormatter()
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
      boost::unit_test::unit_test_log.set_formatter(GetFormatter());
      boost::unit_test::framework::register_observer(*GetFormatter());
   }

   friend class ScopedIndent;
  class ScopedIndent: boost::noncopyable {
   public:
      ScopedIndent() { SpecLogFormatter::GetFormatter()->Indent(); }
      ~ScopedIndent() { SpecLogFormatter::GetFormatter()->Dedent(); }
   };

private:
   int indent_;

   void Indent() 
   {
      indent_ += 2;
   }

   void Dedent()
   {
      indent_ -= 2;
   }

   std::ostream &Indented(std::ostream &os) const
   {
      return os << std::string(indent_, ' ');
   }

   void MaybeReportSlow(std::ostream &os, unsigned long elapsed) const
   {
      if (elapsed > 100000) {
         Indented(os) << "...SLOW: ";
         if(!(elapsed % 1000))
            os << elapsed/1000 << "ms" << std::endl;
         else
            os << elapsed << "mks" << std::endl;
      }
   }

   void ShowHumanReadableTestName(std::ostream &os, std::string const &testName) const
   {
      Indented(os) << boost::replace_all_copy(testName, "_", " ") << std::endl;
   }

   void MaybeShowCurrentTestPath(std::ostream& os) const
   {
      auto path = CurrentTestPath();
      if (!path.empty())
      {
         Indented(os) << CurrentTestPath() << ":" << std::endl;
      }
   }

   //--------------------------------------------------------------------------
   // compiler_log_formatter overrides

   void test_unit_start(std::ostream &os,
      boost::unit_test::test_unit const& tu) override
   {
      ShowHumanReadableTestName(os, tu.p_name.get());
      Indent();
   }

   void test_unit_finish(std::ostream &os,
      boost::unit_test::test_unit const&, unsigned long elapsed) override
   {
      MaybeReportSlow(os, elapsed);
      Dedent();
   }

   void log_entry_start(std::ostream& os, 
      boost::unit_test::log_entry_data const& entry_data, log_entry_types let) override
   {
      if (let == BOOST_UTL_ET_ERROR || let == BOOST_UTL_ET_FATAL_ERROR)
      {
         Indented(os) << "---" << std::endl;
         MaybeShowCurrentTestPath(os);
      }
      compiler_log_formatter::log_entry_start(Indented(os), entry_data, let);
   }

   void log_exception(std::ostream& os, 
      boost::unit_test::log_checkpoint_data const& checkpoint_data, 
      boost::execution_exception const& ex) override
   {
      Indented(os) << "---" << std::endl;
      MaybeShowCurrentTestPath(os);
      compiler_log_formatter::log_exception(os, checkpoint_data, ex);      
   }

};

}
