#include <string>
#include <unordered_map>
#ifndef MYGITCOMMANDS

enum Command { init, add, commit, log, help, status, diff, merge, null };

Command getCommandMap(const std::string cmd);

#endif // !MYGITCOMMANDS
