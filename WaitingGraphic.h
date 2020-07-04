#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
void  waitingWindows()
{
	RenderWindow window(VideoMode(1280.f, 720.f), "Waiting");
	sf::Texture t;

	if (!t.loadFromFile("waiting.png")) {
		std::cout << "can't load file";
	};
	sf::RectangleShape background(sf::Vector2f(1280.f, 720.0f));
	background.setTexture(&t);
	while (window.isOpen()) {
		window.draw(background);
		window.display();
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape)
				{
					//previousWindow.setVisible(true);
					window.close();
				}
		}
	}
}

void handleWWaiting(Message mess, SOCKET s, RenderWindow &previouswindow) {
	previouswindow.setVisible(false);
	sf::Thread waitingThreadDisplay(&waitingWindows);
	waitingThreadDisplay.launch();
	char choose;
	int ret;
	ret = sendMessage(s, (char*)&mess, sizeof(Message));
	ret = recvMessage(s, (char*)&mess, sizeof(Message));

	if (mess.messType == THACH_DAU) {
		RenderWindow windowChoose(VideoMode(1280.0f, 720.f), "Choose");
		sf::Texture a;
		if (!a.loadFromFile("test.png")) {
			std::cout << "can't load file";
		};
		sf::RectangleShape backgroundChoose(sf::Vector2f(1280.0f, 720.0f));
		sf::Text text;
		sf::Font font;
		if (!font.loadFromFile("font.ttf"))
		{
			// error...
		}
		std::string temp = " da thach dau ban";
		text.setFont(font);
		text.setString(mess.opponent + temp);
		backgroundChoose.setTexture(&a);
		while (windowChoose.isOpen()) {
			windowChoose.draw(backgroundChoose);
			windowChoose.draw(text);
			windowChoose.display();
			Event e;
			while (windowChoose.pollEvent(e)) {
				if (e.type == Event::KeyPressed) {
					if (e.key.code == Keyboard::Num1)
					{
						mess.messType = TRA_LOI_THACH_DAU;
						mess.code = ACCEPT;
						ret = sendMessage(s, (char*)&mess, sizeof(Message));
						windowChoose.close();
					}
					if (e.key.code == Keyboard::Num2)
					{
						mess.messType = TRA_LOI_THACH_DAU;
						mess.code = REFUSE;
						ret = sendMessage(s, (char*)&mess, sizeof(Message));
						windowChoose.close();
					}
				}
			}
		}
		ret = recvMessage(s, (char*)&mess, sizeof(Message));
		if (mess.messType == TRA_LOI_THACH_DAU) {
			if (mess.code == SUCCESS) {
				GameParam params = { s, mess };
				sf::Thread gameThread(&startGaneThread, params);
				gameThread.launch();
				previouswindow.setVisible(false);
				//waitingThreadDisplay.terminate();
			};
		}
	}
}



