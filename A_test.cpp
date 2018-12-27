// endHostA.cpp 

#include "pch.h"
#include <iostream>

using namespace std;


#include<stdio.h>
#include<winsock2.h>
#include<string.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#pragma warning(disable : 4996)

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 1000	//Max length of buffer
#define PORT 67	//The port on which to listen for incoming data

int main(void)
{
	struct sockaddr_in si_other;
	int s,num, slen = sizeof(si_other);
	char buf[BUFLEN], serv[] = { "127.0.0.1" }, port[] = {"67"};
	char messageAM[BUFLEN],messageMA[BUFLEN],messageTest[BUFLEN], ipPorttext[50];
	WSADATA wsa;


	printf("%s%s\n",serv,port);
	printf("total char of: %d/n", strlen(serv)+strlen(port));
	printf("\n Enter your message (dataAB): ");
	
	
	//we need to find a way to add here the IP of B
	

	//scanf("%s", messageAM);
	scanf("%[^\n]%*c", messageAM);
	num = strlen(serv) + strlen(port)+1;
	strcat(messageAM, serv);
	strcat(messageAM, ":");
	strcat(messageAM, port);
	
	//printf("%s%s\n", serv, port);


	//Initialise winsock
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

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
	if (sendto(s, "start communication", strlen("start communication"), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	
		if (sendto(s, messageAM, strlen(messageAM), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		
		//printf("Message sent:  , messageAM);//dummy
		printf(" \n data: ");
		puts(messageAM);
		printf(" \ndataAB \n");
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		
		/*
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("\n recived back:\n");

		puts(buf);
		printf("\n end of message\n");

		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("\n recived back:\n");

		puts(buf);
		printf("\n end of message\n");
	*/

		closesocket(s);
		printf("connection closed");

		///////////////////////////////////////////////////////////////////////////////

		//create the socket again
		scanf("%s", buf);
		s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		
		memset((char *)&si_other, 0, sizeof(si_other));
		si_other.sin_family = AF_INET;
		si_other.sin_port = htons(PORT);
		si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

		printf("\nconnection opend again\n");

		//////**///////
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			//exit(EXIT_FAILURE);
		}
		printf("\n recived back:\n");

		printf("Message  received:  \n");
		puts(buf);
		printf(" \ndata:dataBA \n");

		printf("\n end of message\n");
		scanf("%s",buf);

	closesocket(s);
	WSACleanup();

	/*
	//Initialise winsock
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

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
	
		printf("Enter message : ");

		scanf("%s", messageAM);
		printf("\n%s\n", messageAM);
		//send the message
		if (sendto(s, messageAM, strlen(messageAM), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("sent\n");//dummy
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		printf("check1");
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("\n recived back:\n");

		puts(buf);
		printf("\n end of message\n");

		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("\n recived back:\n");

		puts(buf);
		printf("\n end of message\n");
	

	closesocket(s);
	WSACleanup();
	*/

	return 0;
}
