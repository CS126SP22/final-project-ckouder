#include "force.h"
#include <exception>

#define NOT_IMPLEMENTED -1;

namespace bitcoin
{
  ForceEmitterType ForceEmitter::GetType() {
    throw NOT_IMPLEMENTED;
  }

  bool ForceEmitter::ShouldTrigger(Atom* atom) {
    throw NOT_IMPLEMENTED;
  }

  void ForceEmitter::ApplyForce(Atom* atom) {
    throw NOT_IMPLEMENTED;
  }

  bool ForceEmitter::IsExpired() {
    return expired;
  }

  void ForceEmitter::SetExpired() {
    expired = true;
  }

  // Distance Force Emitter
  ForceEmitterType DistanceForceEmitter::GetType() {
    return DISTANCE;
  }

  bool DistanceForceEmitter::ShouldTrigger(Atom* atom) {
    float distance = glm::length2(atom->position - *origin_);
    return distance < range_ && distance > 0;
  }

  void DistanceForceEmitter::ApplyForce(Atom* atom) {
    vec2 diff = atom->position - *origin_;
    float distance = glm::length(diff);
    atom->acceleration -= vec2(
      diff[0] == 0 ? 0 : (diff[0] < 0 ? magnitude_[0] : -magnitude_[0]),
      diff[1] == 0 ? 0 : (diff[1] < 0 ? magnitude_[1] : -magnitude_[1])
    );
  }

  // String Force Emitter
  ForceEmitterType StringForceEmitter::GetType() {
    return STRING;
  }

  bool StringForceEmitter::ShouldTrigger(Atom* atom) {
    return (atom == a_ || atom == b_) 
      && glm::length(a_->position - b_->position) > min_trigger_;
  }

  void StringForceEmitter::ApplyForce(Atom* atom) {
    return;
  }
}