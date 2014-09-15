OPTIMIZATION=3
STANDARD=c++11
CC=g++ -std=$(STANDARD) -O$(OPTIMIZATION) -Wall -Wextra -pedantic -pedantic-errors -Wstrict-aliasing

bin/lispino: src/main.o src/Tokenizer.o src/Token.o src/Parser.o src/Object.o src/Nil.o src/Define.o src/Lambda.o src/Boolean.o src/IntNumber.o src/FloatNumber.o src/List.o src/Quote.o src/Symbol.o src/String.o src/VM.o src/Memory.o src/Allocator.o src/GarbageCollector.o src/Environment.o src/Closure.o src/Interpreter.o src/Sequence.o src/IfExpr.o src/builtins/BuiltinFunction.o src/builtins/Add.o src/builtins/Sub.o src/builtins/Mul.o src/builtins/Div.o src/builtins/Remainder.o src/builtins/LowerThan.o src/builtins/LowerEqualThan.o src/builtins/GreaterThan.o src/builtins/GreaterEqualThan.o src/builtins/Equal.o src/builtins/Car.o src/builtins/Cdr.o src/builtins/Cons.o src/builtins/Display.o src/builtins/Set.o
	$(CC) -o $@ $^

test: bin/all_tests
	bin/all_tests

bin/all_tests: test/tokenizer_tests.o test/parser_tests.o test/interpreter_tests.o test/main_tests.o src/Tokenizer.o src/Token.o src/Parser.o src/Object.o src/Nil.o src/Define.o src/Lambda.o src/Boolean.o src/IntNumber.o src/FloatNumber.o src/List.o src/Quote.o src/Symbol.o src/String.o src/VM.o src/Memory.o src/GarbageCollector.o src/Allocator.o src/Environment.o src/Closure.o src/Sequence.o src/IfExpr.o src/builtins/BuiltinFunction.o src/builtins/Add.o src/builtins/Sub.o src/builtins/Mul.o src/builtins/Div.o src/builtins/Remainder.o src/builtins/LowerThan.o src/builtins/LowerEqualThan.o src/builtins/GreaterThan.o src/builtins/GreaterEqualThan.o src/builtins/Equal.o src/builtins/Car.o src/builtins/Cdr.o src/builtins/Cons.o src/builtins/Display.o src/builtins/Set.o
	$(CC) -o $@ $^ -lgtest -pthread

bin/tokenizer_tests: test/tokenizer_tests.o test/main_tests.o src/Tokenizer.o src/Token.o
	$(CC) -o $@ $^ -lgtest -pthread

bin/parser_tests: test/parser_tests.o test/main_tests.o src/Parser.o src/Tokenizer.o src/Token.o src/Object.o src/Nil.o src/Define.o src/Lambda.o src/Boolean.o src/IntNumber.o src/FloatNumber.o src/List.o src/Quote.o src/Symbol.o src/String.o src/VM.o src/Memory.o src/GarbageCollector.o src/Allocator.o src/Environment.o src/Closure.o src/Sequence.o src/IfExpr.o src/builtins/BuiltinFunction.o src/builtins/Add.o src/builtins/Sub.o src/builtins/Mul.o src/builtins/Div.o src/builtins/Remainder.o src/builtins/LowerThan.o src/builtins/LowerEqualThan.o src/builtins/GreaterThan.o src/builtins/GreaterEqualThan.o src/builtins/Equal.o src/builtins/Car.o src/builtins/Cdr.o src/builtins/Cons.o src/builtins/Display.o src/builtins/Set.o
	$(CC) -o $@ $^ -lgtest -pthread

bin/interpreter_tests: test/interpreter_tests.o test/main_tests.o src/Parser.o src/Tokenizer.o src/Token.o src/Object.o src/Nil.o src/Boolean.o src/Define.o src/Lambda.o src/IntNumber.o src/FloatNumber.o src/List.o src/Quote.o src/Symbol.o src/String.o src/VM.o src/Memory.o src/GarbageCollector.o src/Allocator.o src/Environment.o src/Closure.o src/Sequence.o src/IfExpr.o src/builtins/BuiltinFunction.o src/builtins/Add.o src/builtins/Sub.o src/builtins/Mul.o src/builtins/Div.o src/builtins/Remainder.o src/builtins/LowerThan.o src/builtins/LowerEqualThan.o src/builtins/GreaterThan.o src/builtins/GreaterEqualThan.o src/builtins/Equal.o src/builtins/Car.o src/builtins/Cdr.o src/builtins/Cons.o src/builtins/Display.o src/builtins/Set.o
	$(CC) -o $@ $^ -lgtest -pthread

src/VM.o: src/VM.cc
	$(CC) -c $< -o $@

src/%.o: src/%.cc src/VM.o
	$(CC) -c $< -o $@

test/%.o: test/%.cc src/VM.o
	$(CC) -c $< -o $@

clean:
	rm -rf bin/lispino bin/all_tests src/*.o src/builtins/*.o test/*.o
