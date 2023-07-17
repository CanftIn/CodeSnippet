#include <stdio.h>  
#include <sys/socket.h>  
#include <sys/types.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
#include <ctype.h>  
#include <strings.h>  
#include <string.h>  
#include <sys/stat.h>  
#include <pthread.h>  
#include <sys/wait.h>  
#include <stdlib.h>  

#define ISspace(x) isspace((int)(x))  

#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"  

void *accept_request(void *);
void bad_request(int);
void cat(int, FILE *);
void cannot_execute(int);
void error_die(const char *);
void execute_cgi(int, const char *, const char *, const char *);
int get_line(int, char *, int);
void headers(int, const char *);
void not_found(int);
void serve_file(int, const char *);
int startup(u_short *);
void unimplemented(int);


void error_die(const char *sc)
{
	perror(sc);
	exit(1);
}

int main(void)
{
	int server_sock = -1;
	u_short port = 0;
	int client_sock = -1;
	struct sockaddr_in client_name;
	socklen_t client_name_len = sizeof(client_name);
	pthread_t newthread;

	server_sock = startup(&port);
	printf("myhttpd running on port %d\n", port);

	while(1)
	{
		client_sock = accept(server_sock, 
			(struct sockaddr *)&client_name, &client_name_len);
		if(client_sock == -1)
			error_die("accept");
		if(pthread_create(&newthread, NULL, accept_request, (void *)&client_sock) != 0)
			perror("pthread_create");
	}
	close(server_sock);
	return 0;
}