#ifndef HISTOGRAM_H_INCLUDE
#define HISTOGRAM_H_INCLUDE

#include<iostream>
#include<fstream>
#include <string.h>
#include<vector>


using std::cout;
using std::endl; 
using std::string;
using std::vector;



class Server{
public:
void printStuff();
int validPort(string portNum);
int validIP(string ipAddr);
};
#endif