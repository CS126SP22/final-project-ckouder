#include "engine.h"

namespace bitcoin
{
  void Engine::ComputeAcceleration(const Particle* particle) {
    
  }

  void Engine::ComputeVelocity(const Particle* particle) {
    if (particle->velocity == nullptr || particle->acceleration == nullptr) {
      return;
    }
    *(particle->velocity) += *(particle->acceleration) / S;
  }

  void Engine::ComputePosition(const Particle* particle) {
    if (particle->position == nullptr || particle->velocity == nullptr) {
      return;
    }
    *(particle->position) += *(particle->velocity) / S;
  }

  void Engine::Compute(const Particle* particle) {
    ComputeAcceleration(particle);
    ComputeVelocity(particle);
    ComputePosition(particle);
  }
} // namespace bitcoin
