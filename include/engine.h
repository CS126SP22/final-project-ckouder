#pragma once
#include "cinder/gl/gl.h"

#define S 50.0f

using glm::vec2;

namespace bitcoin
{

struct Atom {
  vec2 position = vec2(0);
  vec2 velocity = vec2(0);
  vec2 acceleration = vec2(0);
  vec2 field = vec2(-10);
  vec2 field_range = vec2(1000);
};

class Engine {
 public:
  void Add(Atom*);
  void ComputeAcceleration(Atom*);
  void ComputeVelocity(Atom*);
  void ComputePosition(Atom*);
  void Compute();

 private:
  std::vector<Atom*> atoms;
};

} // namespace bitcoin
