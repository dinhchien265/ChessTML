#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include "Game.h"
#include "BussinessClient.h"
#include "DataIOClient.h"
#include "Menu.h"
#include<iostream>
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048
#pragma comment(lib,"Ws2_32.lib")
#include "GameMenuGraphic.h"
#include "GameMenu.h"
#pragma comment(lib,"Ws2_32.lib")




int main()
{
	//Step 1: Inittiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData))
		printf("Version is not supported\n");

	//Step 2: Construct socket
	SOCKET client;
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	//Step 3: Specify server address
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5500);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Step 4: Request to connect serverk
	if (connect(client, (sockaddr *)&serverAddr, sizeof(serverAddr))) {
		printf("Error! Cannot connect server. %d", WSAGetLastError());
		_getch();
		return 0;
	}
	printf("Connected server! socket %d\n", client);

	//Step 5: Communicate with server
	char buff[BUFF_SIZE];
	int ret;
	//startMenuGame(client);

	//Step 5: Communicate with server 
	menu(client);
	return 0;
}
