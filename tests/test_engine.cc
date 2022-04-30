#include <catch2/catch.hpp>
#include "engine.h"

using bitcoin::Atom;
using bitcoin::Force;
using bitcoin::Engine;

TEST_CASE("Test two atoms") {
  Atom *a = new Atom(), *b = new Atom();
  Engine *e = new Engine();
  Force *fa = new Force(),
        *fb = new Force();
  float f = 1000;
  e->Add(a);
  e->Add(b);

  a->position = vec2(0, 0);
  b->position = vec2(100, 0);
  fa->SetPosition(&a->position);
  fb->SetPosition(&b->position);
  fa->magnitude = vec2(-f);
  fb->magnitude = vec2(-f);
  a->forces.push_back(fa);
  a->forces.push_back(fb);
  b->forces.push_back(fa);
  b->forces.push_back(fb);
  e->Compute();

  float a_mag = f / 100;
  SECTION("two static atoms acceleration") {
    REQUIRE(a->acceleration == vec2(a_mag, 0));
    REQUIRE(b->acceleration == vec2(-a_mag, 0));
  };

  float v_mag = a_mag / S;
  SECTION("two static atoms velocity") {
    REQUIRE(a->velocity == vec2(v_mag, 0));
    REQUIRE(b->velocity == vec2(-v_mag, 0));
  };

  float s_mag = v_mag / S;
  SECTION("two static atoms position") {
    REQUIRE(a->position == vec2(s_mag, 0));
    REQUIRE(b->position == vec2(100 - s_mag, 0));
  };

  a->position = vec2(0, 0);
  b->position = vec2(100, 0);
  a->velocity = vec2(-10, 0);
  b->velocity = vec2(10, 0);
  a->acceleration = vec2(0);
  b->acceleration = vec2(0);
  e->Compute();

  SECTION("two opposite moving atoms acceleration") {
    REQUIRE(a->acceleration == vec2(a_mag, 0));
    REQUIRE(b->acceleration == vec2(-a_mag, 0));
  };

  SECTION("two static atoms velocity") {
    REQUIRE(a->velocity == vec2(-10 + v_mag, 0));
    REQUIRE(b->velocity == vec2(10 - v_mag, 0));
  };

  SECTION("two static atoms position") {
    REQUIRE(a->position == vec2((-10 + v_mag) / S, 0));
    REQUIRE(b->position == vec2(100 + (10 - v_mag) / S, 0));
  };
}