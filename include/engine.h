#pragma once
#include "renderables.h"

#define S 50.0f

namespace bitcoin
{

class Engine {
 public:
  // vec2 friction;
  void ComputeAcceleration(const Particle*);
  void ComputeVelocity(const Particle*);
  void ComputePosition(const Particle*);
  void Compute(const Particle*);
};

} // namespace bitcoin
