chat: Server.o main.o
	g++ -std=c++11 Server.o main.o -o chat
Server.o: Server.cpp Server.h
	g++ -Wall -std=c++11 -g  -I. -c Server.cpp	
main.o: main.cpp Server.h
	g++ -Wall -std=c++11 -g  -I. -c main.cpp

clean:
	rm *.o chat
	
tar:
	tar -cvf KinchenChat.tar *.cpp *.h Makefile README