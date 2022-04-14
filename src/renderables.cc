#include "renderables.h"

using cinder::Rectf;

namespace bitcoin {

Renderables RenderableObject::GetType() const {
  return ATOM;
}

Renderables Square::GetType() const {
  return SQUARE;
}

Renderables Circle::GetType() const {
  return CIRCLE;
}

void Render(
  const RenderableObject* object,
  const vec2& position) {
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

      case ATOM:
        break;
    }
}

}// namespace bitcoin