

//#include "pch.h"
#include <iostream>
#include<string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#pragma warning(disable : 4996)


int main()
{
	
	char a, message1[50], message2[150] = { "abc\0" }, message3[250], test[15], server_IP[] = "127.0.0.3";
	int i, j, k,n;
	time_t t;
	char *ret;

	//get string from user
	printf("enter message:\n");
	scanf("%[^\n]%*c", message1);


	//add IP to the end of the message
	strcat(message1, " $$$   ");
	strcat(message1, server_IP);
	printf("%s", message1);


	//flip one random char in message
	srand(time(NULL));
	j = rand() % (strlen(message1)-13);
	
	if (message1[j] != 's')
	{
		message1[j] = 's';
	}
	else
	{
		message1[j] = 'R';
	}

	printf("\n%s\n\n", message1);



	
	//triple each char
	k = strlen(message1);
	for ( i = 0; i < k; i++)
	{
		message2[i*3] = message1[i];
		message2[i*3+1] = message1[i];
		message2[i*3+2] = message1[i];
	}
	message2[3*k] = '\\';
	message2[3*k+1] = '0';
	printf("\n %s \n\n", message2);

	//flip one random char in message
	srand(time(NULL));
	j = rand() % (strlen(message2) - 13);

	if (message2[j] != 'd')
	{
		message2[j] = 'd';
	}
	else
	{
		message2[j] = 'a';
	}

	printf("\n%s\n\n", message2);



	//"untriple"
	for ( i = 0; i < 3*k; i++)
	{
		if (message2[3*i]==message2[3*i+1])
		{
			message3[i] = message2[3*i];
		}
		else
		{
			if (message2[3 * i] == message2[3 * i + 2])
			{
				message3[i] = message2[3 * i];
			}
			else
			{
				message3[i] = message2[3 * i+1];
			}
		}

	}

	printf("\n %s \n\n", message3);
	

	//extract the ip from the text
	ret = strstr(message3, "   ");
	
	printf("The IP is: %s\n", ret);

	return 0;
}


