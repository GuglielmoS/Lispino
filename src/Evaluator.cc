#include "Evaluator.h"

#include "VM.h"
#include "builtins/BuiltinFunction.h"
#include "utils/List.h"

namespace Lispino {

Evaluator::Evaluator(std::shared_ptr<Environment> env) : global_env(env) {
  /* DO NOTHING */
}

Object* Evaluator::eval(Object* expr) throw (Errors::RuntimeError) {
  return eval(expr, global_env);
}

Object* Evaluator::eval(Object *expr, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object *current_object = expr;
  std::shared_ptr<Environment> current_env = env;

  while (true) {
    switch (current_object->getType()) {
      // self evaluating expression
      case ObjectType::NIL:
      case ObjectType::BOOLEAN:
      case ObjectType::INT_NUMBER:
      case ObjectType::FLOAT_NUMBER:
      case ObjectType::STRING:
      case ObjectType::BUILTIN_FUNCTION:
      case ObjectType::CLOSURE:
        return current_object;

      case ObjectType::SYMBOL:
        return current_env->get(static_cast<Symbol*>(current_object));

      case ObjectType::QUOTE:
        return static_cast<Quote*>(current_object)->getValue();
    
      case ObjectType::DEFINE:
        return evalDefine(static_cast<Define*>(current_object), current_env);

      case ObjectType::LAMBDA: {
        Lambda *lambda = static_cast<Lambda*>(current_object);
        return VM::getAllocator().createClosure(lambda, current_env->extend(current_env));
      }

      case ObjectType::IF:
        current_object = evalIf(static_cast<IfExpr*>(current_object), current_env);
        continue;

      case ObjectType::SEQUENCE:
        current_object = evalSequence(static_cast<Sequence*>(current_object), current_env);
        continue;

      case ObjectType::LIST: {
        List *list = static_cast<List*>(current_object);

        // extract the first element of the list
        Object *first = list->getFirst();

        // evaluate the first element
        Object *evaluated_first = eval(first, current_env);

        // extract the arguments to use for the function application
        std::vector<Object*> arguments;
        if (list->getRest()->isList()) {
          arguments = Utils::list2vec(static_cast<List*>(list));
        } else if (list->getRest()->isNil()) { 
          // DO NOTHING, there are zero arguments
        } else {
          throw Errors::RuntimeError("Invalid function call: malformed arguments given");
        }

        // since the special cases have been all treated in the previous cases,
        // a list must represent a function call. The first element evaluated
        // is therefore a builtin function or a closure.
        switch (evaluated_first->getType()) {
          case ObjectType::BUILTIN_FUNCTION: {
            Builtins::BuiltinFunction *bf = static_cast<Builtins::BuiltinFunction*>(evaluated_first);
            
            // check that there are enough arguments for the specified builtin function
            if (arguments.size() < bf->getRequiredArguments())
              throw Errors::RuntimeError("Invalid function call: wrong number of arguments");

            // execute the builtin function and return the result
            return bf->apply(arguments, current_env); 
          }

          case ObjectType::LAMBDA: {
            Lambda *lambda = static_cast<Lambda*>(evaluated_first);

            // check that there are enough arguments for the specified lambda code
            auto lambda_arguments = lambda->getArguments();
            if (lambda_arguments.size() != arguments.size())
              throw Errors::RuntimeError("Invalid function call: wrong number of arguments");

            // evaluate each argument
            std::vector<Object*> evaluated_arguments;
            for (auto& current_arg : arguments)
              evaluated_arguments.push_back(eval(current_arg, current_env));
    
            // extend the current environment with the arguments to apply
            current_env = current_env->extend(current_env);
            for (unsigned int i = 0; i < evaluated_arguments.size(); i++)
              current_env->put(VM::getAllocator().createSymbol(lambda_arguments[i]), evaluated_arguments[i]);

            // evaluate the code associated to this lambda
            current_object = lambda->getBody();
            continue;
          }

          case ObjectType::CLOSURE: {
            Closure *closure = static_cast<Closure*>(evaluated_first);

            // check that there are enough arguments for the specified lambda code
            auto lambda_arguments = closure->getLambda()->getArguments();
            if (lambda_arguments.size() != arguments.size())
              throw Errors::RuntimeError("Invalid function call: wrong number of arguments");

            // evaluate each argument
            std::vector<Object*> evaluated_arguments;
            for (auto& current_arg : arguments)
              evaluated_arguments.push_back(eval(current_arg, current_env));
         
            // extend the current environment with the arguments to apply
            for (unsigned int i = 0; i < evaluated_arguments.size(); i++)
              closure->getEnv()->put(VM::getAllocator().createSymbol(lambda_arguments[i]), evaluated_arguments[i]);

            // evaluate the code associated to this lambda in the extended environment
            current_object = closure->getLambda()->getBody();
            current_env = closure->getEnv();

            continue;
          }

          default:
            throw Errors::RuntimeError("Invalid function call: non-callable object given");
        }
      }

      default:
        throw Errors::RuntimeError("Invalid object given, evaluation suspended!");
    }
  }
}

Object* Evaluator::evalIf(IfExpr* expr, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object *condition_result = eval(expr->getCondition(), env);

  if (condition_result->isTrue())
    return expr->getConsequent();
  else
    return expr->getAlternative(); 
}

Object* Evaluator::evalSequence(Sequence* expr, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object *result = VM::getAllocator().createNil();
  for (auto& cur_expr : expr->getValue())
    result = eval(cur_expr, env);

  return result;
}

Object* Evaluator::evalDefine(Define *expr, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  if (expr->getValue()->isLambda())
    return env->put(expr->getSymbol(), expr->getValue());
  else
    return env->put(expr->getSymbol(), eval(expr->getValue(), env));
}

}
