#ifndef HISTOGRAM_H_INCLUDE
#define HISTOGRAM_H_INCLUDE

#include<iostream>
#include<fstream>
#include <string.h>
#include<vector>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <sys/types.h>
#include<unistd.h>
#include<netdb.h>
#include <arpa/inet.h>
#include <bitset> 
using std::cout;
using std::endl; 
using std::string;
using std::vector;
using std::cin;
using std::bitset;

class Server{
struct build{
		int versionNum;
		int messageLenght;
		char* messageText;
	};
	
	
	
public:
void printStuff();
int validPort(string portNum);
int validIP(string ipAddr);
char* pack(char* message, int version);
};
#endif