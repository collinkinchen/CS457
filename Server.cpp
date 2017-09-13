#include "Server.h"

void Server::printStuff(){
	cout << "printStuff" << endl;
}

int Server::validPort(string portNum){
	//cout << "made it to valid port" << endl;
	int portLenght = portNum.length();
	//cout << "port length: " << portLenght << endl;
	for (int i = 0; i < portLenght; i++){
		//cout << portNum[i] << endl;
		if (!(isdigit(portNum[i]))){return 4;}
	}
	return 1;
}

int Server::validIP(string ipAddr){
	//cout << "made it to validIP motherfucker" << endl;
	//char* newIP = strtok(ipAddr,".");
	string tempString = ipAddr;
	int ipLength = ipAddr.length();
	//cout << ipLength << endl;
	if (ipLength > 15 || ipLength < 7){return 5;}
	vector<string> ipNums;
	for(int i =0; i < ipLength; i++){
		int temp = i;
		int count= 0;
		while(ipAddr[i] != '.' && i < ipLength){i++;count++;}
		//cout << "substring: " << tempString.substr(temp,count) << endl;
		
		ipNums.push_back(tempString.substr(temp,count));
	}
	for ( int i=0;i<4;i++){
		//cout << ipNums[i] << endl;
		int ipcheck = validPort(ipNums[i]);
		if (ipcheck == 4){return 5;}
	}
	return 1;

}

