#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace bitcoin
{

class BitcoinApp : public ci::app::App {
 public:
  BitcoinApp();

  void draw() override;
  void update() override;

 private:
  const int kWindowHeight = 800;
  const int kWindowWidth = 600;
  ci::Color frame_color = ci::Color("white");
};

} // namespace bitcoin
