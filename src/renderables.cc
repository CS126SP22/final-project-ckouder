#include "renderables.h"

using cinder::Rectf;

namespace bitcoin {

Shapes Shape::GetType() const {
  return PARTICLE;
}

void Shape::Render() {
  return;
}

Shapes Square::GetType() const {
  return SQUARE;
}

void Square::Render() {
  ci::gl::color(color);
  ci::gl::drawSolidRect(Rectf(
    position - size / vec2(2),
    position + size / vec2(2)
  ));
}

Shapes Circle::GetType() const {
  return CIRCLE;
}

void Circle::Render() {
  ci::gl::color(color);
  ci::gl::drawSolidCircle(position, radius);
}

Shapes Line::GetType() const {
  return LINE;
}

void Line::Render() {
  ci::gl::color(color);
  ci::gl::drawLine(*from, *to);
}

}// namespace bitcoin