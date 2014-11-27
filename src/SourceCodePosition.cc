#include "SourceCodePosition.h"


namespace Lispino {

SourceCodePosition::SourceCodePosition()
  : filename("stdin"), line(0), column(0), last_column(0), last_char(0x00) {
  /* DO NOTHING */
}

SourceCodePosition::SourceCodePosition(const std::string&& filename)
  : filename(filename), line(0), column(0), last_column(0), last_char(0x00) {
  /* DO NOTHING */
}

SourceCodePosition::SourceCodePosition(uint32_t line, uint32_t column)
    : filename("stdin"), line(line), column(column), last_char(0x00) {
  /* DO NOTHING */
}

SourceCodePosition::SourceCodePosition(const std::string&& filename, uint32_t line, uint32_t column)
    : filename(filename), line(line), column(column), last_char(0x00) {
  /* DO NOTHING */
}

void SourceCodePosition::addChar(char ch) {
  last_column = column;

  switch (ch) {
    case '\n':
      line++;
      column = 0;
      break;
    default:
      column++;
      break;
  }
}

void SourceCodePosition::removeChar(char ch) {
  switch (ch) {
    case '\n':
      line--;
      column = last_column;
    break;
    default:
      column--;
      break;
  }

  last_char = ch;
}

void SourceCodePosition::removeLastChar() {
  removeChar(last_char);
}

std::string SourceCodePosition::getFilename() const {
  return filename;
}

uint32_t SourceCodePosition::getLine() const {
  return line;
}

uint32_t SourceCodePosition::getColumn() const {
  return column;
}
}
