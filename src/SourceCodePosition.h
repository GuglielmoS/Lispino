#ifndef LISPINO_SOURCECODEPOSITION_H_
#define LISPINO_SOURCECODEPOSITION_H_

#include <cstdint>

#include <string>

namespace Lispino {

class SourceCodePosition {
 public:
  SourceCodePosition();

  explicit SourceCodePosition(const std::string&& filename);

  SourceCodePosition(uint32_t line, uint32_t column);

  SourceCodePosition(const std::string&& filename, uint32_t line, uint32_t column);

  void addChar(char ch);

  void removeChar(char ch);

  void removeLastChar();

  std::string getFilename() const;

  uint32_t getLine() const;

  uint32_t getColumn() const;

 private:
  std::string filename;
  uint32_t line;
  uint32_t column;
  uint32_t last_column;
  char last_char;
};
}

#endif // LISPINO_SOURCECODEPOSITION_H_
