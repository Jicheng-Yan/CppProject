#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "SomeClass.h"
#include "version.h"
#include "spdlog/spdlog.h"
#include "gflags/gflags.h"
//#include "spdlog/sinks/stdout_sinks.h"

DEFINE_bool(verbose, false, "Display program name before message");
DEFINE_string(message, "Hello world!", "Message to print");

static bool IsNonEmptyMessage(const char *flagname, const std::string &value)
{
  return value[0] != '\0';
}
DEFINE_validator(message, &IsNonEmptyMessage);

#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON
#define SPDLOG_INFO_ON

using namespace std;
namespace spd = spdlog;

void printHelp() {
  cout << "Help for cleanCppApplication " << endl;
  cout << "Version: " << Version::current().asLongStr() << endl;
  cout << "Version: " << Version::current().asShortStr() << endl;
  cout << "Version: " << Version::current().asNumber() << endl;
  cout << "Author:  " << endl;
  cout << "URL:     " << endl;
  /// @todo Do stuff in here also
}

/**
 * Example UML diagram:
 *
 * \startuml
 *
 * [-> main : start program
 *
 * activate main
 *
 * main -> main : process parameters
 *
 * main -> Version : get version
 *
 * activate Version
 * Version -> Version : loads version
 * Version -> main
 * deactivate Version
 *
 * main -> main : prints version
 *
 * main -> SomeClass : create instance
 * activate SomeClass
 * SomeClass -> BaseClass : call constructor
 * activate BaseClass
 *
 * main -> SomeClass : do stuff
 * activate SomeClass
 * SomeClass -> main : return stuff
 * deactivate SomeClass
 *
 * BaseClass -> SomeClass
 * deactivate BaseClass
 * SomeClass -> main
 * deactivate SomeClass
 *
 * deactivate main
 *
 * \enduml
 */
int main(int argc, char  *argv[]) {
  gflags::SetUsageMessage("some usage message");
  gflags::SetVersionString("1.0.0");
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  if (FLAGS_verbose) std::cout << gflags::ProgramInvocationShortName() << ": ";
  std::cout << FLAGS_message << std::endl;
  gflags::ShutDownCommandLineFlags();

  // Console logger with color
  auto console = spd::stdout_color_mt("console");
  console->info("Welcome to spdlog!");

  // Print help if no arguments are given
  if (argc == 1)
    printHelp();

  // process parameters
  int argIt;
  for (argIt = 1; argIt < argc; ++argIt) {
    string tmp = argv[argIt];

    if (tmp == "--help" || tmp == "-h")
      printHelp();
    else if (tmp == "--version")
      cout << "v" << Version::current().asLongStr() << endl;
    else
      break;
  }
  // process rest of the free arguments. EG. file list, word list
  for (; argIt < argc; ++argIt)
    cout << argv[argIt] << endl;

  /// @todo Do more stuff.
  {
    BaseClass c;
    if (argc == 1)
      c.freePtr();
    /// @todo fix another leak
  }

  SomeClass o;
  o.set(5);
  cout << o.get() << endl;

  // possible memory leak here, run with `make analyze`
  int *a = new int(5);
  cout << *a << endl;

  if (argc == 3)
    return 1;

  // we will crash here
  delete a;
  cout << *a << endl;

  return 0;
}
