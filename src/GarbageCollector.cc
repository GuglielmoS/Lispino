#include "GarbageCollector.h"

#include <algorithm>
#include <string>

#include "Character.h"
#include "Symbol.h"
#include "IntNumber.h"
#include "FloatNumber.h"
#include "List.h"
#include "String.h"
#include "Lambda.h"
#include "Closure.h"
#include "Promise.h"
#include "Quote.h"
#include "Define.h"
#include "IfExpr.h"
#include "Sequence.h"

namespace Lispino {

GarbageCollector::GarbageCollector(std::shared_ptr<Environment> env) : global_env(env) {
  /* DO NOTHING */
}

void GarbageCollector::collect() {
  std::vector<Environment*> marked_envs;
  markVisibleObjects(global_env, marked_envs);
}

bool GarbageCollector::alreadyMarked(std::shared_ptr<Environment> env, std::vector<Environment*>& marked_envs) {
  return std::find(marked_envs.begin(), marked_envs.end(), env.get()) != marked_envs.end();
}

void GarbageCollector::markObject(Object *object, std::vector<Environment*>& marked_envs) {
  if (!object->isMarked()) {
    // mark the object
    object->mark();

    // marke the sub-components
    switch (object->getType()) {
      case ObjectType::NIL:
      case ObjectType::BOOLEAN:
      case ObjectType::INT_NUMBER:
      case ObjectType::FLOAT_NUMBER:
      case ObjectType::SYMBOL:
      case ObjectType::STRING:
      case ObjectType::CHARACTER:
      case ObjectType::BUILTIN_FUNCTION:
        break;

      case ObjectType::IF: {
        IfExpr *if_obj = static_cast<IfExpr*>(object);
        markObject(if_obj->getCondition(), marked_envs);
        markObject(if_obj->getConsequent(), marked_envs);
        markObject(if_obj->getAlternative(), marked_envs);
        break;
      }

      case ObjectType::DEFINE: {
        Define *def = static_cast<Define*>(object);
        markObject(def->getSymbol(), marked_envs);
        markObject(def->getValue(), marked_envs);
        break;
      }

      case ObjectType::QUOTE: {
        Quote *quote = static_cast<Quote*>(object);
        markObject(quote->getValue(), marked_envs);
        break;
      }

      case ObjectType::LIST: {
        List *list = static_cast<List*>(object);
        markObject(list->getFirst(), marked_envs);
        markObject(list->getRest(), marked_envs);
        break;
      }

      case ObjectType::SEQUENCE: {
        Sequence *seq = static_cast<Sequence*>(object);
        for (auto& expr : seq->getValue())
          markObject(expr, marked_envs);
        break;
      }

      case ObjectType::LAMBDA: {
        Lambda *lambda = static_cast<Lambda*>(object);
        markObject(lambda->getBody(), marked_envs);
        break;
      }

      case ObjectType::CLOSURE: {
        Closure *closure = static_cast<Closure*>(object);
        markObject(closure->getLambda(), marked_envs);
        markVisibleObjects(closure->getEnv(), marked_envs);
        break;
      }

      case ObjectType::PROMISE: {
        Promise *promise = static_cast<Promise*>(object);
        markObject(promise->getBody(), marked_envs);
        if (promise->hasCachedResult())
          markObject(promise->getCachedResult(), marked_envs);
        markVisibleObjects(promise->getEnv(), marked_envs);
        break;
      }
    }
  }
}

void GarbageCollector::markVisibleObjects(std::shared_ptr<Environment> env, std::vector<Environment*>& marked_envs) {
  // mark the given environment objects if needed
  if (!alreadyMarked(env, marked_envs)) {
    marked_envs.push_back(env.get());

    // loop through the environment values
    for (auto& current_pair : env->getLookupTable()) {
      auto current_symbol = current_pair.second.first;
      auto current_object = current_pair.second.second;

      // mark the current key-value pair
      markObject(current_symbol, marked_envs);
      markObject(current_object, marked_envs);
    }
  }

  // mark the parent environment if it exists
  std::shared_ptr<Environment> parent_env = env->getParent();
  if (parent_env)
    markVisibleObjects(parent_env, marked_envs);
}
}
