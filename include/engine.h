#pragma once
#include "force.h"
#include "mass.h"
#include "renderables.h"
#include "cinder/gl/gl.h"

#define S 50.0f

using glm::vec2;
using std::unordered_map;
using std::vector;

namespace bitcoin
{

class Engine {
  public:
  void AddAtom(Atom*);
  void AddForce(ForceConfig*);

  void ComputeAcceleration();
  void ComputeVelocity(Atom*);
  void ComputePosition(Atom*);
  void Compute();

  template<typename R, typename T>
  void AddMass(Mass<R, T>* mass) {
    AddAtom(mass);
    AddForce(mass);
  }

  private:
  vector<Atom*> atoms_;
  vector<FrictionForceConfig*> frictions_;
  vector<StringForceConfig*> tensions_;
  vector<DistanceForceConfig*> gravities_;
};

} // namespace bitcoin
