#pragma once
#include "force.h"
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
    ci::Color color = ci::Color("grey");
    virtual Shapes GetType() const;
    virtual void Render(vec2);
  };

  struct Square : Shape {
    vec2 size = vec2(10);
    Shapes GetType() const;
    void Render(vec2);
  };

  struct Circle : Shape {
    float radius = 5;
    Shapes GetType() const;
    void Render(vec2);
  };

  struct Line : Shape {
    vec2* from;
    vec2* to;

    Line() {};
    Line(Atom* a, Atom* b) : from(&a->position), to(&b->position) {};

    Shapes GetType() const;
    void Render(vec2);
  };
} // namespace bitcoin
