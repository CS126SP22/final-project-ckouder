#include "engine.h"
#include "force.h"

namespace bitcoin
{
  void Engine::AddAtom(Atom* atom) {
    atoms_.push_back(atom);
  }

  void Engine::AddForceEmitter(ForceEmitter* emitter) {
    forces_.push_back(emitter);
  }

  void Engine::ComputeAcceleration(Atom* atom) {
    for (auto emitter : forces_) {
      emitter->TryApplyForce(atom);
    }
  }

  void Engine::ComputeVelocity(Atom* atom) {
    atom->velocity += atom->acceleration / S;
  }

  void Engine::ComputePosition(Atom* atom) {
    atom->position += atom->velocity / S;
  }

  void Engine::Compute() {
    for (auto atom : atoms_) {
      ComputeAcceleration(atom);
    }
    for (auto atom : atoms_) {
      ComputeVelocity(atom);
    }
    for (auto atom : atoms_) {
      ComputePosition(atom);
    }
  }
} // namespace bitcoin
