#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "engine.h"
#include "renderables.h"
#include "config.h"

namespace bitcoin
{

class BitcoinApp : public ci::app::App {
 public:
  BitcoinApp();

  void draw() override;
  void update() override;

 private:
  const int kWindowHeight = WINDOW_HEIGHT;
  const int kWindowWidth = WINDOW_WIDTH;
  const ci::Color kFrameColor = ci::Color(FRAME_COLOR);
  const ci::Color kBackgroundColor = ci::Color(BACKGROUND_COLOR);
  Engine engine_ = Engine();
  std::vector<Shape*> objects_;
};

} // namespace bitcoin
