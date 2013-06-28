REPL_NAME=repl
CLANG_OPTIONS=-std=gnu++11 -stdlib=libc++ -Weverything
CC=clang++ $(CLANG_OPTIONS)

all: main.o LObject.o LNilObject.o Lexer.o LAtom.o LCons.o LLambda.o BuiltinSum.o BuiltinProduct.o BuiltinDecrement.o BuiltinCar.o BuiltinCdr.o Parser.o Environment.o
	$(CC) -o $(REPL_NAME) $^

clean:
	rm *.o $(REPL_NAME)

%.o: %.cpp
	$(CC) -c $^
