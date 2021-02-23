Project7: proj7Main.o proj7Tokens.o infixEval_i.o infixEval_c.o 
	g++ -o Project7 proj7Main.o proj7Tokens.o infixEval_i.o infixEval_c.o  

proj7Main.o: proj7Main.cpp proj7Tokens.h
	g++ -c proj7Main.cpp

proj7Tokens.o: proj7Tokens.cpp proj7Tokens.h
	g++ -c proj7Tokens.cpp

infixEval_c.o: infixEval_c.cpp infixEval_c.h
	g++ -c infixEval_c.cpp

infixEval_i.o: infixEval_i.cpp infixEval_i.h
	g++ -c infixEval_i.cpp
clean:
	rm Project7 proj7Main.o proj7Tokens.o infixEval_i.o infixEval_c.o
