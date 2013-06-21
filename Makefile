all:
	g++ -pedantic -o repl -ansi -Wall main.cpp Lexer.cpp LCons.cpp Parser.cpp Environment.cpp LLambda.cpp BuiltinSum.cpp BuiltinProduct.cpp BuiltinDecrement.cpp

tests:
	g++ -pedantic -ansi -Wall tests.cpp
