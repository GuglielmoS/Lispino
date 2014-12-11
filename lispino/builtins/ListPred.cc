#include "ListPred.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t ListPred::getRequiredArguments() const {
  return 1;
}

std::string ListPred::getName() const {
  return "list?";
}

Object* ListPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  bool pred_result = false;

  if (args[0]->isList()) {
    Object *rest = static_cast<List*>(args[0])->getRest();
    pred_result = rest->isNil() || rest->isList();
  }

  return VM::getAllocator().createBoolean(pred_result);
}
}
}
