#include "stdafx.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>

#pragma comment(lib,"ws2_32")

#define BUF_SIZE 1024
#define opsz

void error_handling(char* message);
int calculate(int opnum, int opnds[], char oprator);

int main(int argc, char *argv[]) {

	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	int serv_sock, clnt_sock;
	char opinfo[BUF_SIZE];
	int result, opnd_cnt, i;
	int recv_cnt, recv_len;
	struct sockaddr_in serv_addr, clnt_addr;
	int clnt_addr_size;
	char message[BUF_SIZE];
	int str_len;
	
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock != 0)
		error_handling("socket() error!");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) != 0)
		error_handling("bind() error!");
	if (listen(serv_sock, 5) != 0)
		error_handling("listen() error!");
	clnt_addr_size = sizeof(clnt_addr);
	for (int i = 0;i < 5;i++) {
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr,
			&clnt_addr_size);
		if (clnt_sock != 0)
			error_handling("accept error!");
		else
			printf("connected client %d\n", i + 1);
		while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
			write(clnt_sock, message, str_len);
		close(clnt_sock);
		return 0;
	}
	WSACleanup();
}

void error_handling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
