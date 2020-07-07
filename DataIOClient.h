#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")


enum messType { LOGIN = 5, LOGOUT = 8, TIM_NGUOI_CHOI, THACH_DAU, CHO_THACH_DAU, TRA_LOI_THACH_DAU, GUI_NUOC_DI, ENDGAME, Xin_thua, RANK };
enum code { SUCCESS = 1, INCORRECT_USER_NAME_OR_PASSWORD = 10, ACC_HAS_BLOCKED = 12, LOGGED_IN, NOT_LOGGED_IN, ALLREADY_LOGGED_IN, ACCEPT, REFUSE, WIN, LOSE };

struct Message {
	int messType; //opcode
	int code;	// success or false
	char userName[30];
	char passWord[30];
	char move[5];
	char opponent[200]; // name of opponent
	int color;
};


// wrapped of send
int sendMessage(SOCKET s, char*buff, int len) {

	int nLeft, idx, ret;
	nLeft = len;
	idx = 0;

	while (nLeft > 0) {
		ret = send(s, &buff[idx], nLeft, 0);
		if (ret == SOCKET_ERROR) {
			return 0;
		}
		nLeft -= ret;
		idx += ret;
	}
	return len;
}
// wrapped of message
int recvMessage(SOCKET s, char*buff,int len) {
	int ret, nLeft=len, idx;
	idx = 0;

	while (nLeft > 0)
	{
		ret = recv(s, &buff[idx], nLeft, 0);
		if (ret == SOCKET_ERROR) {
			return 0;
		}
		nLeft -= ret;
		idx += ret;
	}
	return len;
}
