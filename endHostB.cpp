// endHostB.cpp 

#include "pch.h"
#include <iostream>

using namespace std;

/*
	Simple udp client
*/
#include<stdio.h>
#include<winsock2.h>
#include<string.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#pragma warning(disable : 4996)

#define SERVER "127.0.0.1"	//ip address of udp server    127.0.0.1
#define BUFLEN 1000	//Max length of buffer
#define PORT 404	//The port on which to listen for incoming data

int main(void)
{
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char messageBM[BUFLEN],messageMB[BUFLEN],messageTest[BUFLEN];
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("\n Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	//start communication
	

	if (sendto(s, "test", strlen(messageBM), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("\n waiting for M's message:\n");

	if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
	{
		printf("recvfrom() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("\n recived back:\n");
	puts(buf);
	printf("\n end of messageB\n");


	printf("\n enter message:\n");
		scanf("%s", messageBM);
		printf("%s", messageBM);


		if (sendto(s, messageBM, strlen(messageBM), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		/*
		printf("Enter a back message : ");

		scanf("%s", messageBM);
		printf("%s", messageBM);
		//send the message
		if (sendto(s, messageBM, strlen(messageBM), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("sent\n");//dummy
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		printf("check1B");
		//try to receive some data, this is a blocking call
		*/
	

	closesocket(s);
	WSACleanup();

	return 0;
}
