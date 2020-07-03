#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Rule.h"
#include "Utils.h"
enum color { WHITE = -1, BLACK = 1 };
#include <SFML/Graphics.hpp>
#include <time.h>
#include "process.h"
#include "string.h"
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "DataIOClient.h"
#pragma comment(lib,"Ws2_32.lib")
using namespace sf;
typedef struct {
	SOCKET s;
	Message mess;
} GameParam;
int turn = WHITE;
int myColor = BLACK;
SOCKET client;
Message mess;
bool flag;

int size = 56;
Vector2f offset(28, 28);

Sprite f[32]; //figures
std::string position = "";

int board[8][8] =
{ -1,-2,-3,-4,-5,-3,-2,-1, //quan trang so am, quan den so duong
-6,-6,-6,-6,-6,-6,-6,-6,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
6, 6, 6, 6, 6, 6, 6, 6,
1, 2, 3, 4, 5, 3, 2, 1 };

std::string toChessNote(Vector2f p)
{
	std::string s = "";
	s += char(p.x / size + 97);
	s += char(7 - p.y / size + 49);
	return s;
}

Vector2f toCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 7 - int(b) + 49;
	return Vector2f(x*size, y*size);
}

void move(std::string str)
{
	Vector2f oldPos = toCoord(str[0], str[1]);
	Vector2f newPos = toCoord(str[2], str[3]);

	for (int i = 0; i < 32; i++)
		if (f[i].getPosition() == newPos) f[i].setPosition(-100, -100);

	for (int i = 0; i < 32; i++)
		if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);

	//castling       //if the king didn't move
	if (str == "e1g1") if (position.find("e1") == -1) move("h1f1");
	if (str == "e8g8") if (position.find("e8") == -1) move("h8f8");
	if (str == "e1c1") if (position.find("e1") == -1) move("a1d1");
	if (str == "e8c8") if (position.find("e8") == -1) move("a8d8");
}

void loadPosition()
{
	int k = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			f[k].setTextureRect(IntRect(size*x, size*y, size, size));
			if (myColor == BLACK) {
				f[k].setPosition(size*(7 - j), size*(7 - i));
			}
			if (myColor == WHITE) {
				f[k].setPosition(size*(j), size*(i));
			}
			k++;
		}

	for (int i = 0; i < position.length(); i += 5)
		move(position.substr(i, 4));
}

void updateBoard(std::string str, int board[8][8]) {
	int x1 = str[0] - 97;
	int y1 = str[1] - 49;
	int x2 = str[2] - 97;
	int y2 = str[3] - 49;
	board[y2][x2] = board[y1][x1];
	board[y1][x1] = 0;
}

unsigned __stdcall recvThread(void* param) {
	int ret = recvMessage(client, (char*)&mess, sizeof(Message));
	flag = true;
	return 0;
}

void startGaneThread(GameParam params) {
	SOCKET s = params.s;
	Message mess = params.mess;
	client = s;
	myColor = mess.color;
	RenderWindow window(VideoMode(1280.0f, 720.f), "Game Player");
	Texture t1, t2;
	t1.loadFromFile("images/figures.png");
	t2.loadFromFile("images/board.png");
	for (int i = 0; i < 32; i++) f[i].setTexture(t1);
	Sprite sBoard(t2);
	loadPosition();
	bool isMove = false;
	float dx = 0, dy = 0;
	Vector2f oldPos, newPos;
	std::string str;
	int n = 0;

	if (mess.color == 1) {
		int ret = recvMessage(s, (char*)&mess, sizeof(Message));
		str = std::string(mess.move);
		move(convertMove(str));
		updateBoard(str,board);
		turn *= -1;
		printBoard(board);
	}

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			////move back//////
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::BackSpace)
				{
					if (position.length() > 6) position.erase(position.length() - 6, 5); loadPosition();
				}

			/////drag and drop///////
			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
					for (int i = 0; i < 32; i++)
						if (f[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							isMove = true; n = i;
							dx = pos.x - f[i].getPosition().x;
							dy = pos.y - f[i].getPosition().y;
							oldPos = f[i].getPosition();
						}

			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Left)
				{
					isMove = false;
					Vector2f p = f[n].getPosition() + Vector2f(size / 2, size / 2);
					newPos = Vector2f(size*int(p.x / size), size*int(p.y / size));
					str = toChessNote(oldPos) + toChessNote(newPos);
					if (oldPos != newPos) position += str + " ";
					std::string convertPosition = str;
					if (myColor == BLACK) {
						convertPosition = convertMove(str);
					}
					std::cout << "\n" << convertPosition;
					if (check(convertPosition, board, turn) == 1) {
						turn = turn*-1;
						move(str);
						f[n].setPosition(newPos);
						updateBoard(convertPosition, board);
						mess.messType = GUI_NUOC_DI;
						mess.move[0] = convertPosition[0];
						mess.move[1] = convertPosition[1];
						mess.move[2] = convertPosition[2];
						mess.move[3] = convertPosition[3];
						mess.move[4] = '\0';
						int ret = sendMessage(s, (char*)&mess, sizeof(Message));
						std::cout << "\nret= " << ret<<"\nsocket: "<<s;
						_beginthreadex(0, 0, recvThread, (void*)client, 0, 0);

					}
					else f[n].setPosition(oldPos);
					printBoard(board);
				}
		}

		//comp move
		if (flag==true)
		{
			str = std::string(mess.move);
			move(convertMove(str));
			updateBoard(str, board);
			turn *= -1;
			printBoard(board);
			flag = false;

			oldPos = toCoord(str[0], str[1]);
			newPos = toCoord(str[2], str[3]);

			for (int i = 0; i < 32; i++) if (f[i].getPosition() == oldPos) n = i;

			/////animation///////
			for (int k = 0; k < 50; k++)
			{
				Vector2f p = newPos - oldPos;
				f[n].move(p.x / 50, p.y / 50);
				window.draw(sBoard);
				for (int i = 0; i < 32; i++) f[i].move(offset);
				for (int i = 0; i < 32; i++) window.draw(f[i]); window.draw(f[n]);
				for (int i = 0; i < 32; i++) f[i].move(-offset);
				window.display();
			}

			move(str);  position += str + " ";
			f[n].setPosition(newPos);
		}

		if (isMove) f[n].setPosition(pos.x - dx, pos.y - dy);

		////// draw  ///////
		window.clear();
		window.draw(sBoard);
		for (int i = 0; i < 32; i++) f[i].move(offset);
		for (int i = 0; i < 32; i++) window.draw(f[i]); window.draw(f[n]);
		for (int i = 0; i < 32; i++) f[i].move(-offset);
		window.display();
	}

}