#pragma once

#include "engine.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace bitcoin
{

  enum Shapes {
    PARTICLE,
    SQUARE,
    CIRCLE,
    LINE
  };

  struct Shape : Atom {
    ci::Color color = ci::Color("red");
    virtual Shapes GetType() const;
    virtual void Render();
  };

  struct Square : Shape {
    vec2 size;
    Shapes GetType() const;
    void Render();
  };

  struct Circle : Shape {
    float radius;
    Shapes GetType() const;
    void Render();
  };

  struct Line : Shape {
    vec2* from;
    vec2* to;

    Line() {};
    Line(Atom* a, Atom* b) : from(&a->position), to(&b->position) {};

    Shapes GetType() const;
    void Render();
  };
} // namespace bitcoin
