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
		std::cout << "\nSuccessful" << std::endl;
		if (mess.messType == LOGIN) {
			startMenuGame(s);
		}
		break;
	case INCORRECT_USER_NAME_OR_PASSWORD:
		std::cout << "\nError: Incorrect user or password" << std::endl;
		break;
	case ACC_HAS_BLOCKED:
		std::cout << "\nError: Account has blocked" << std::endl;
		break;
	case LOGGED_IN:
		std::cout << "\nError: Logged in !" << std::endl;
		break;
	case NOT_LOGGED_IN:
		std::cout << "\nError: Not logged in !" << std::endl;
		break;
	case ALLREADY_LOGGED_IN:
		std::cout << "\nAccount is allready logged in another client";
	default:
		break;
	}
	system("pause");
	return;
}


void Login(SOCKET s) {
	Message message;
	message.messType = LOGIN;
	std::cout << "\nUsername : ";
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
	message.messType = LOGOUT;
	ret = sendMessage(s, (char*)&message, sizeof(Message));

	Message mess;
	ret = recvMessage(s, (char*)&mess, sizeof(mess));
	handleMessage(mess, s);
	return;
}

