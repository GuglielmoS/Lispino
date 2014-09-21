#ifndef LISPINO_EVALUATOR_H_
#define LISPINO_EVALUATOR_H_

#include <memory>

#include "Object.h"
#include "Environment.h"
#include "errors/RuntimeError.h"

#include "IfExpr.h"
#include "Nil.h"
#include "IntNumber.h"
#include "FloatNumber.h"
#include "Boolean.h"
#include "Symbol.h"
#include "String.h"
#include "List.h"
#include "Lambda.h"
#include "Quote.h"
#include "IfExpr.h"
#include "Sequence.h"
#include "Define.h"

namespace Lispino {

class Evaluator {
 public:
  Evaluator(std::shared_ptr<Environment> env);

  Object* eval(Object* expr) throw (Errors::RuntimeError);

 private:
  std::shared_ptr<Environment> global_env;

  Object* eval(Object* expr, std::shared_ptr<Environment> env) throw (Errors::RuntimeError);
  Object* evalIf(IfExpr *expr, std::shared_ptr<Environment> env) throw (Errors::RuntimeError);
  Object* evalSequence(Sequence *expr, std::shared_ptr<Environment> env) throw (Errors::RuntimeError);
  Object* evalDefine(Define *expr, std::shared_ptr<Environment> env) throw (Errors::RuntimeError);
};

}

#endif // LISPINO_EVALUATOR_H__
