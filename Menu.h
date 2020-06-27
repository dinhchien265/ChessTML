#pragma once

#include "BussinessClient.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048

#pragma comment(lib,"Ws2_32.lib")


// Generate a menu and handle user choose
void menu(SOCKET s) {
	while (1) {
		char choose;
		system("cls");
		std::cout << "1. Login" << std::endl << "2. Logout" << std::endl << "3. Exit"<<"\nsocket: "<<s;
		choose = _getch();
		switch (choose)
		{
		case '1':
			Login(s);
			break;
		case '2':
			Logout(s);
			break;
		case '3':
			exit(0);
		default:
			break;
		}
	}
}