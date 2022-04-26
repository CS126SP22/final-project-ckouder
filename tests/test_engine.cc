#include <catch2/catch.hpp>
#include "engine.h"

using bitcoin::Atom;
using bitcoin::Engine;

TEST_CASE("Test two atoms") {
  Atom *a = new Atom(), *b = new Atom();
  Engine *e = new Engine();
  float f = 1000;
  e->Add(a);
  e->Add(b);

  a->position = vec2(0, 0);
  b->position = vec2(100, 0);
  a->field = vec2(-f);
  b->field = vec2(-f);
  e->Compute();

  SECTION("two static atoms acceleration") {
    REQUIRE(a->acceleration == vec2(f, 0));
    REQUIRE(b->acceleration == vec2(-f, 0));
  };

  SECTION("two static atoms velocity") {
    REQUIRE(a->velocity == vec2(f / S, 0));
    REQUIRE(b->velocity == vec2(-f / S, 0));
  };

  SECTION("two static atoms position") {
    REQUIRE(a->position == vec2(f / S / S, 0));
    REQUIRE(b->position == vec2(100 - f / S / S, 0));
  };
}