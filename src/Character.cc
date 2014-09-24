#include "Character.h"

#include <sstream>

namespace Lispino {

Character::Character() : Object(ObjectType::CHARACTER), value(0x00) {
  // DO NOTHING
}

Character::Character(char value) : Object(ObjectType::CHARACTER), value(value) {
  // DO NOTHING
}

void Character::setValue(char value) {
  this->value = value;
}

char Character::getValue() const {
  return this->value;
}

bool Character::eqv(const Object* obj) const {
  return obj->eqvCharacter(this);
}

bool Character::eqvCharacter(const Character* obj) const {
  return value == obj->value;
}

int Character::compare(const Object* obj) const throw (Errors::RuntimeError) {
  if (obj == this)
    return 0;
  else
    return obj->compareCharacter(this);
}

int Character::compareCharacter(const Character* obj) const throw (Errors::RuntimeError) {
  if (obj->value == value)
    return 0;
  else if (obj->value > value)
    return 1;
  else
    return -1;
}

std::string Character::toString() const {
  std::stringstream buf;
  buf << "#\\" << value;
  return buf.str();
}

}
