#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#define BUF_SIZE 1024
int main() {
	char filename[100] = { 0 };
	printf("Input filename to save: ");
	std::cin >> filename;
	FILE *fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	char buffer[BUF_SIZE] = { 0 };
	int nCount;
	while ((nCount = recv(sock, buffer, BUF_SIZE, 0)) > 0) {
		fwrite(buffer, nCount, 1, fp);
	}
	puts("File transfer success!");
	fclose(fp);
	closesocket(sock);
	WSACleanup();
	system("pause");
	return 0;
}