OPTIMIZATION=3
STANDARD=c++11
CC=g++ -std=$(STANDARD) -O$(OPTIMIZATION) -Wall

bin/lispino: src/main.o src/Tokenizer.o src/Token.o src/Parser.o src/Object.o src/Lambda.o src/IntNumber.o src/FloatNumber.o src/List.o src/Symbol.o src/String.o src/VM.o src/Environment.o src/Closure.o src/Interpreter.o src/Sequence.o src/builtin/Add.o src/builtin/Sub.o src/builtin/Mul.o src/builtin/Div.o src/builtin/Remainder.o src/builtin/LowerThan.o src/builtin/LowerEqualThan.o src/builtin/GreaterThan.o src/builtin/GreaterEqualThan.o src/builtin/Equal.o src/builtin/NullPredicate.o src/builtin/TruePredicate.o src/builtin/FalsePredicate.o src/builtin/Car.o src/builtin/Cdr.o src/builtin/Cons.o
	$(CC) -o $@ $^

test: bin/all_tests
	bin/all_tests

bin/all_tests: test/tokenizer_tests.o test/parser_tests.o test/interpreter_tests.o test/main_tests.o src/Tokenizer.o src/Token.o src/Parser.o src/Object.o src/Lambda.o src/IntNumber.o src/FloatNumber.o src/List.o src/Symbol.o src/String.o src/VM.o src/Environment.o src/Closure.o src/Sequence.o src/builtin/Add.o src/builtin/Sub.o src/builtin/Mul.o src/builtin/Div.o src/builtin/Remainder.o src/builtin/LowerThan.o src/builtin/LowerEqualThan.o src/builtin/GreaterThan.o src/builtin/GreaterEqualThan.o src/builtin/Equal.o src/builtin/NullPredicate.o src/builtin/TruePredicate.o src/builtin/FalsePredicate.o src/builtin/Car.o src/builtin/Cdr.o src/builtin/Cons.o
	$(CC) -o $@ $^ -lgtest -pthread

bin/tokenizer_tests: test/tokenizer_tests.o test/main_tests.o src/Tokenizer.o src/Token.o
	$(CC) -o $@ $^ -lgtest -pthread

bin/parser_tests: test/parser_tests.o test/main_tests.o src/Parser.o src/Tokenizer.o src/Token.o src/Object.o osrc/Lambda.o src/IntNumber.o src/FloatNumber.o src/List.o src/Symbol.o src/String.o src/VM.o src/Environment.o src/Closure.o src/Sequence.o src/builtin/Add.o src/builtin/Sub.o src/builtin/Mul.o src/builtin/Div.o src/builtin/Remainder.o src/builtin/LowerThan.o src/builtin/LowerEqualThan.o src/builtin/GreaterThan.o src/builtin/GreaterEqualThan.o src/builtin/Equal.o src/builtin/NullPredicate.o src/builtin/TruePredicate.o src/builtin/FalsePredicate.o src/builtin/Car.o src/builtin/Cdr.o src/builtin/Cons.o
	$(CC) -o $@ $^ -lgtest -pthread

bin/interpreter_tests: test/interpreter_tests.o test/main_tests.o src/Parser.o src/Tokenizer.o src/Token.o src/Object.o src/Lambda.o src/IntNumber.o src/FloatNumber.o src/List.o src/Symbol.o src/String.o src/VM.o src/Environment.o src/Closure.o src/Sequence.o src/builtin/Add.o src/builtin/Sub.o src/builtin/Mul.o src/builtin/Div.o src/builtin/Remainder.o src/builtin/LowerThan.o src/builtin/LowerEqualThan.o src/builtin/GreaterThan.o src/builtin/GreaterEqualThan.o src/builtin/Equal.o src/builtin/NullPredicate.o src/builtin/TruePredicate.o src/builtin/FalsePredicate.o src/builtin/Car.o src/builtin/Cdr.o src/builtin/Cons.o
	$(CC) -o $@ $^ -lgtest -pthread

src/VM.o: src/VM.cpp
	$(CC) -c $< -o $@

src/%.o: src/%.cpp src/VM.o
	$(CC) -c $< -o $@

test/%.o: test/%.cpp src/VM.o
	$(CC) -c $< -o $@

clean:
	rm -rf bin/* src/*.o src/builtin/*.o test/*.o
