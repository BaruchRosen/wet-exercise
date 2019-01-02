// endHostB.cpp 

#include "pch.h"
#include <iostream>

using namespace std;


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
	char buf[BUFLEN], IPA[] = { "127.0.0.1" };
	char messageBM[BUFLEN],messageMB[BUFLEN],messageTest[BUFLEN], *ret;
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		//exit(EXIT_FAILURE);
	}
	printf("\n Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		//exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	//conection...
	if (sendto(s, "start comunication", strlen("start comunication"), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		//exit(EXIT_FAILURE);
	}
	printf("\nConnection with %s accepted\n", SERVER);
	

	//fflush
	if (recvfrom(s, messageMB, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
	{
		printf("recvfrom() failed with error code : %d", WSAGetLastError());
		//exit(EXIT_FAILURE);
	}

	printf("Message received: %s , data: dataAB",messageMB);



	printf("\n enter message:\n");
	scanf("%[^\n]%*c", messageBM);

	//add ip of B
	strcat(messageBM, " $$$ ");
	strcat(messageBM, IPA);


		if (sendto(s, messageBM, strlen(messageBM), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		ret = strtok(messageBM, "$$$");
		printf("Message sent: %s , data: dataBA" , ret);
		
		scanf("%s", buf);
	closesocket(s);
	WSACleanup();

	return 0;
}
