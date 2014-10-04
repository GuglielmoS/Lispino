OPTIMIZATION=2
STANDARD=c++11
WARNINGS=-Wall -Wextra -Werror -pedantic -pedantic-errors -Wstrict-aliasing
CC=g++ -std=$(STANDARD) -O$(OPTIMIZATION) $(WARNINGS)

TOKENIZER_OBJS=src/Tokenizer.o src/Token.o src/SourceCodePosition.o

PARSER_OBJS=src/Parser.o src/Object.o src/Nil.o src/Define.o src/Lambda.o src/Character.o src/Boolean.o src/IntNumber.o src/FloatNumber.o src/List.o src/Quote.o src/Symbol.o src/String.o src/VM.o src/Memory.o src/Allocator.o src/Sequence.o src/IfExpr.o

BUILTIN_FUNCTIONS_OBJS=src/builtins/BuiltinFunction.o src/builtins/Add.o src/builtins/Sub.o src/builtins/Mul.o src/builtins/Div.o src/builtins/Remainder.o src/builtins/LowerThan.o src/builtins/LowerEqualThan.o src/builtins/GreaterThan.o src/builtins/GreaterEqualThan.o src/builtins/NumberEqual.o src/builtins/Car.o src/builtins/Cdr.o src/builtins/Cons.o src/builtins/Display.o src/builtins/Set.o src/builtins/Load.o src/builtins/Apply.o src/builtins/NumberPred.o src/builtins/BooleanPred.o src/builtins/PairPred.o src/builtins/SymbolPred.o src/builtins/CharPred.o src/builtins/StringPred.o src/builtins/ProcedurePred.o src/builtins/ListPred.o src/builtins/PromisePred.o src/builtins/And.o src/builtins/Or.o src/builtins/Error.o src/builtins/Eq.o src/builtins/Eqv.o src/builtins/Equal.o src/builtins/Delay.o src/builtins/Force.o src/builtins/LazyCons.o

INTERPRETER_OBJS=src/Closure.o src/Promise.o src/GarbageCollector.o src/Environment.o src/Interpreter.o src/Evaluator.o src/Args.o

UTILS_OBJS=src/utils/List.o src/utils/Token.o

ALL_OBJS=$(TOKENIZER_OBJS) $(PARSER_OBJS) $(BUILTIN_FUNCTIONS_OBJS) $(UTILS_OBJS) $(INTERPRETER_OBJS)

TEST_OBJS=test/tokenizer_tests.o test/parser_tests.o test/interpreter_tests.o 

bin/lispino: src/main.o $(ALL_OBJS) 
	$(CC) -o $@ $^

test: bin/all_tests
	bin/all_tests

bin/all_tests: test/main_tests.o $(TEST_OBJS) $(ALL_OBJS)
	$(CC) -o $@ $^ -lgtest -pthread

src/VM.o: src/VM.cc
	$(CC) -c $< -o $@

src/%.o: src/%.cc src/VM.o
	$(CC) -c $< -o $@

test/%.o: test/%.cc src/VM.o
	$(CC) -c $< -o $@

clean:
	rm -rf bin/lispino bin/all_tests src/*.o src/builtins/*.o src/errors/*.o src/utils/*.o test/*.o
