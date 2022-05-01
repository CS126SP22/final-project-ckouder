#include "force.h"
#include <exception>

#define NOT_IMPLEMENTED -1

namespace bitcoin
{
  void ForceConfig::TryApply(Atom* atom) {
    if (ShouldTrigger(atom)) {
      Apply(atom);
    }
  }

  bool ForceConfig::ShouldTrigger(Atom*) {
    throw NOT_IMPLEMENTED;
  }

  void ForceConfig::Apply(Atom*) {
    throw NOT_IMPLEMENTED;
  }

  void StringForceConfig::Apply(Atom* atom) {
    return;
  }

  bool StringForceConfig::ShouldTrigger(Atom* atom) {
    return !expired && glm::length(a->position - b->position) > min_length;
  }

  void DistanceForceConfig::Apply(Atom* atom) {
    vec2 diff = atom->position - *origin;
    float distance = glm::length(diff);
    atom->acceleration -= vec2(
      diff[0] == 0 ? 0 : (diff[0] < 0 ? magnitude : -magnitude) / distance,
      diff[1] == 0 ? 0 : (diff[1] < 0 ? magnitude : -magnitude) / distance
    );
  }

  bool DistanceForceConfig::ShouldTrigger(Atom* atom) {
    float distance = glm::length(atom->position - *origin);
    return !expired && distance < range && distance > 0;
  }
}