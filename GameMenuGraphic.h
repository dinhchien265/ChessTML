#pragma once

#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 4
enum { CONFIG_HEIGHT = 90, CONFIG_WIDTH = 40 };
class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void drawWaiting(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("font.ttf"))
	{
		// handle error
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Invite");
	menu[0].setPosition(sf::Vector2f(width / 2 - CONFIG_WIDTH, (height - CONFIG_HEIGHT) / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Wait");
	menu[1].setPosition(sf::Vector2f(width / 2 - CONFIG_WIDTH, (height - CONFIG_HEIGHT) / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Ranking");
	menu[2].setPosition(sf::Vector2f(width / 2 - CONFIG_WIDTH, (height - CONFIG_HEIGHT) / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	selectedItemIndex = 0;

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(width / 2 - CONFIG_WIDTH, (height - CONFIG_HEIGHT) / (MAX_NUMBER_OF_ITEMS + 1) * 4));

}


Menu::~Menu()
{
}
void Menu::drawWaiting(sf::RenderWindow &window) {
	window.clear(sf::Color::Black);
	sf::Texture w;
	std::cout << "this is my story";
	if (!w.loadFromFile("waiting.png")) {

	};
	sf::RectangleShape waiting(sf::Vector2f(1280.f, 720.0f));
	waiting.setTexture(&w);
	window.draw(waiting);
}
void Menu::draw(sf::RenderWindow &window)
{
	sf::Texture t;
	if (!t.loadFromFile("background.png")) {

	};
	sf::RectangleShape background(sf::Vector2f(1280.f, 720.0f));
	background.setTexture(&t);
	window.draw(background);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}