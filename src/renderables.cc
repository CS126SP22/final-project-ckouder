#include "renderables.h"

using cinder::Rectf;

namespace bitcoin {

Renderables Renderable::GetType() const {
  return PARTICLE;
}

Renderables Square::GetType() const {
  return SQUARE;
}

Renderables Circle::GetType() const {
  return CIRCLE;
}

Renderables Line::GetType() const {
  return LINE;
}

void Render(const Renderable* object) {
    const vec2& position = object->position;
    ci::gl::color(object->color);
    switch (object->GetType()) {

      case SQUARE:
        ci::gl::drawSolidRect(Rectf(
          position - (((Square*)object)->size) / vec2(2),
          position + (((Square*)object)->size) / vec2(2)
        ));
        break;

      case CIRCLE:
        ci::gl::drawSolidCircle(position, ((Circle*)object)->radius);
        break;

      case LINE:
        ci::gl::drawLine(position, *(((Line*)object)->to));
        break;

      case PARTICLE:
        break;
    }
}

}// namespace bitcoin