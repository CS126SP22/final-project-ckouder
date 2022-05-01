#pragma once
#include "force.h"
#include "renderables.h"

namespace bitcoin {
  template <typename R, typename F>
  struct Mass : R, F {
    Mass() {};

    protected:
    Mass(Atom* a, Atom* b) : R(a, b), F(a, b) {};
  };

  template <typename R, typename F>
  struct Constraint : Mass<R, F> {
    Constraint(Atom* a, Atom* b) : Mass<R, F>(a, b) {};
  };

  typedef Mass<struct Circle, struct DistanceForceConfig> Ball;
  typedef Mass<struct Square, struct DistanceForceConfig> Box;
  typedef Constraint<struct Line, struct StringForceConfig> String;
}