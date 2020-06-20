#pragma once
#include <iostream>
#include "Game.h"
enum gameFunction { INVITE = 1, WAIT = 2, RANKING = 3, BACK = 4 };

int handleGame(int status, SOCKET s) {
	switch (status)
	{
	case INVITE:
		std::cout << "\nInviting people";
		_beginthreadex(0, 0, startGaneThread, (void*)s, 0, 0);
		break;
	case WAIT:
		std::cout << "\n Wait for challenge";
	case RANKING:
		std::cout << "\n Ranking";
	case BACK:
		return 0;
	default:
		break;
	}
}

void startMenuGame(SOCKET s) {
	int status = 0;
	system("cls");
	std::cout << "\n1.Invite people";
	std::cout << "\n2.Wait people";
	std::cout << "\n3.Ranking";
	std::cout << "\n4.Back\n";
	std::cin >> status;
	handleGame(status, s);
}