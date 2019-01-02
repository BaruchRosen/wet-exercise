// hosts 1 
/*
This program simulates a host comunicating in UDP protocol.
The User chooses the type of host A or B as explaind in the external
documentation. in this part they work with an ECC protocol s mentiond in
the external documentation.
*/

//#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<winsock2.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#pragma warning(disable : 4996)

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 1000	//Max length of buffer
#define PORTA 67	//The port on which to listen for incoming data
#define PORTB 404

int main()
{
	int select = 0;


	printf("press 1 to select host A or press any other key for host B\n");

	scanf("%d", &select);


	if (select == 1)
	{
		struct sockaddr_in si_other;
		int s, i,k, num2, num, slen = sizeof(si_other);
		char buf[BUFLEN], serv[] = { "127.0.0.1" }, port[] = { "67" }, IPB[] = { "127.0.0.1" };
		char messageAM[BUFLEN], messageMA[BUFLEN], messageTest[3 * BUFLEN], *ret;
		WSADATA wsa;

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
		si_other.sin_port = htons(PORTA);
		si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

		printf("Connection to %s established\n", SERVER);


		//user input
		printf("\n\n Enter your message (dataAB): ");

		scanf(" %[^\t\n]s", &messageAM);

		//add ip of B
		strcat(messageAM, " $$$ ");
		strcat(messageAM, "127.0.0.1");////////////////


		//triple code
		num2 = strlen(messageAM);
		for (i = 0; i < num2; i++)
		{
			messageTest[i * 3] = messageAM[i];
			messageTest[i * 3 + 1] = messageAM[i];
			messageTest[i * 3 + 2] = messageAM[i];
		}
		
		//send data AB and B IP to M	
		if (sendto(s, messageTest, strlen(messageTest), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//confirm sending
		ret = strtok(messageTest, "$$$");
		printf("\nMessage sent: %s ,", ret);
		printf(" \n data: dataAB\n");



		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);



		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			//exit(EXIT_FAILURE);
		}

	for ( i = 0; i < 3*k; i++)
	{
		if (buf[3*i]==buf[3*i+1])
		{
			messageTest[i] = buf[3*i];
		}
		else
		{
			if (buf[3 * i] == buf[3 * i + 2])
			{
				messageTest[i] = buf[3 * i];
			}
			else
			{
				messageTest[i] = buf[3 * i+1];
			}
		}

	}

		ret = strtok(buf, "$$$");
		printf("Message  received: %s \n", ret);
		//puts(buf);
		printf(" \ndata:dataBA \n");
		//////////////////////////////////////////////////////////////



		scanf("%s", buf);

		closesocket(s);
		WSACleanup();


	}

	else
	{
		struct sockaddr_in si_other;
		int s, i , k , num2, slen = sizeof(si_other);
		char buf[BUFLEN], IPA[] = { "127.0.0.1" };
		char messageBM[BUFLEN], messageMB[BUFLEN], messageTest[BUFLEN], *ret;
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
		si_other.sin_port = htons(PORTB);
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

		for (i = 0; i < 3 * k; i++)
		{
			if (messageMB[3 * i] == messageMB[3 * i + 1])
			{
				messageTest[i] = messageMB[3 * i];
			}
			else
			{
				if (messageMB[3 * i] == messageMB[3 * i + 2])
				{
					messageTest[i] = messageMB[3 * i];
				}
				else
				{
					messageTest[i] = messageMB[3 * i + 1];
				}
			}

		}

		
		printf("Message received: %s , data: dataAB", messageTest);



		printf("\n enter message:\n");
		scanf(" %[^\t\n]s", &messageBM);

		//add ip of B
		strcat(messageBM, " $$$ ");
		strcat(messageBM, IPA);


		
		//triple code
		num2 = strlen(messageBM);
		for (i = 0; i < num2; i++)
		{
			messageTest[i * 3] = messageBM[i];
			messageTest[i * 3 + 1] = messageBM[i];
			messageTest[i * 3 + 2] = messageBM[i];
		}
		

		


		if (sendto(s, messageTest, strlen(messageTest), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		ret = strtok(messageTest, "$$$");
		printf("Message sent: %s , data: dataBA", ret);

		scanf("%s", buf);
		closesocket(s);
		WSACleanup();


	}



	return 0;
}
