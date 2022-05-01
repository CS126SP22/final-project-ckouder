#include "renderables.h"

using cinder::Rectf;

namespace bitcoin {

Renderables Renderable::GetType() const {
  return PARTICLE;
}

void Renderable::Render() {
  return;
}

Renderables Square::GetType() const {
  return SQUARE;
}

void Square::Render() {
  ci::gl::color(color);
  ci::gl::drawSolidRect(Rectf(
    position - size / vec2(2),
    position + size / vec2(2)
  ));
}

Renderables Circle::GetType() const {
  return CIRCLE;
}

void Circle::Render() {
  ci::gl::color(color);
  ci::gl::drawSolidCircle(position, radius);
}

Renderables Line::GetType() const {
  return LINE;
}

void Line::Render() {
  ci::gl::color(color);
  ci::gl::drawLine(position, *end);
}

}// namespace bitcoin