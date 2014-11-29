#include "Args.h"

namespace lispino {

Args::Args(std::vector<Object*> arguments, std::vector<Symbol*> arguments_names)
    : arguments(arguments),
      arguments_names(arguments_names),
      catch_rest(nullptr) {
  // DO NOTHING
}

Args::Args(std::vector<Object*> arguments, std::vector<Symbol*> arguments_names, List* catch_rest)
    : arguments(arguments),
      arguments_names(arguments_names),
      catch_rest(catch_rest) {
  // DO NOTHING
}

void Args::setArguments(std::vector<Object*> arguments) {
  this->arguments = arguments;
}

void Args::setArgumentsNames(std::vector<Symbol*> arguments_names) {
  this->arguments_names = arguments_names;
}

void Args::setCatchRest(List* catch_rest) {
  this->catch_rest = catch_rest;
}

std::vector<Object*> Args::getArguments() const {
  return arguments;
}

std::vector<Symbol*> Args::getArgumentsNames() const {
  return arguments_names;
}

List* Args::getCatchRest() {
  return catch_rest;
}

bool Args::hasCatchRest() const {
  return catch_rest != nullptr;
}
}
