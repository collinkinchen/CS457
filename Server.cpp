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

char* Server::pack(char* message, int version){
	int messageLen = strlen(message);
	cout << "MESSAGE: "  << message << endl;
	cout << "MESSAGE LENGTH: "  << messageLen << endl;
	cout << "VERSION: " << version << endl;
	//cout << "VERSION in hex: " <<  << endl;
	// unsigned char test[16];
	// unsigned char *buffer = test;
	// unsigned int i;
	// *buffer++ = version>>i;
	// *buffer++ = i;
	bitset<8> version;
	version.set();
	cout << "version in hex: " << version << endl;
	//cout << "VERSION in htons: " << htons(htons(version)) << endl;
	bool loop = true;
	if (strlen(message) > 140){
		while(loop){
		cout << "Message not sent: length exceeds 140 characters" << endl;
		cout << "You: ";
		cin.getline (message,256);
		if (strlen(message) <= 140){
			loop = false;
		}
		}
	}
	return message;

}
