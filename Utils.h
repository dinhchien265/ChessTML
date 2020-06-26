#pragma once
#pragma once
#include "string.h"
#include<iostream>

std::string convertMove(std::string chessMove) {
	std::string newChessMove = "a0a0";
	newChessMove[0] = 'h' - chessMove[0] + 'a';
	newChessMove[1] = '9' - chessMove[1] + '0';
	newChessMove[2] = 'h' - chessMove[2] + 'a';
	newChessMove[3] = '9' - chessMove[3] + '0';
	return newChessMove;
}