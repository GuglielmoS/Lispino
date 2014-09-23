#include "Evaluator.h"

#include <cassert>

#include "VM.h"
#include "Args.h"
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
      case ObjectType::CHARACTER:
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
        return VM::getAllocator().createClosure(lambda, Environment::extend(current_env));
      }

      case ObjectType::SEQUENCE:
        return evalSequence(static_cast<Sequence*>(current_object), current_env);

      case ObjectType::IF:
        current_object = evalIf(static_cast<IfExpr*>(current_object), current_env);
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
        // is therefore a builtin function, a lambda or a closure.
        if (evaluated_first->isBuiltinFunction()) {
          Builtins::BuiltinFunction *bf = static_cast<Builtins::BuiltinFunction*>(evaluated_first);
          
          // check that there are enough arguments for the specified builtin function
          if (arguments.size() < bf->getRequiredArguments())
            throw Errors::RuntimeError("Invalid function call: wrong number of arguments");

          // execute the builtin function and return the result
          return bf->apply(arguments, current_env); 
        } else {
          // extract the lambda object to execute
          Lambda *lambda = nullptr;
          if (evaluated_first->isLambda()) {
            lambda = static_cast<Lambda*>(evaluated_first);
          } else if (evaluated_first->isClosure()) {
            lambda = static_cast<Lambda*>(static_cast<Closure*>(evaluated_first)->getLambda());
          } else { 
            throw Errors::RuntimeError("Invalid function call: non-callable object given");
          }

          // check that there are enough arguments for the specified lambda code
          if (!validateArguments(lambda, arguments))
            throw Errors::RuntimeError("Invalid function call: wrong number of arguments");

          // extract and evaluate the arguments from the raw list of arguments
          Args evaluated_arguments = extractAndEvalArgs(lambda, arguments, current_env);

          // extend the current environment
          if (evaluated_first->isLambda())
            current_env = Environment::extend(current_env);
          else
            current_env = static_cast<Closure*>(evaluated_first)->getEnv();

          // apply the arguments to the current environment
          current_env->applyArgs(evaluated_arguments);

          // evaluate the code associated to the lambda
          current_object = lambda->getBody();

          continue;
        }
      }

      default:
        assert(false && "Invalid object given, evaluation suspended!");
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

Args Evaluator::extractAndEvalArgs(Lambda *lambda, std::vector<Object*> raw_args, std::shared_ptr<Environment> env) {
  auto lambda_arguments = lambda->getArguments();

  // check if there is a "catch rest" argument
  bool has_catch_rest = lambda->hasCatchRest(); 

  // compute the minimun arguments number and the position
  // of the last arguments
  size_t min_args = lambda_arguments.size();
  if (has_catch_rest && min_args > 0)
    min_args--;

  // evaluate each argument
  std::vector<Object*> first_arguments;
  std::vector<Object*> catch_rest_arguments;
  for (size_t i = 0; i < min_args; i++)
    first_arguments.push_back(eval(raw_args[i], env));
  if (has_catch_rest) {
    for (size_t i = min_args; i < raw_args.size(); i++)
      catch_rest_arguments.push_back(eval(raw_args[i], env));
  }

  // transform the arguments names in symbols
  std::vector<Symbol*> arguments_names;
  for (auto& arg : lambda_arguments)
    arguments_names.push_back(VM::getAllocator().createSymbol(arg));

  // build the arguments to apply accordingly to the fact that there
  // can be a "catch rest" argument
  Args evaluated_arguments(first_arguments, arguments_names);
  if (has_catch_rest)
    evaluated_arguments.setCatchRest(Utils::vec2list(catch_rest_arguments));

  return evaluated_arguments;
}

bool Evaluator::validateArguments(Lambda *lambda, std::vector<Object*>& raw_args) const {
  return raw_args.size() >= lambda->getRequiredArguments();
}

}
