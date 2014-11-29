OPTIMIZATION=2
STANDARD=c++11
WARNINGS=-Wall -Wextra -Werror -pedantic -pedantic-errors -Wstrict-aliasing
CC=g++ -std=$(STANDARD) -O$(OPTIMIZATION) $(WARNINGS)

TOKENIZER_OBJS=lispino/Tokenizer.o lispino/Token.o lispino/SourceCodePosition.o

PARSER_OBJS=lispino/Parser.o lispino/Object.o lispino/Nil.o lispino/Define.o lispino/Lambda.o lispino/Character.o lispino/Boolean.o lispino/Number.o lispino/IntNumber.o lispino/FloatNumber.o lispino/List.o lispino/Quote.o lispino/Symbol.o lispino/String.o lispino/VM.o lispino/Memory.o lispino/Allocator.o lispino/Sequence.o lispino/IfExpr.o

BUILTIN_FUNCTIONS_OBJS=lispino/builtins/BuiltinFunction.o lispino/builtins/Add.o lispino/builtins/Sub.o lispino/builtins/Mul.o lispino/builtins/Div.o lispino/builtins/Remainder.o lispino/builtins/LowerThan.o lispino/builtins/LowerEqualThan.o lispino/builtins/GreaterThan.o lispino/builtins/GreaterEqualThan.o lispino/builtins/NumberEqual.o lispino/builtins/Car.o lispino/builtins/Cdr.o lispino/builtins/Cons.o lispino/builtins/Display.o lispino/builtins/Set.o lispino/builtins/Load.o lispino/builtins/Apply.o lispino/builtins/NumberPred.o lispino/builtins/BooleanPred.o lispino/builtins/PairPred.o lispino/builtins/SymbolPred.o lispino/builtins/CharPred.o lispino/builtins/StringPred.o lispino/builtins/ProcedurePred.o lispino/builtins/ListPred.o lispino/builtins/PromisePred.o lispino/builtins/And.o lispino/builtins/Or.o lispino/builtins/Error.o lispino/builtins/Eq.o lispino/builtins/Eqv.o lispino/builtins/Equal.o lispino/builtins/Delay.o lispino/builtins/Force.o lispino/builtins/LazyCons.o lispino/builtins/SetCar.o lispino/builtins/SetCdr.o

INTERPRETER_OBJS=lispino/Closure.o lispino/Promise.o lispino/GarbageCollector.o lispino/Environment.o lispino/Interpreter.o lispino/Evaluator.o lispino/Args.o

UTILS_OBJS=lispino/utils/List.o lispino/utils/Token.o lispino/utils/Object.o

ALL_OBJS=$(TOKENIZER_OBJS) $(PARSER_OBJS) $(BUILTIN_FUNCTIONS_OBJS) $(UTILS_OBJS) $(INTERPRETER_OBJS)

TEST_OBJS=test/tokenizer_tests.o test/parser_tests.o test/interpreter_tests.o 

bin/lispino: lispino/main.o $(ALL_OBJS) 
	$(CC) -o $@ $^

test: bin/all_tests
	bin/all_tests

bin/all_tests: test/main_tests.o $(TEST_OBJS) $(ALL_OBJS)
	$(CC) -o $@ $^ -lgtest -pthread

lispino/VM.o: lispino/VM.cc
	$(CC) -c $< -o $@

lispino/%.o: lispino/%.cc lispino/VM.o
	$(CC) -c $< -o $@

test/%.o: test/%.cc lispino/VM.o
	$(CC) -c $< -o $@

clean:
	rm -rf bin/lispino bin/all_tests lispino/*.o lispino/builtins/*.o lispino/errors/*.o lispino/utils/*.o test/*.o
