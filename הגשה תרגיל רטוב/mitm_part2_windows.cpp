// M2.cpp 

//#include "pch.h"
#include <iostream>
#pragma warning(disable : 4996)
#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include <time.h>

#define BUFLEN 1000	//Max length of buffer
#define PORTA 67	//The port on which to listen for A
#define PORTB 404	//The port on which to listen for B
using namespace std;

int main()
{
	SOCKET socketA, socketB;
	struct sockaddr_in server, clientA, clientB;
	int slen, recv_len, j;
	char buf[BUFLEN], msgAM[BUFLEN], msgBM[BUFLEN], *ret;
	WSADATA wsa;
	time_t t;

	slen = sizeof(clientA);

	//Initialise winsock
	printf("\nInitialising Winsock...\n");

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
	printf("\nConnection with %s accepted\n", inet_ntoa(clientA.sin_addr));

	//flip one random char in message

	ret = strstr(msgAM, "$$$");
	srand(time(NULL));
	j = rand() % (strlen(msgAM) - strlen(ret));//

	if (msgAM[j] != 's')
	{
		msgAM[j] = 's';
	}
	else
	{
		msgAM[j] = 'r';
	}

	//printing data AB
	ret = strtok(msgAM, "$$$");
	printf("Message received: %s,\n data:dataAB\n", ret);
	//extract the ip from the text
	ret = strstr(msgAM, " ");

	//printf("The IP is: %s\n", ret);


	closesocket(socketA);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Create a socket for B
	socketB = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//socketB = socket(AF_INET, SOCK_DGRAM, 0);
	printf("\n\n\n Socket B created.\n");


	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ret);// inet_addr(ret); // .sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORTB);


	//Bind B
	bind(socketB, (struct sockaddr *)&server, sizeof(server));
	puts("Bind B done");

	recv_len = recvfrom(socketB, buf, BUFLEN, 0, (struct sockaddr *) &clientB, &slen);
	printf("\nConnection with %s accepted\n", inet_ntoa(clientB.sin_addr));

	//send from "A" to B
	sendto(socketB, msgAM, recv_len, 0, (struct sockaddr*) &clientB, slen);
	ret = strtok(msgAM, "$$$");
	printf("Message	sent: %s, data : dataAB", ret);

	//receive data BM
	recv_len = recvfrom(socketB, msgBM, BUFLEN, 0, (struct sockaddr *) &clientB, &slen);

	//flip char in the B to A
	ret = strstr(msgBM, "$$$");
	srand(time(NULL));
	j = rand() % (strlen(msgBM) - strlen(ret));//

	if (msgBM[j] != 's')
	{
		msgBM[j] = 's';
	}
	else
	{
		msgBM[j] = 'r';
	}


	ret = strtok(msgBM, "$$$");
	printf("\nMessage received: %s data: dataBA\n", ret);


	closesocket(socketB);
	//////////////////////////////////////////////////////////////////////////////////////////////

	//Create socket A again
	socketA = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	printf("Socket A created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORTA);

	//Bind A
	bind(socketA, (struct sockaddr *)&server, sizeof(server));
	puts("Bind A done\n");

	//send BM to A
	sendto(socketA, msgBM, recv_len, 0, (struct sockaddr*) &clientA, slen);

	ret = strtok(msgBM, "$$$");
	printf("Message sent: %s, data: dataBA", ret);

	closesocket(socketA);
	scanf("%s", buf);

	WSACleanup();


	return 0;
}
