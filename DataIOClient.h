#pragma once
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")

// wrapped of send
int sendMessage(SOCKET s, char*buff, int len) {

	int nLeft, idx, ret;
	nLeft = len;
	idx = 0;

	while (nLeft > 0) {
		ret = send(s, &buff[idx], nLeft, 0);
		if (ret == SOCKET_ERROR) {

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
			return SOCKET_ERROR;
		}
		nLeft -= ret;
		idx += ret;
	}
	return len;
}