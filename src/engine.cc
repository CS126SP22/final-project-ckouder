#include "engine.h"
#include "force.h"

namespace bitcoin
{

  void Engine::AddShape(Atom* shape) {
    if (std::find(shapes_.begin(), shapes_.end(), shape) != shapes_.end()) {
      return;
    }
    shapes_.push_back(shape);
  }

  void Engine::AddForce(ForceConfig* config) {
    if (std::find(frictions_.begin(), frictions_.end(), config) != frictions_.end()) {
      return;
    }
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
    for (auto atom : shapes_) {
      for (auto force : gravities_) {
        force->TryApply(atom);
      }
      for (auto force : frictions_) {
        force->TryApply(atom);
      }
    }
  }

  void Engine::ComputeVelocity(Atom* atom) {
    if (atom->status != FREEZED) {
      atom->velocity += atom->acceleration / S;
    }
    atom->acceleration = vec2(0, 0);
  }

  void Engine::ComputePosition(Atom* atom) {
    if (atom->status != FREEZED) {
      atom->position += atom->velocity / S;
    }
  }

  void Engine::Compute() {
    ComputeAcceleration();
    for (auto atom : shapes_) {
      ComputeVelocity(atom);
    }
    for (auto atom : shapes_) {
      ComputePosition(atom);
    }
  }
} // namespace bitcoin
