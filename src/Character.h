#ifndef LISPINO_CHARACTER_H_
#define LISPINO_CHARACTER_H_

#include "Object.h"

namespace Lispino {

class Character : public Object {
 public:
  Character();

  Character(char value);

  void setValue(char value);

  char getValue() const;

  int compare(const Object* obj) const throw (Errors::RuntimeError) override;

  int compareCharacter(const Character* obj) const throw (Errors::RuntimeError) override;

  std::string toString() const override;

 private:
  char value;
};

}

#endif // LISPINO_CHARACTER_H_