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

  enum ForceType {
    STRING,
    DISTANCE,
    FRICTION,
    NA
  };

  struct ForceConfig {
    bool expired = false;
    
    ForceConfig() {};
    virtual ~ForceConfig() {};

    void TryApply(Atom*);
    virtual bool ShouldTrigger(Atom*);
    virtual void Apply(Atom*);
    virtual ForceType GetType();
  };

  struct StringForceConfig : ForceConfig {
    Atom* a = nullptr;
    Atom* b = nullptr;
    float length = 100.0f;
    float k = 10.0f;
    float negk = 100.0f;

    StringForceConfig() {};
    StringForceConfig(Atom* a, Atom* b) : a(a), b(b) {};
    StringForceConfig(Atom* a, Atom* b, float length, float k, float negk)
    : a(a), b(b), length(length), k(k), negk(negk) {};
    ~StringForceConfig() {};

    bool ShouldTrigger(Atom*);
    void Apply(Atom*);
    ForceType GetType();
  };

  struct DistanceForceConfig : ForceConfig {
    float magnitude = -10;
    float range = 100;

    DistanceForceConfig() {};
    DistanceForceConfig(vec2 origin) : origin_(origin) {};
    DistanceForceConfig(vec2 origin, float magnitude, float range)
    : magnitude(magnitude), range(range), origin_(origin) {};
    DistanceForceConfig(Atom* ref, float magnitude, float range)
    : magnitude(magnitude), range(range), ref_(ref) {};
    ~DistanceForceConfig() {};

    bool ShouldTrigger(Atom*);
    void Apply(Atom*);
    vec2 GetOrigin();
    void SetOrigin(Atom*);
    void SetOrigin(vec2);
    ForceType GetType();

    private:
    vec2 origin_ = vec2(0, 0);
    Atom* ref_ = nullptr;
    
  };

  struct FrictionForceConfig : ForceConfig {
    float magnitude = 0.3;

    FrictionForceConfig() {};
    FrictionForceConfig(float magnitude) : magnitude(magnitude) {};
    ~FrictionForceConfig() {};

    bool ShouldTrigger(Atom*);
    void Apply(Atom*);    
    ForceType GetType();
  };
}