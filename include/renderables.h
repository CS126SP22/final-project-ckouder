#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace bitcoin
{
  enum Renderables {
    PARTICLE,
    SQUARE,
    CIRCLE,
    LINE
  };

  struct Particle {
    vec2* position;
    vec2 velocity;
    // float rotation;
    ci::Color color = ci::Color("red");
    virtual Renderables GetType() const;
  };

  struct Square : Particle {
    vec2 size;
    Renderables GetType() const;
  };

  struct Circle : Particle {
    float radius;
    Renderables GetType() const;
  };

  struct Line : Particle {
    vec2* to;
    Renderables GetType() const;
  };

  void Render(const Particle*);
} // namespace bitcoin
