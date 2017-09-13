#include "Server.h"
#include <iostream> 
using std::cout;
using std::endl;
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
using std::ifstream;
using std::cerr;
using std::string;
#define MYPORT "3490"

//struct sockaddr_in{
//unsigned short sin_family;/* Internet protocol (AF_INET) */
//unsigned short sin_port;  /* Address port (16 bits) */
//struct in_addr sin_addr; /* Internet address (32 bits) */
//char sin_zero[8];       /* Not used */
//}



int errorMessage(int i) 
{  
	switch(i){
		case 1: cerr << "Error: Wrong number of argumants" << endl; break;
		case 2: cerr << "Error: Incorrect argument. expected -h" << endl; break;
		case 3: cerr << "Error: Incorrect argument. expected -p and -s" << endl; break;
		case 4: cerr << "Error: port argument expects number" << endl; break;
		case 5: cerr << "Error: Server IP is incorrect" << endl; break;
		case 6: cerr << "Error: Problem with sockets" << endl; break;
	}
	return -1;
}


int main(int argc, char* argv[]){
	//cout << "main stuff" << endl;
	Server s1;
	//s1.printStuff();
	// int portStatus = s1.validPort(argv[2]);
	if (argc == 1 || argc == 2 || argc == 5){
	if (argc == 2){
		string helpCheck = argv[1];
		if (helpCheck == ("-h")){
			cout << "HELP: Please run the program as:\n SERVER: ./chat\n CLIENT: ./chat -p <port number> -s <server IP address>" << endl;
		}else{return errorMessage(2);}
	}
	else if (argc == 1){ //handle 1
			// socket() create socket
			int newSocket = socket(PF_INET,SOCK_STREAM,0);
			if (newSocket < 0){return errorMessage(6);}
			// cout << newSocket << endl;
			// bind()
			struct sockaddr_in ServAddr;
			ServAddr.sin_family = AF_INET; /* Internet address family */
			ServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface ServAddr.*/
			ServAddr.sin_port = htons(8080); /* Local port ###JUST GIVEN RANDOM AT THE MOMENT###*/
			int testBind = bind(newSocket,(struct sockaddr *)&ServAddr, sizeof(ServAddr));
			if (testBind < 0){return errorMessage(6);}
			// listen()
			#define MAXPENDING 5
			int testListen = listen(newSocket,MAXPENDING);
			cout << testListen << endl;
			if (testBind < 0){return errorMessage(6);}
			// accept()
			struct sockaddr_storage their_addr;
			socklen_t addr_size ;
			
			addr_size = sizeof their_addr;
			int testAccept = accept(newSocket, (sockaddr *) &their_addr, &addr_size);
			cout << "TEST ACCEPT" << testAccept << endl;
			//int clientSock=accept(newSocket,(structsockaddr*)&ClntAddr,&clntLen)
			//cout << "CLIENT SOCK: " << clientSock << endl;
			// while still open
				// recv()
				// send()

// struct sockaddr_storage their_addr;
    // socklen_t addr_size;
    // struct addrinfo hints, *res;
    // int sockfd, new_fd;

    // memset(&hints, 0, sizeof hints);
    // hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    // hints.ai_socktype = SOCK_STREAM;
    // hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    // getaddrinfo(NULL, MYPORT, &hints, &res);


    // sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    // bind(sockfd, res->ai_addr, res->ai_addrlen);
    // listen(sockfd, 5);


    // addr_size = sizeof their_addr;
    // new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

	}
	else{//handle 5
		string arg1 = argv[1];
		string arg3 = argv[3];
		if ((arg1 == "-p" || arg1 == "-s")){
			if ((arg3 == "-p" || arg3 == "-s")){ //check to make sure only getting -s or -p commands
				string arg2 = argv[2];
				string arg4 = argv[4];
				// int portStatus = validPort(argv[2]);
				int portStatus;
				int ipStatus;
				if (arg1 == "-p"){portStatus = s1.validPort(arg2);}
				if (arg3 == "-p"){portStatus = s1.validPort(arg4);}
				if (portStatus == 4){return errorMessage(4);}
				if (arg1 == "-s"){ipStatus = s1.validIP(arg2);}
				if (arg3 == "-s"){ipStatus = s1.validIP(arg4);}
				if (ipStatus == 5){return errorMessage(5);}
			//cout << "made it here" << endl;
				
				}
			else{return errorMessage(3);}
			}
		else{return errorMessage(3);}
		}
	}
	else{return errorMessage(1);}
	
	cout << "ALL IS GOOD" << endl;	
	return 0;

	
	
	
}