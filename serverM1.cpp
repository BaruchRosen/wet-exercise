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
	char buf[BUFLEN];
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
		printf("In this part a TCP would make 'Connection to m_ip_addr established',here it is irellevent\n");



		// listening for data A

		printf("Waiting for data(A)...");
		fflush(stdout);
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		recv_len = recvfrom(socketA, buf, BUFLEN, 0, (struct sockaddr *) &clientA, &slen);
		printf("\nConnection with a_ip_addr accepted\n");

		/*
		//print details of the client/peer and the data received
		printf("Received packet from(A) %s:%d\n", inet_ntoa(clientA.sin_addr), ntohs(clientA.sin_port));
		printf("Data: %s\n", buf);
		*/
		recv_len = recvfrom(socketA, buf, BUFLEN, 0, (struct sockaddr *) &clientA, &slen);
		printf("Message received: %s, data:dataAB\n", buf);

		/*
		//now reply the client
		sendto(socketA, "got the message from A", recv_len, 0, (struct sockaddr*) &clientA, slen);
		printf("\n sent replay to A\n");
		*/

		closesocket(socketA);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//Create a socket
		socketB = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		//socketB = socket(AF_INET, SOCK_DGRAM, 0);
		printf("Socket B created.\n");

		
		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;//server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(PORTB);
		


		//Bind B
		bind(socketB, (struct sockaddr *)&server, sizeof(server));
		puts("Bind B done");
		printf("In this part a TCP would make 'Connection to m_ip_addr established',here it is irellevent\n");

		//try to receive some data, this is a blocking call
		recv_len = recvfrom(socketA, buf, BUFLEN, 0, (struct sockaddr *) &clientA, &slen);
		printf("\nConnection with b_ip_addr accepted\n");


		// listening for data B
		printf("Waiting for data(B)...");
		fflush(stdout);
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		
		sendto(socketB, "M got your message", recv_len, 0, (struct sockaddr*) &clientB, slen);
		printf("\nMessage sent: 'M got your message', data : dataAB\n");


		//try to receive some data, this is a blocking call
		recv_len = recvfrom(socketB, buf, BUFLEN, 0, (struct sockaddr *) &clientB, &slen);
		printf("Message received: %s, data: dataBA", buf);

		//print details of the client/peer and the data received
		//printf("Received packet from(A) %s:%d\n", inet_ntoa(clientB.sin_addr), ntohs(clientB.sin_port));
		//printf("Data: %s\n", buf);

		closesocket(socketB);

	
	WSACleanup();




	return 0;
}
