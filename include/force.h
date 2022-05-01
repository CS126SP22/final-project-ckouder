#pragma once
#include "cinder/gl/gl.h"

using glm::vec2;

namespace bitcoin
{
  struct Atom {
    vec2 position = vec2(0);
    vec2 velocity = vec2(0);
    vec2 acceleration = vec2(0);
  };

  struct ForceConfig {
    bool expired = false;
    
    ForceConfig() {};
    virtual ~ForceConfig() {};

    void TryApply(Atom*);
    virtual bool ShouldTrigger(Atom*);
    virtual void Apply(Atom*);
  };

  struct StringForceConfig : ForceConfig {
    Atom* a = nullptr;
    Atom* b = nullptr;
    float min_length = 50.0f;
    float k = 3.0f;

    StringForceConfig() {};
    StringForceConfig(Atom* a, Atom* b) : a(a), b(b) {};
    StringForceConfig(Atom* a, Atom* b, float min_length, float k)
    : a(a), b(b), min_length(min_length), k(k) {};
    ~StringForceConfig() {};

    bool ShouldTrigger(Atom*);
    void Apply(Atom*);
  };

  struct DistanceForceConfig : ForceConfig {
    vec2* origin;
    float magnitude = 10;
    float range = 100;

    DistanceForceConfig() {};
    DistanceForceConfig(vec2* origin) : origin(origin) {};
    DistanceForceConfig(vec2* origin, float magnitude, float range)
    : origin(origin), magnitude(magnitude), range(range) {};
    ~DistanceForceConfig() {};

    bool ShouldTrigger(Atom*);
    void Apply(Atom*);
  };
}