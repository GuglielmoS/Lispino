#ifndef LISPINO_CHARACTER_H_
#define LISPINO_CHARACTER_H_

#include "Object.h"

namespace lispino {

class Character : public Object {
 public:
  Character();

  explicit Character(char value);

  void setValue(char value);

  char getValue() const;

  bool eqv(const Object* obj) const override;

  bool eqvCharacter(const Character* obj) const override;

  int compare(const Object* obj) const throw(errors::RuntimeError) override;

  int compareCharacter(const Character* obj) const throw(errors::RuntimeError) override;

  std::string toString() const override;

 private:
  char value;
};
}

#endif // LISPINO_CHARACTER_H_
