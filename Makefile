OPTIMIZATION=2
STANDARD=c++11
CC=g++ -std=$(STANDARD) -O$(OPTIMIZATION) -Wall

bin/lispino: src/main.o src/Tokenizer.o src/Token.o src/Parser.o src/Lambda.o src/List.o src/Symbol.o src/VM.o src/Environment.o src/Closure.o src/Object.o src/Interpreter.o
	$(CC) -o $@ $^

test: bin/all_tests
	bin/all_tests

bin/all_tests: test/tokenizer_tests.o test/parser_tests.o test/interpreter_tests.o test/main_tests.o src/Tokenizer.o src/Token.o src/Parser.o src/Lambda.o src/List.o src/Symbol.o src/VM.o src/Environment.o src/Closure.o src/Object.o
	$(CC) -o $@ $^ -lgtest -pthread

bin/tokenizer_tests: test/tokenizer_tests.o test/main_tests.o src/Tokenizer.o src/Token.o
	$(CC) -o $@ $^ -lgtest -pthread

bin/parser_tests: test/parser_tests.o test/main_tests.o src/Parser.o src/Tokenizer.o src/Token.o src/Lambda.o src/List.o src/Symbol.o src/VM.o src/Environment.o src/Closure.o src/Object.o
	$(CC) -o $@ $^ -lgtest -pthread

bin/interpreter_tests: test/interpreter_tests.o test/main_tests.o src/Parser.o src/Tokenizer.o src/Token.o src/Lambda.o src/List.o src/Symbol.o src/VM.o src/Environment.o src/Closure.o src/Object.o
	$(CC) -o $@ $^ -lgtest -pthread

src/%.o: src/%.cpp
	$(CC) -c $< -o $@

test/%.o: test/%.cpp
	$(CC) -c $< -o $@

clean:
	rm -rf bin/* src/*.o test/*.o
