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

    Line line;

    vec2 a(10), b(100);
    square.position = &a;
    circle.position = &b;
    line.position = &a;
    line.to = &b;

    Render(&square);
    Render(&circle);
    Render(&line);
  }

  void BitcoinApp::update() {

  }
} // namespace bitcoin