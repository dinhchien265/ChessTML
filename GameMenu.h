#pragma once
#include <iostream>
#include "GameMenuGraphic.h"
#include "DataIOClient.h"
#include "BussinessClient.h"
#include "WaitingGraphic.h"
enum gameFunction { INVITE = 0, WAIT = 1, RANKING = 2, BACK = 3 };



// handle option from menu game
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
// open menu game
void startMenuGame(SOCKET s) {
	int ret;
	Message mess;
	char choose;
	GameParam params;
	sf::RenderWindow window(sf::VideoMode(1280.f, 720.f), "Chess");
	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
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
						mess.messType = FIND_OPPONENT;
						ret = sendMessage(s, (char*)&mess, sizeof(Message));
						ret = recvMessage(s, (char*)&mess, sizeof(Message));
						if (mess.code == SUCCESS) {
							std::cout << "\nChon 1 nguoi : " << mess.data << "\n";
							std::cin >> mess.data;
							mess.messType = CHALLENGER;
							ret = sendMessage(s, (char*)&mess, sizeof(Message));
							ret = recvMessage(s, (char*)&mess, sizeof(Message));
							if (mess.messType == REP_CHALLENGER) {
								if (mess.code == SUCCESS)
								{
									window.setVisible(false);
									params.s = s;
									params.mess = mess;
									startGameThread(params);
									startMenuGame(s);
								}
							}
						}
						else {
							printf("\nKhong co nguoi choi nao ranh");
						}
						break;
					case WAIT:
						mess.messType = WAIT_CHALLENGER;
						handleWWaiting(mess, s, window);
						startMenuGame(s);
						break;
					case RANKING:
						mess.messType = RANK;
						ret = sendMessage(s, (char*)&mess, sizeof(Message));
						ret = recvMessage(s, (char*)&mess, sizeof(Message));
						printf("\n%s", mess.data);
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
