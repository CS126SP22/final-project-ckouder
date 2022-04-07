#include "visualizer.h"

namespace bitcoin {
  BitcoinApp::BitcoinApp() {
    ci::app::setWindowSize(800, 600);
  }

  void BitcoinApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
  }

  void BitcoinApp::update() {

  }
} // namespace bitcoin