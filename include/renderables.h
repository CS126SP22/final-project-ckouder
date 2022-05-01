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
    virtual void Render();
  };

  struct Square : Renderable {
    vec2 size;
    Renderables GetType() const;
    void Render();
  };

  struct Circle : Renderable {
    float radius;
    Renderables GetType() const;
    void Render();
  };

  struct Line : Renderable {
    vec2* from;
    vec2* to;

    Line() {};
    Line(Atom* a, Atom* b) : from(&a->position), to(&b->position) {};

    Renderables GetType() const;
    void Render();
  };
} // namespace bitcoin
