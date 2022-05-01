#pragma once
#include "force.h"
#include "cinder/gl/gl.h"

#define S 50.0f

using glm::vec2;

namespace bitcoin
{

class Engine {
  public:
  void AddAtom(Atom*);
  void AddForce(ForceConfig*);
  void ComputeAcceleration(Atom*);
  void ComputeVelocity(Atom*);
  void ComputePosition(Atom*);
  void Compute();

  private:
  std::vector<Atom*> atoms_;
  std::vector<ForceConfig*> forces_;
};

} // namespace bitcoin
