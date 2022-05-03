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

  template <typename R>
  struct PointMass : Mass<R, DistanceForceConfig> {
    virtual vec2 GetOrigin() override;
    virtual void SetOrigin(Atom*) override;
    virtual void SetOrigin(vec2) override;
  };

  typedef PointMass<struct Circle> Ball;
  typedef PointMass<struct Square> Box;
  typedef Constraint<struct Line, struct StringForceConfig> String;
}