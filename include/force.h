#pragma once
#include "engine.h"

using glm::vec2;

namespace bitcoin
{
  typedef vec2 Force;

  enum ForceEmitterType {
    DISTANCE,
    STRING,
  };

  class ForceEmitter {
    public:
    bool IsExpired();

    virtual ForceEmitterType GetType();
    virtual bool ShouldTrigger(Atom*);
    virtual void ApplyForce(Atom*);

    protected:
    bool expired = false;
    vec2 magnitude_;

    void SetExpired();
  };

  class DistanceForceEmitter : ForceEmitter {
    public:
    DistanceForceEmitter();

    ForceEmitterType GetType();
    bool ShouldTrigger(Atom*);
    void ApplyForce(Atom*);

    private:
    vec2* origin_;
    float range_;
  };

  class StringForceEmitter : ForceEmitter {
    public:
    StringForceEmitter();

    ForceEmitterType GetType();
    bool ShouldTrigger(Atom*);
    void ApplyForce(Atom*);

    private:
    Atom* a_;
    Atom* b_;
    float min_trigger_;
  };
}