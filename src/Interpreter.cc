#include "Interpreter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

#include "Parser.h"
#include "VM.h"

namespace Lispino {

void Interpreter::init() {
  // try to load the standard library
  execute(LIB_DIR + "/" + STDLIB_FILE);

  // try to load the unit testing library
  execute(LIB_DIR + "/" + TESTLIB_FILE);
}

int Interpreter::repl(bool verbose) {
  bool terminated = false;

  // Read - Eval - Print - Loop
  while (not terminated) {
    std::string input_expr;

    // gets the expression
    std::cout << "> ";
    std::getline(std::cin, input_expr);

    // evaluates the expression
    if (input_expr == "quit") {
      terminated = true;
    } else if (input_expr != "") {
      clock_t begin, end;
      double total_time, parsing_time, evaluation_time, garbage_collection_time;
      std::stringstream stream(input_expr);

      // *** PARSING ***
      begin = clock();
      Object *expr = Parser(stream).parse();
      end = clock();
      parsing_time = (double)(end - begin) / CLOCKS_PER_SEC;

      // *** EVALUATION ***
      begin = clock();
      std::cout << expr->eval()->toString() << std::endl;
      end = clock();
      evaluation_time = (double)(end - begin) / CLOCKS_PER_SEC;

      // *** GARBAGE COLLECTION ***
      size_t total_objects = VM::getMemory().getAllocatedObjects();
      begin = clock();
      size_t removed_objects = VM::getMemory().cleanup();
      end = clock();
      garbage_collection_time = (double)(end - begin) / CLOCKS_PER_SEC;

      // calculate the total execution time
      total_time = parsing_time + evaluation_time + garbage_collection_time;

      // shows the time
      if (verbose) {
        std::cout << ";; Timing report" << std::endl;
        std::cout << "     + Parsing Time:            " << parsing_time << std::endl;
        std::cout << "     + Evaluation Time:         " << evaluation_time << std::endl;
        std::cout << "     + Garbage Collection Time: " << garbage_collection_time << std::endl;
        std::cout << "     = Total Time:              " << total_time << std::endl;
        std::cout << ";; Memory report" << std::endl;
        std::cout << "     Garbage collected objects " <<  removed_objects << "/" << total_objects << std::endl;
      }
    }
  }

  return 0;
}

int Interpreter::execute(std::string filename) {
  std::ifstream input_stream(filename);

  if (input_stream.is_open()) {
    Parser parser(input_stream);

    Object *current_expr = nullptr;
    while ((current_expr = parser.parseExpr()) != nullptr) {
      // evaluate the current expression
      current_expr->eval()->toString();

      // run the garbage collector
      VM::getMemory().cleanup();
    }

    input_stream.close();

    return 0;
  }
  else {
    std::cerr << "File not found: " << filename << std::endl;
    return 1;
  }
}

std::string Interpreter::humanTime(double time_spent) {
  std::stringstream buf;
  std::string unit;

  if (time_spent > 0.001)
  unit = "secs";
  else if (time_spent > 0.000001) {
  time_spent *= 1000.0;
  unit = "ms";
  }
  else if (time_spent > 0.000000001) {
  time_spent *= 1000000.0;
  unit = "us";
  }
  else {
  time_spent *= 1000000000.0;
  unit = "ns";
  }

  buf << time_spent << " " << unit;

  return buf.str();
}

}
