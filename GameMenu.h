#pragma once
#include <iostream>
#include "Game.h"
#include "GameMenuGraphic.h"
enum gameFunction { INVITE = 0, WAIT = 1, RANKING = 2, BACK = 3 };

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
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Chess", sf::Style::Fullscreen);
	Menu menu(window.getSize().x, window.getSize().y);
	sf::Music music;
	if (!music.openFromFile("menu.wav")) {
	}
	music.play();
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
						window.setVisible(false);
						handleGame(INVITE, s);
						break;
					case 1:
						std::cout << "Option button has been pressed" << std::endl;
						break;
					case 2:
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


