// serverM1.cpp 

#include "pch.h"
#include <iostream>
#pragma warning(disable : 4996)
#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 1000	//Max length of buffer
#define PORTA 67	//The port on which to listen for A

using namespace std;

int main()
{
	SOCKET socketA, socketB;
	struct sockaddr_in server, clientA, clientB;
	int slen, recv_len;
	char buf[BUFLEN],ipA[20];
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

	recv_len = recvfrom(socketA, buf, BUFLEN, 0, (struct sockaddr *) &clientA, &slen);
	printf("Message received:\n ");
	puts(buf);
	printf(" data:dataAB\n");

	//get the sender ip from the text
	ipA[1] = 'a';


	closesocket(socketA);

	printf("\nclosed A");
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	printf("\n\n this is where B should work, assume he sends 'like a a boss'\n\n");

	//Create a socket
	socketA = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	printf("Socket A created again.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORTA);

	//Bind A
	bind(socketA, (struct sockaddr *)&server, sizeof(server));
	puts("Bind A done\n");
	printf("In this part a TCP would make 'Connection to m_ip_addr established',here it is irellevent\n");

	fflush(stdout);
	//clear the buffer by filling null, it might have previously received data
	memset(buf, '\0', BUFLEN);

	sendto(socketA, "M got your message", recv_len, 0, (struct sockaddr*) &clientA, slen);

	scanf("%s", buf);

	closesocket(socketA);

	WSACleanup();




	return 0;
}
