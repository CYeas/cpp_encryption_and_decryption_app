#include <cstdio>
#include <cstdlib>
#include <WinSock2.h>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")

const int BUF_SIZE = 1024;

int main() {
	char *filename = "D:/workspace/cpp_encryption_and_decryption_app/learn/cpp_socket_learn/windows/test.txt";
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		std::cout << "can't open file" << filename << std::endl;
		system("pause");
		exit(0);
	}

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(SOCKADDR));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	listen(servSock, 20);

	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	char buffer[BUF_SIZE] = { 0 };
	int nCount;
	while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
		send(clntSock, buffer, nCount, 0);
	}
	shutdown(clntSock, SD_SEND);
	recv(clntSock, buffer, BUF_SIZE, 0);
	fclose(fp);
	closesocket(clntSock);
	closesocket(servSock);
	WSACleanup();

	system("pause");
	return 0;
}