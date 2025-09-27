#include "../include/commands.h"
#include "../include/init.h"
#include "../include/status.hpp"
#include "../test/basic_test.h"
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "No command exist.(use " << argv[0]
              << " help to list commands)\n";
    return 1;
  }

  std::string cmd = argv[1];
  Command command = getCommandMap(cmd);

  switch (command) {
  case Command::init:
    gitInit();
    std::cout << "Initializing an empty .mygit directory\n";
    break;

  case Command::add:
    std::cout << "Adding files to staging area.\n";
    break;

  case Command::commit:
    std::cout << "A new commit\n";
    break;

  case Command::status:
    std::cout << "Showing status of working directory and staging area\n";
    gitStatus();
    break;

  case Command::log:
    std::cout << "Showing commit history\n";
    break;

  case Command::merge:
    std::cout << "Merging to branches\n";
    break;

  case Command::diff:
    std::cout << "unstaged files to staging area are these files.\n";
    break;

  case Command::help:
    std::cout << "mygit - a minimal version control system\n\n";
    std::cout << "Available commands:\n";
    std::cout << "  init        - Initialize a new mygit repository\n";
    std::cout << "  add         - Add files to the staging area\n";
    std::cout << "  commit      - Commit staged changes to the repository\n";
    std::cout << "  status      - Show the status of working directory and "
                 "staging area\n";
    std::cout << "  log         - Show commit history\n";
    std::cout << "  diff        - Show changes between commits or working "
                 "directory\n";
    std::cout << "  branch      - List, create, or delete branches\n";
    std::cout
        << "  checkout    - Switch branches or restore working tree files\n";
    std::cout << "  merge       - Merge a branch into the current branch\n";
    std::cout << "  help        - Show help for mygit commands\n";
    break;

  case Command::null:
    std::cerr << "No command exist.(use " << argv[0]
              << " help to list commands)\n";
  default:
    return 1;
  }

  // Test cases for functiosn
  testBasicFunctions();

  return 0;
}
