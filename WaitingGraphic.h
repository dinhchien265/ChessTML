#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
void  waitingWindows()
{
	RenderWindow window(VideoMode(1280, 720), "Game Player1");
	sf::Texture t;
	if (!t.loadFromFile("waiting.png")) {
		std::cout << "can't load file";
	};
	sf::RectangleShape background(sf::Vector2f(1280.0f, 720.0f));
	background.setTexture(&t);
	while (window.isOpen()) {
		window.draw(background);
		window.display();
	}
}