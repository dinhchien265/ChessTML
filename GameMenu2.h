#pragma once
#include <iostream>
#include "Game.h"
#include "GameMenuGraphic.h"
#include "DataIOClient.h"
#include "WaitingGraphic.h"
enum gameFunction { INVITE = 0, WAIT = 1, RANKING = 2, BACK = 3 };

int handleGame(int status, SOCKET s) {
	switch (status)
	{
	case INVITE:
		std::cout << "\nInviting people";
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
	int ret;
	Message mess;
	char choose;
	sf::RenderWindow window(sf::VideoMode(700, 700), "Chess");
	Menu menu(window.getSize().x, window.getSize().y);
	//sf::Music music;
	//if (!music.openFromFile("menu.wav")) {
	//}
	//music.play();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case INVITE:
						mess.messType = TIM_NGUOI_CHOI;
						ret = sendMessage(s, (char*)&mess, sizeof(Message));
						ret = recvMessage(s, (char*)&mess, sizeof(Message));
						if (mess.code == SUCCESS) {
							std::cout << "\nChon 1 nguoi : " << mess.opponent << "\n";
							std::cin >> mess.opponent;
							mess.messType = THACH_DAU;
							ret = sendMessage(s, (char*)&mess, sizeof(Message));
							ret = recvMessage(s, (char*)&mess, sizeof(Message));
							if (mess.messType == TRA_LOI_THACH_DAU) {
								if (mess.code == SUCCESS)
								{
									window.setVisible(false);
									startGaneThread(s,mess);
								}
							}
						}
						break;
					case WAIT:
						mess.messType = CHO_THACH_DAU;
						ret = sendMessage(s, (char*)&mess, sizeof(Message));
						ret = recvMessage(s, (char*)&mess, sizeof(Message));
						window.setVisible(false);
						//waitingWindows();
						if (mess.messType == THACH_DAU) {
							std::cout << mess.opponent << " thach dau\nClich 1 to accept, 2 to refuse";
							scanf_s("%c", &choose);
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
								if (mess.code == SUCCESS) {
									window.setVisible(false);
									startGaneThread(s,mess);
								};
							}
						}
						break;
					case RANKING:
						break;
					case BACK:
						window.close();
						break;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		menu.draw(window);
		window.display();
	}
}


