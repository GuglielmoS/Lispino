#include "ListPred.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t ListPred::getRequiredArguments() const {
  return 1;
}
  
std::string ListPred::getName() const {
  return "list?";
}

Object* ListPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  bool pred_result = false;
  Object* arg = eval(args[0], env);

  if (arg->isList()) {
    Object *rest = static_cast<List*>(arg)->getRest();
    pred_result = rest->isNil() || rest->isList();
  }

  return VM::getAllocator().createBoolean(pred_result);
}

}

}
