#include <catch2/catch.hpp>
#include "engine.h"

using bitcoin::Atom;
using bitcoin::Engine;
using bitcoin::DistanceForceConfig;

TEST_CASE("Test two atoms") {
  Atom *a = new Atom(), *b = new Atom();
  Engine *e = new Engine();
  float f = 1000;
  a->position = vec2(0, 0);
  b->position = vec2(100, 0);
  DistanceForceConfig
    *fa = new DistanceForceConfig(a, -f, 1000),
    *fb = new DistanceForceConfig(b, -f, 1000);

  e->AddShape(a);
  e->AddShape(b);

  e->AddForce(fa);
  e->AddForce(fb);
  e->Compute();

  float a_mag = f / 100;
  float v_mag = a_mag / S;
  float s_mag = v_mag / S;
  SECTION("two static atoms acceleration") {
    REQUIRE(a->acceleration == vec2(a_mag, 0));
    REQUIRE(b->acceleration == vec2(-a_mag, 0));
  };

  SECTION("two static atoms velocity") {
    REQUIRE(a->velocity == vec2(v_mag, 0));
    REQUIRE(b->velocity == vec2(-v_mag, 0));
  };

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