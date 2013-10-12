REPL_NAME=repl
CLANG_OPTIONS=-std=gnu++11 -stdlib=libc++
CC=clang++ $(CLANG_OPTIONS)

all: main.o Tokenizer.o IfExpression.o QuoteExpression.o LambdaExpression.o LCons.o Parser.o Environment.o Repl.o
	$(CC) -o $(REPL_NAME) $^

clean:
	rm *.o $(REPL_NAME)

%.o: %.cpp
	$(CC) -c $^
