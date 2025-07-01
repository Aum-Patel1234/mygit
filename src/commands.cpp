#include "../include/commands.h"

Command getCommandMap(const std::string cmd) {
  static const std::unordered_map<std::string, Command> map = {
      {"init", Command::init},     {"add", Command::add},
      {"commit", Command::commit}, {"status", Command::status},
      {"log", Command::log},       {"help", Command::help},
      {"merge", Command::merge},   {"diff", Command::diff}};

  auto command = map.find(cmd);
  return command != map.end() ? command->second : Command::null;
}
