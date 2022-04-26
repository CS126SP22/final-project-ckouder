#include "visualizer.h"
#include "renderables.h"

namespace bitcoin {
  BitcoinApp::BitcoinApp() {
    ci::app::setWindowSize(kWindowHeight, kWindowWidth);
    Circle* circle1 = new Circle();
    Circle* circle2 = new Circle();
    Circle* circle3 = new Circle();
    // Line* line = new Line();
    vec2 position_a(500, 400),
        //  position_b(400, 400),
         position_b(300, 400);
        //  velocity_a(0.01),
        //  velocity_b(-0.01);
        //  accelera_a(5),
        //  accelera_b(-5);
    circle1->radius = 5;
    circle2->radius = 5;
    circle3->radius = 5;
    // circle1->position = position_b;
    circle2->position = position_a;
    circle3->position = position_b;
    // circle2->velocity = velocity_a;
    // circle3->velocity = velocity_b;
    // square->velocity = velocity_a;
    // square->acceleration = accelera_a;
    // circle->velocity = velocity_b;
    // circle->acceleration = accelera_b;
    // line->position = position_a;
    // line->to = position_b;
    // objects.push_back(circle1);
    objects.push_back(circle2);
    objects.push_back(circle3);
    
    // engine.Add(circle1);
    engine.Add(circle3);
    engine.Add(circle2);
  }

  void BitcoinApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
    for (Renderable* Renderable : objects) {
      Render(Renderable);
    }
  }

  void BitcoinApp::update() {
    engine.Compute();
  }
} // namespace bitcoin