#include "visualizer.h"
#include "renderables.h"
#include "engine.h"

namespace bitcoin {
  BitcoinApp::BitcoinApp() {
    ci::app::setWindowSize(kWindowHeight, kWindowWidth);
    Circle* circle1 = new Circle();
    Circle* circle2 = new Circle();
    // Circle* circle3 = new Circle();
    vec2 position_a(500, 400),
         position_b(300, 400);
        //  position_c(400, 250);
    circle1->radius = 5;
    circle2->radius = 5;
    circle1->color = ci::Color("blue");

    circle1->position = position_a;
    circle2->position = position_b;
    // circle3->position = position_b;

    ForceConfig
      *fa = new StringForceConfig(circle2, circle1, 100, 10, 100),
      *fb = new DistanceForceConfig(circle2, -100, 1000),
      *fc = new DistanceForceConfig(circle1, -100, 1000),
      *fd = new FrictionForceConfig(0.2);

    objects.push_back(circle1);
    objects.push_back(circle2);
    // objects.push_back(circle3);
    
    // engine.AddAtom(circle3);
    engine.AddAtom(circle2);
    engine.AddAtom(circle1);
    engine.AddForce(fa);
    engine.AddForce(fb);
    engine.AddForce(fc);
    engine.AddForce(fd);
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