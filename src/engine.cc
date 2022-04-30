#include "engine.h"

namespace bitcoin
{
  // vec2 Force::GetPosition() {
  //   return position_ref == nullptr ? position : *(position_ref);
  // }

  // void Force::SetPosition(vec2* ref) {
  //   position_ref = ref;
  // }

  // void Force::SetPosition(vec2 p) {
  //   position = p;
  // }

  void Engine::Add(Atom* atom) {
    atoms.push_back(atom);
  }

  void Engine::ComputeAcceleration(Atom* atom) {
    // for (auto force : atom->forces) {
      // vec2 diff = atom->position - force->GetPosition();
      // float distance = glm::length(diff);
      // if (distance < force->range) {
        // atom->acceleration -= vec2(
        //   diff[0] == 0 ? 0 : (diff[0] < 0 ? force->magnitude[0] : -force->magnitude[0]),
        //   diff[1] == 0 ? 0 : (diff[1] < 0 ? force->magnitude[1] : -force->magnitude[1])
        // );
      // }
    // }
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
