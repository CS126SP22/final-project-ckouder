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

  ForceType ForceConfig::GetType() {
    return NA;
  }

  bool ForceConfig::ShouldTrigger(Atom*) {
    throw NOT_IMPLEMENTED;
  }

  void ForceConfig::Apply(Atom*) {
    throw NOT_IMPLEMENTED;
  }

  void StringForceConfig::Apply(Atom* atom) {
    vec2 diff = a->position - b->position;
    float distance = glm::length(diff);
    float coe = distance - length;
    coe = -coe * (coe < 0 ? negk : k);

    a->acceleration += (diff / distance) * coe;
    b->acceleration += (-diff / distance) * coe;
  }

  bool StringForceConfig::ShouldTrigger(Atom* atom) {
    return !expired && glm::length(a->position - b->position) != length;
  }

  ForceType StringForceConfig::GetType() {
    return STRING;
  }

  vec2 DistanceForceConfig::GetOrigin() {
    return ref_ == nullptr ? origin_ : ref_->position;
  }

  void DistanceForceConfig::SetOrigin(Atom* ref) {
    ref_ = ref;
  }

  void DistanceForceConfig::SetOrigin(vec2 origin) {
    origin_ = origin;
  }

  void DistanceForceConfig::Apply(Atom* atom) {
    vec2 diff = atom->position - GetOrigin();
    float distance = glm::length(diff) > 1 ? glm::length(diff) : 1;
    float x_acc = diff[0] == 0 ? 0 : (diff[0] > 0 ? magnitude : -magnitude) / distance,
          y_acc = diff[1] == 0 ? 0 : (diff[1] > 0 ? magnitude : -magnitude) / distance;

    atom->acceleration += vec2(x_acc, y_acc);
  }

  bool DistanceForceConfig::ShouldTrigger(Atom* atom) {
    float distance = glm::length(atom->position - GetOrigin());
    return !expired && distance < range && distance > 0;
  }

  ForceType DistanceForceConfig::GetType() {
    return DISTANCE;
  }

  bool FrictionForceConfig::ShouldTrigger(Atom* atom) {
    return glm::length(atom->velocity) != 0;
  }

  void FrictionForceConfig::Apply(Atom* atom) {
    atom->acceleration -= (atom->velocity * magnitude);
  }

  ForceType FrictionForceConfig::GetType() {
    return FRICTION;
  }
}