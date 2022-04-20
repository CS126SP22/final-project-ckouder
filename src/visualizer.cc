#include "visualizer.h"
#include "renderables.h"

namespace bitcoin {
  BitcoinApp::BitcoinApp() {
    ci::app::setWindowSize(kWindowHeight, kWindowWidth);
    Square* square = new Square();
    Circle* circle = new Circle();
    Line* line = new Line();
    vec2* position_a = new vec2(10),
        * position_b = new vec2(100),
        * velocity_a = new vec2(10),
        * velocity_b = new vec2(-10),
        * accelera_a = new vec2(5),
        * accelera_b = new vec2(-5);
    square->size = vec2(10);
    circle->radius = 5;
    square->position = position_a;
    square->velocity = velocity_a;
    square->acceleration = accelera_a;
    circle->position = position_b;
    circle->velocity = velocity_b;
    circle->acceleration = accelera_b;
    line->position = position_a;
    line->to = position_b;
    objects.push_back(square);
    objects.push_back(circle);
    objects.push_back(line);
  }

  void BitcoinApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
    for (Particle* particle : objects) {
      Render(particle);
    }
  }

  void BitcoinApp::update() {
    for (Particle* particle : objects) {
      engine.Compute(particle);
    }
  }
} // namespace bitcoin