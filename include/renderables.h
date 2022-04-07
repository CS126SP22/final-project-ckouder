#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace bitcoin
{
  struct Particle {
    vec2 position;
    vec2 velocity;

    virtual void Render();
  };

  struct Square : Particle {
    vec2 size;

    void Render() override;
  };

  struct Circle : Particle {
    float radius;

    void Render() override;
  }; 
} // namespace bitcoin
