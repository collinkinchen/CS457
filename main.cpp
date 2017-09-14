#include "Server.h"
#include <iostream> 
using std::cout;
using std::endl;
#include <fstream>
#include <string.h>
#include <stdio.h>
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

using std::ifstream;
using std::cerr;
using std::string;
using std::cin;
#define PORT "3490"
#define BACKLOG 10
#define MAXDATASIZE 100
int version = 457;
//struct sockaddr_in{
//unsigned short sin_family;/* Internet protocol (AF_INET) */
//unsigned short sin_port;  /* Address port (16 bits) */
//struct in_addr sin_addr; /* Internet address (32 bits) */
//char sin_zero[8];       /* Not used */
//}
struct build{
		short versionNum;
		short messageLenght;
		char messageText[256];
	};


void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


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
	
	int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

	
	//cout << "MY IP: " << hints.ai_flags << endl;
	
	
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
	
		if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
		}

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }
		//cout << "IP: " << p->ai_addr << endl;

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
	printf("Welcome to Chat!\n");
    printf("Waiting for connections on...\n");
    printf("%d port 3490\n", hints.ai_flags);
	
	//cout << "IP: " << hints.ai_flags << endl;
	//cout << "PORT: " << PORT << endl;
    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("Found a friend! got connection from %s\n", s);
        printf("You recieve first.\n");
	int numbytes;
	//char buf[MAXDATASIZE];
	int tempcount = 0;
	while (tempcount < 4){
		struct build packet;
	if ((numbytes = recv(new_fd, &packet, sizeof (packet), 0)) == -1) {
		perror("recv");

    }

    //buf[numbytes] = '\0';

    printf("Friend: '%s'\n",packet.messageText);
		
		struct build temp;
		packet = temp;

		char message[256];
		cout << "You: ";
		cin.getline (message,256);
	
	//struct build packet;
	packet.versionNum = 457;//might need to be htons(457)
	packet.messageLenght = strlen(message);
	//packet.messageText = message;
	stpcpy(packet.messageText,message);
		
		bool loop = true;
	if (strlen(message) > 140){
		while(loop){
		cout << "Message not sent: length exceeds 140 characters" << endl;
		cout << "You: ";
		cin.getline (message,256);
		if (strlen(message) <= 140){
			//packet.messageText = message;
			stpcpy(packet.messageText,message);
			packet.messageLenght = strlen(message);
			loop = false;
		}
		}
	}

        if (send(new_fd, &packet, sizeof (packet), 0) == -1)
                perror("send");		

			//sleep(2);
			// struct build temp;
			// packet = temp;
        
			// if ((numbytes = recv(new_fd, &packet, sizeof (packet), 0)) == -1) {
			// perror("recv");

    // }

    // buf[numbytes] = '\0';

    // printf("Server: received '%s'\n",packet.messageText);
    //printf("Server: received '%d'\n",packet.messageLenght);
    //printf("Server: received '%d'\n",packet.versionNum);
	
	tempcount++;
	}
        close(new_fd);  // parent doesn't need this
    
	}

	}
	else{//handle 5
		string arg1 = argv[1];
		string arg3 = argv[3];
		if ((arg1 == "-p" || arg1 == "-s")){
			if ((arg3 == "-p" || arg3 == "-s")){ //check to make sure only getting -s or -p commands
				char* arg2 = argv[2];
				char* arg4 = argv[4];
				// int portStatus = validPort(argv[2]);
				int portStatus;
				int ipStatus;
				string ip;
				char* port;
				if (arg1 == "-p"){portStatus = s1.validPort(arg2);port = arg2;}
				if (arg3 == "-p"){portStatus = s1.validPort(arg4);port = arg4;}
				if (portStatus == 4){return errorMessage(4);}
				if (arg1 == "-s"){ipStatus = s1.validIP(arg2);ip = arg2;}
				if (arg3 == "-s"){ipStatus = s1.validIP(arg4);ip = arg4;}
				if (ipStatus == 5){return errorMessage(5);}
				//cout << "made it here" << endl;
				int newSocket = socket(PF_INET,SOCK_STREAM,0);
				if (newSocket < 0){return errorMessage(6);}
				
	int sockfd, numbytes;  
    //char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(INADDR_ANY, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            //perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure
	int tempcount = 0;
	struct build recieveData;

    while( tempcount < 4){//start while for sending/reciving

		char message[256];
		cout << "You: ";
		cin.getline (message,256);
		//s1.pack(message,version);

		struct build clientPacket;
	clientPacket.versionNum = 457; //might need to be htons(457)
	clientPacket.messageLenght = strlen(message);
	//packet.messageText = message;
	stpcpy(clientPacket.messageText,message);
		
		bool loop = true;
	if (strlen(message) > 140){
		while(loop){
		cout << "Message not sent: length exceeds 140 characters" << endl;
		cout << "You: ";
		cin.getline (message,256);
		if (strlen(message) <= 140){
			//packet.messageText = message;
			stpcpy(clientPacket.messageText,message);
			clientPacket.messageLenght = strlen(message);
			loop = false;
		}
		}
	}

	
	if (send(sockfd, &clientPacket, sizeof(clientPacket), 0) == -1)
        perror("send");
	
	if ((numbytes = recv(sockfd, &recieveData, sizeof (recieveData), 0)) == -1) {
        perror("recv");
    }
    //buf[numbytes] = '\0';
    printf("Friend: '%s'\n",recieveData.messageText);
	//sleep(2);
	
	
	tempcount++;
	}//end while for sending/reciving
    close(sockfd);

				// struct sockaddr_in server_addr;
				// int client=socket(AF_INET,SOCK_STREAM,0);
				// if (client < 0){return errorMessage(6);}
				// server_addr.sin_family=AF_INET;
				// server_addr.sin_addr.s_addr = inet_addr(IP);
				// server_addr.sin_port=htons(8080);
				// if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0){
        // cout << "=> Connection to the server " << inet_ntoa(server_addr.sin_addr) << " with port number: 8080" << endl;
					// }	
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