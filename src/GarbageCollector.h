#ifndef LISPINO_GARBAGECOLLECTOR_H_
#define LISPINO_GARBAGECOLLECTOR_H_

#include <vector>

#include "Environment.h"

namespace Lispino {

class GarbageCollector {
 public:
  GarbageCollector(Environment& env);

  void collect();

 private:

  // global environment reference
  Environment &global_env;

  bool alreadyMarked(Environment* env, std::vector<Environment*> marked_envs);

  void markVisibleObjects(Environment* env, std::vector<Environment*>& marked_envs);
};

}

#endif // LISPINO_GARBAGECOLLECTOR_H_
