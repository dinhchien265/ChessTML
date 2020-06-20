#pragma once

#include "DataIOClient.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "GameMenu.h"
#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048

#pragma comment(lib,"Ws2_32.lib")




// handle message from server and display to the screen
void handleMessage(Message mess, SOCKET s) {
	switch (mess.code)
	{
	case SUCCESS:
		std::cout << "Successful" << std::endl;
		startMenuGame(s);
		break;
	case INCORRECT_USER_NAME_OR_PASSWORD:
		std::cout << "Error: Incorrect user or password" << std::endl;
		break;
	case ACC_HAS_BLOCKED:
		std::cout << "Error: Account has blocked" << std::endl;
		break;
	case LOGGED_IN:
		std::cout << "Error: Logged in !" << std::endl;
		break;
	case NOT_LOGGED_IN:
		std::cout << "Error: Not logged in !" << std::endl;
		break;
	case ALLREADY_LOGGED_IN:
		std::cout << "Account is allready logged in another client";
	default:
		break;
	}
	system("pause");
	return;
}

void Login(SOCKET s) {
	Message message;
	message.messType = LOGIN;
	system("cls");
	std::cout << "Username : ";
	gets_s(message.userName, 30);
	std::cout << "Password : ";
	gets_s(message.passWord, 30);
	sendMessage(s, (char*)&message, sizeof(Message));

	Message mess;
	recvMessage(s, (char*)&mess, sizeof(mess));
	handleMessage(mess, s);
	return;
}

void Logout(SOCKET s) {
	int ret;
	Message message;
	system("cls");
	message.messType = LOGOUT;
	ret = sendMessage(s, (char*)&message, sizeof(Message));

	Message mess;
	ret = recvMessage(s, (char*)&mess, sizeof(mess));
	handleMessage(mess, s);
	return;
}