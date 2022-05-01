#include "engine.h"
#include "force.h"

namespace bitcoin
{

  void Engine::AddAtom(Atom* atom) {
    atoms_.push_back(atom);
  }

  void Engine::AddForce(ForceConfig* config) {

    switch (config->GetType()) {
      case FRICTION:
        frictions_.push_back((FrictionForceConfig*)config);
        break;
      case STRING:
        tensions_.push_back((StringForceConfig*)config);
        break;
      case DISTANCE:
        gravities_.push_back((DistanceForceConfig*)config);
        break;
      case NA:
        throw -1;
        break;
    };
  }

  void Engine::ComputeAcceleration() {
    for (auto force : tensions_) {
      force->TryApply(nullptr);
    }
    for (auto atom : atoms_) {
      for (auto force : gravities_) {
        force->TryApply(atom);
      }
      for (auto force : frictions_) {
        force->TryApply(atom);
      }
    }
  }

  void Engine::ComputeVelocity(Atom* atom) {
    atom->velocity += atom->acceleration / S;
    atom->acceleration = vec2(0, 0);
  }

  void Engine::ComputePosition(Atom* atom) {
    atom->position += atom->velocity / S;
  }

  void Engine::Compute() {
    ComputeAcceleration();
    for (auto atom : atoms_) {
      ComputeVelocity(atom);
    }
    for (auto atom : atoms_) {
      ComputePosition(atom);
    }
  }
} // namespace bitcoin
