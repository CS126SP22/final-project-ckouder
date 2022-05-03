#include "mass.h"

// TODO: Refractor code
namespace bitcoin {
  template<>
  vec2 Ball::GetOrigin() {
    return position;
  }

  template<>
  void Ball::SetOrigin(Atom* ref) {
    position = ref->position;
  }

  template<>
  void Ball::SetOrigin(vec2 origin) {
    position = origin;
  }

  template<>
  vec2 Box::GetOrigin() {
    return position;
  }

  template<>
  void Box::SetOrigin(Atom* ref) {
    position = ref->position;
  }

  template<>
  void Box::SetOrigin(vec2 origin) {
    position = origin;
  }
}