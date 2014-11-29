#ifndef LISPINO_GARBAGECOLLECTOR_H_
#define LISPINO_GARBAGECOLLECTOR_H_

#include <vector>
#include <memory>

#include "Environment.h"

namespace lispino {

class GarbageCollector {
 public:
  explicit GarbageCollector(std::shared_ptr<Environment> env);

  void collect();

 private:
  // global environment reference
  std::shared_ptr<Environment> global_env;

  bool alreadyMarked(std::shared_ptr<Environment> env, std::vector<Environment*>& marked_envs);

  void markObject(Object *object, std::vector<Environment*>& marked_envs);
  void markVisibleObjects(std::shared_ptr<Environment> env, std::vector<Environment*>& marked_envs);
};
}

#endif // LISPINO_GARBAGECOLLECTOR_H_
