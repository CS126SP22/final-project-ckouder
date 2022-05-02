#include "visualizer.h"
#include "renderables.h"
#include "engine.h"
#include "mass.h"

namespace bitcoin {
  BitcoinApp::BitcoinApp() {
    ci::app::setWindowSize(kWindowHeight, kWindowWidth);
    Ball* ball1 = new Ball(),
        * ball2 = new Ball();
    String* string = new String(ball1, ball2);
    ForceConfig *fd = new FrictionForceConfig(0.2);
    vec2 position_a(500, 400),
         position_b(300, 400);
    ball1->radius = 5;
    ball2->radius = 5;

    ball1->position = position_a;
    ball2->position = position_b;

    string->color = ci::Color("white");
    ball1->color = ci::Color("blue");
    ball2->color = ci::Color("green");
    ball1->status = FREEZED;

    objects_.push_back(ball1);
    objects_.push_back(ball2);
    objects_.push_back(string);

    engine_.AddMass(string);
    engine_.AddMass(ball1);
    engine_.AddMass(ball2);
    engine_.AddForce(fd);
  }

  void BitcoinApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
    for (Shape* object : objects_) {
      object->Render();
    }
  }

  void BitcoinApp::update() {
    engine_.Compute();
  }
} // namespace bitcoin