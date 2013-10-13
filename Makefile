REPL_NAME=repl
CLANG_OPTIONS=-std=gnu++11 -stdlib=libc++
CC=clang++ $(CLANG_OPTIONS)

all: LCons.o IfExpression.o QuoteExpression.o LambdaExpression.o Closure.o DefineExpression.o BuiltinSum.o BuiltinSub.o BuiltinMul.o BuiltinDiv.o BuiltinEqual.o BuiltinCar.o BuiltinCdr.o Environment.o Tokenizer.o Parser.o Repl.o main.o
	$(CC) -o $(REPL_NAME) $^

%.o: %.cpp
	$(CC) -c $<

clean:
	rm *.o $(REPL_NAME)

