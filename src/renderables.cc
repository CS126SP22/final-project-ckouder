#include "renderables.h"
#include "config.h"

using cinder::Rectf;

#define FREEZE_FRAME_WIDTH 1
#define FREEZE_FRAME_MARGIN 1

namespace bitcoin {

Shapes Shape::GetType() const {
  return PARTICLE;
}

void Shape::Render(vec2 offset) {
  return;
}

Shapes Square::GetType() const {
  return SQUARE;
}

void Square::Render(vec2 offset) {
  if (status == FREEZED) {
    // draw frame square
    ci::gl::color(ci::Color(FRAME_COLOR));
    ci::gl::drawSolidRect(Rectf(
      position + offset - size / vec2(2) - vec2(FREEZE_FRAME_MARGIN + FREEZE_FRAME_WIDTH),
      position + offset + size / vec2(2) + vec2(FREEZE_FRAME_MARGIN + FREEZE_FRAME_WIDTH)
    ));
    // draw inner square
    ci::gl::color(ci::Color(BACKGROUND_COLOR));
    ci::gl::drawSolidRect(Rectf(
      position + offset - size / vec2(2) - vec2(FREEZE_FRAME_MARGIN),
      position + offset + size / vec2(2) + vec2(FREEZE_FRAME_MARGIN)
    ));
  }
  ci::gl::color(color);
  ci::gl::drawSolidRect(Rectf(
    position + offset - size / vec2(2),
    position + offset + size / vec2(2)
  ));
}

Shapes Circle::GetType() const {
  return CIRCLE;
}

void Circle::Render(vec2 offset) {
  if (status == FREEZED) {
    // draw framw circle
    ci::gl::color(ci::Color(FRAME_COLOR));
    ci::gl::drawSolidCircle(position + offset, 
      radius + FREEZE_FRAME_MARGIN + FREEZE_FRAME_WIDTH);  
    // draw inner circle
    ci::gl::color(ci::Color(BACKGROUND_COLOR));
    ci::gl::drawSolidCircle(position + offset, 
      radius + FREEZE_FRAME_MARGIN);
  }
  ci::gl::color(color);
  ci::gl::drawSolidCircle(position + offset, radius);
}

Shapes Line::GetType() const {
  return LINE;
}

void Line::Render(vec2 offset) {
  ci::gl::color(color);
  ci::gl::drawLine(*from + offset, *to + offset);
}

}// namespace bitcoin