#include "engine.h"

namespace bitcoin
{
  void Engine::Add(Atom* atom) {
    atoms.push_back(atom);
  }

  void Engine::ComputeAcceleration(Atom* atom) {
    for (auto other : atoms) {
      vec2 diff = atom->position - other->position;
      float distance = glm::length2(diff);
      float field_range = glm::length2(atom->field_range + other->field_range);
      if (other == atom || distance > field_range) {
        continue;
      }
      atom->acceleration -= vec2(
        diff[0] == 0 ? 0 : (diff[0] < 0 ? other->field[0] : -other->field[0]),
        diff[1] == 0 ? 0 : (diff[1] < 0 ? other->field[1] : -other->field[1])
      );
    }
  }

  void Engine::ComputeVelocity(Atom* atom) {
    atom->velocity += atom->acceleration / S;
  }

  void Engine::ComputePosition(Atom* atom) {
    atom->position += atom->velocity / S;
  }

  void Engine::Compute() {
    for (auto atom : atoms) {
      ComputeAcceleration(atom);
    }
    for (auto atom : atoms) {
      ComputeVelocity(atom);
    }
    for (auto atom : atoms) {
      ComputePosition(atom);
    }
  }
} // namespace bitcoin
