#include "visualizer.h"
#include "renderables.h"

namespace bitcoin {
  BitcoinApp::BitcoinApp() {
    ci::app::setWindowSize(kWindowHeight, kWindowWidth);
  }

  void BitcoinApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);

    Square square;
    square.size = vec2(5);

    Circle circle;
    circle.radius = 5;

    Render(&square, vec2(10));
    Render(&circle, vec2(100));
  }

  void BitcoinApp::update() {

  }
} // namespace bitcoin