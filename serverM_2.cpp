// serverM1.cpp 

#include "pch.h"
#include <iostream>
#pragma warning(disable : 4996)
#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 1000	//Max length of buffer
#define PORTA 67	//The port on which to listen for A
#define PORTB 404	//The port on which to listen for B
using namespace std;

int main()
{
	SOCKET socketA, socketB;
	struct sockaddr_in server, clientA , clientB;
	int slen, recv_len;
	char buf[BUFLEN], msgAM[BUFLEN], msgBM[BUFLEN];
	WSADATA wsa;
	slen = sizeof(clientA);

	//Initialise winsock
	printf("\nInitialising Winsock...\n");
	/*
	The MAKEWORD(2,2) parameter of WSAStartup makes a request
	for version 2.2 of Winsock on the system, and sets the passed
	version as the highest version of Windows Sockets support that the caller can use.
	*/
	WSAStartup(MAKEWORD(2, 2), &wsa);
	printf("Initialised.\n");

	

		//Create a socket
		socketA = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		printf("Socket A created.\n");

		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(PORTA);

		//Bind A
		bind(socketA, (struct sockaddr *)&server, sizeof(server));
		puts("Bind A done\n");


		// listening for data A
		
		fflush(stdout);
		
		memset(buf, '\0', BUFLEN);
		memset(msgAM, '\0', BUFLEN);
		memset(msgBM, '\0', BUFLEN);
		
		//receive data AB
		
		recv_len = recvfrom(socketA, msgAM, BUFLEN, 0, (struct sockaddr *) &clientA, &slen);
		
		
		printf("\nConnection with %s accepted\n" , inet_ntoa(clientA.sin_addr));
		//recv_len = recvfrom(socketA, msgAM, BUFLEN, 0, (struct sockaddr *) &clientA, &slen);
		printf("Message received: %s,\n data:dataAB\n", msgAM);

		/*
		//print details of the client/peer and the data received
		printf("Received packet from(A) %s:%d\n", inet_ntoa(clientA.sin_addr), ntohs(clientA.sin_port));
		printf("Data: %s\n", buf);
		*/
		//recv msg AM
		//recv_len = recvfrom(socketA, buf, BUFLEN, 0, (struct sockaddr *) &clientA, &slen);
		
		//sendto(socketA, "M got your message AM data A to B", recv_len, 0, (struct sockaddr*) &clientA, slen);

		

		//closesocket(socketA);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//Create a socket for B
		socketB = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		//socketB = socket(AF_INET, SOCK_DGRAM, 0);
		printf("\n\n\nSocket B created.\n");

		
		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;//server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(PORTB);
		

		//Bind B
		bind(socketB, (struct sockaddr *)&server, sizeof(server));
		puts("Bind B done");
		recv_len = recvfrom(socketB, msgBM, BUFLEN, 0, (struct sockaddr *) &clientB, &slen);
		sendto(socketB, msgAM, recv_len, 0, (struct sockaddr*) &clientB, slen);
		printf("Message	sent: %s, data : dataAB", msgAM);
		sendto(socketB, msgAM, recv_len, 0, (struct sockaddr*) &clientB, slen);

		//receive data BM
		recv_len = recvfrom(socketB, msgBM, BUFLEN, 0, (struct sockaddr *) &clientB, &slen);
	
		printf("\n %s \n", msgBM); 
				

		closesocket(socketB);



		sendto(socketA, msgBM, recv_len, 0, (struct sockaddr*) &clientA, slen);
		printf("Message sent: %s, data: dataBA" , msgBM);

		closesocket(socketA);
	
	WSACleanup();




	return 0;
}
