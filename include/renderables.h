#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace bitcoin
{
  enum Renderables {
    ATOM,
    SQUARE,
    CIRCLE
  };

  struct RenderableObject {
    vec2 velocity;
    // float rotation;
    ci::Color color = ci::Color("red");
    virtual Renderables GetType() const;
  };

  struct Square : RenderableObject {
    vec2 size;
    Renderables GetType() const;
  };

  struct Circle : RenderableObject {
    float radius;
    Renderables GetType() const;
  };  

  void Render(const RenderableObject*, const vec2&);
} // namespace bitcoin
