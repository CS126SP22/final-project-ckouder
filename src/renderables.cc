#include "renderables.h"
#include "config.h"

using cinder::Rectf;

#define FREEZE_FRAME_WIDTH 1
#define FREEZE_FRAME_MARGIN 1

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
  if (status == FREEZED) {
    // draw frame square
    ci::gl::color(ci::Color(FRAME_COLOR));
    ci::gl::drawSolidRect(Rectf(
      position - size / vec2(2) - vec2(FREEZE_FRAME_MARGIN + FREEZE_FRAME_WIDTH),
      position + size / vec2(2) + vec2(FREEZE_FRAME_MARGIN + FREEZE_FRAME_WIDTH)
    ));
    // draw inner square
    ci::gl::color(ci::Color(BACKGROUND_COLOR));
    ci::gl::drawSolidRect(Rectf(
      position - size / vec2(2) - vec2(FREEZE_FRAME_MARGIN),
      position + size / vec2(2) + vec2(FREEZE_FRAME_MARGIN)
    ));
  }
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
  if (status == FREEZED) {
    // draw framw circle
    ci::gl::color(ci::Color(FRAME_COLOR));
    ci::gl::drawSolidCircle(position, 
      radius + FREEZE_FRAME_MARGIN + FREEZE_FRAME_WIDTH);  
    // draw inner circle
    ci::gl::color(ci::Color(BACKGROUND_COLOR));
    ci::gl::drawSolidCircle(position, 
      radius + FREEZE_FRAME_MARGIN);
  }
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