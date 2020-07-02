#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
int handleWWaiting(Message mess, SOCKET s, RenderWindow &window) {
	int choose;
	int ret = sendMessage(s, (char*)&mess, sizeof(Message));
	ret = recvMessage(s, (char*)&mess, sizeof(Message));
	if (mess.messType == THACH_DAU) {
		std::cout << mess.opponent << " thach dau\nClick 1 to accept, 2 to refuse";
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
				startGaneThread(s, mess);
			};
		}
	}
	return ret;
}

void  waitingWindows(RenderWindow &previousWindow)
{
	RenderWindow window(VideoMode(700, 700), "Game Player1");
	sf::Texture t;
	if (!t.loadFromFile("waiting.png")) {
		std::cout << "can't load file";
	};
	sf::RectangleShape background(sf::Vector2f(700.0f, 700.0f));
	background.setTexture(&t);
	while (window.isOpen()) {
		window.draw(background);
		window.display();
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape)
				{
					previousWindow.setVisible(true);
					window.close();

				}

		}
	}
}

