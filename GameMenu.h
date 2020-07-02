#pragma once
#include <iostream>
#include "Game.h"
#include "GameMenuGraphic.h"
#include "DataIOClient.h"
#include "WaitingGraphic.h"
#include <thread>
#include <future>
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
	sf::Texture w;
	if (!w.loadFromFile("waiting.png")) {

	};
	sf::RectangleShape waiting(sf::Vector2f(700.0f, 700.0f));
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
									startGaneThread(s, mess);
								}
							}
						}
						break;
					case WAIT:
						window.setVisible(false);
						waitingWindows(window);
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


