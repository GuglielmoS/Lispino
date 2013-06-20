all:
	g++ -pedantic -o repl -ansi -Wall main.cpp Environment.cpp LLambda.cpp

tests:
	g++ -pedantic -ansi -Wall tests.cpp
