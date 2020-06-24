
#include "DataIOClient.h"
#include <iostream>
#include "Game.h"


int handleGame(char status, SOCKET s) {
	int ret;
	Message mess;
	char choose;
	switch (status)
	{
	case '1':
		system("cls");
		std::cout << "\nDang tim nguoi choi";
		//_beginthreadex(0, 0, startGaneThread, (void*)s, 0, 0);
		mess.messType = TIM_NGUOI_CHOI;
		ret=sendMessage(s, (char*)&mess, sizeof(Message));
		ret=recvMessage(s, (char*)&mess, sizeof(Message));
		if (mess.code == SUCCESS) {
			std::cout << "\nChon 1 nguoi : " << mess.opponent << "\n";
			std::cin >> mess.opponent;
			mess.messType = THACH_DAU;
			ret = sendMessage(s, (char*)&mess, sizeof(Message));
			ret = recvMessage(s, (char*)&mess, sizeof(Message));
			if (mess.messType == TRA_LOI_THACH_DAU) {
				if (mess.code == SUCCESS) _beginthreadex(0, 0, startGaneThread, (void*)s, 0, 0);
			}
		}
		break;
	case '2':
		std::cout << "\n Wait for challenge\n";
		mess.messType = CHO_THACH_DAU;
		ret = sendMessage(s, (char*)&mess, sizeof(Message));
		ret = recvMessage(s, (char*)&mess, sizeof(Message));
		if (mess.messType == THACH_DAU) {
			std::cout << mess.opponent << " thach dau\nClich 1 to accept, 2 to refuse";
			choose = _getch();
			mess.messType = TRA_LOI_THACH_DAU;
			switch (choose)
			{
			case '1':
				mess.code = ACCEPT;
				ret = sendMessage(s, (char*)&mess, sizeof(Message));
				break;
			case '2':
				mess.code = REFUSE;
				ret = sendMessage(s, (char*)&mess, sizeof(Message));
				break;
			default:
				break;
			}
			ret = recvMessage(s, (char*)&mess, sizeof(Message));
			if (mess.messType == TRA_LOI_THACH_DAU) {
				if(mess.code==SUCCESS) _beginthreadex(0, 0, startGaneThread, (void*)s, 0, 0);
			}
		}

	case '3':
		std::cout << "\n Ranking";
	case '4':
		return 0;
	default:
		break;
	}
}

void startMenuGame(SOCKET s) {
	char choose;
	system("cls");
	std::cout << "\n1.Tim nguoi choi";
	std::cout << "\n2.Wait people";
	std::cout << "\n3.Ranking";
	std::cout << "\n4.Back\n";
	choose = _getch();
	handleGame(choose, s);
}