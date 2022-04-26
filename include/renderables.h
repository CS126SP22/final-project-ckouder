#pragma once

#include "engine.h"
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

  struct Renderable : Atom {
    ci::Color color = ci::Color("red");
    virtual Renderables GetType() const;
  };

  struct Square : Renderable {
    vec2 size;
    Renderables GetType() const;
  };

  struct Circle : Renderable {
    float radius;
    Renderables GetType() const;
  };

  struct Line : Renderable {
    vec2* to;
    Renderables GetType() const;
  };

  void Render(const Renderable*);
} // namespace bitcoin
