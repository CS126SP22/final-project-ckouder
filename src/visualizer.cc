#include "visualizer.h"
#include "renderables.h"
#include "engine.h"
#include "mass.h"

namespace bitcoin {
  BitcoinApp::BitcoinApp() {
    ci::app::setWindowSize(kWindowHeight, kWindowWidth);
    Ball* ball1 = new Ball(),
        * ball2 = new Ball(),
        * ball3 = new Ball(),
        * ball4 = new Ball();
    String* string1 = new String(ball1, ball2),
          * string2 = new String(ball1, ball3),
          * string3 = new String(ball1, ball4);
    ForceConfig *fd = new FrictionForceConfig(0.2);
    vec2 position_a(500, 400),
         position_b(300, 400),
         position_c(400, 400),
         position_d(400, 300);
    ball1->radius = 5;
    ball2->radius = 5;
    ball3->radius = 5;
    ball4->radius = 5;

    ball1->position = position_a;
    ball2->position = position_b;
    ball3->position = position_c;
    ball4->position = position_d;

    ball1->magnitude = 1000;
    ball2->magnitude = 1000;
    ball3->magnitude = 1000;
    ball4->magnitude = 1000;

    string1->color = ci::Color("white");
    string2->color = ci::Color("white");
    string3->color = ci::Color("white");
    string1->length = 10;
    string2->length = 10;
    string3->length = 10;
    ball1->color = ci::Color("blue");
    ball2->color = ci::Color("green");
    ball3->color = ci::Color("pink");

    objects_.push_back(ball1);
    objects_.push_back(ball2);
    objects_.push_back(ball3);
    objects_.push_back(ball4);
    objects_.push_back(string1);
    objects_.push_back(string2);
    objects_.push_back(string3);

    engine_.AddMass(string1);
    engine_.AddMass(string2);
    engine_.AddMass(string3);
    engine_.AddMass(ball1);
    engine_.AddMass(ball2);
    engine_.AddMass(ball3);
    engine_.AddMass(ball4);
    engine_.AddForce(fd);
  }

  void BitcoinApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
    for (Shape* object : objects_) {
      object->Render(drag_acc_);
    }
  }

  void BitcoinApp::update() {
    engine_.Compute();
  }

  void BitcoinApp::mouseDown(MouseEvent event) {
    Shape* target = FindShapeAtPos(GetRealShapePos(event.getPos()));
    if (target != nullptr) {
      if (event.isLeft()) {
        target->status = FREEZED;
      } else if (event.isRight()) {
        target->status = ACTIVE;
      }
    }
  }

  void BitcoinApp::mouseMove(MouseEvent event) {
    drag_ = event.getPos();
  }

  void BitcoinApp::mouseDrag(MouseEvent event) {
    Shape* target = FindShapeAtPos(GetRealShapePos(event.getPos()));
    if (target != nullptr) {
      target->status = FREEZED;
      target->position = GetRealShapePos(event.getPos());
    } else {
      drag_acc_ += event.getPos() - drag_;
      drag_ = event.getPos();
    }
  }

  void BitcoinApp::mouseWheel(MouseEvent event) {
    // scale view
  }

  Shape* BitcoinApp::FindShapeAtPos(const vec2 & coordinate) {
    for (Shape* object : objects_) {
      if (glm::length(coordinate - object->position) <= kTolerance) {
        return object;
      }
    }
    return nullptr;
  }

  ivec2 BitcoinApp::GetRealShapePos(const ivec2 & position) {
    return position - drag_acc_;
  }
} // namespace bitcoin