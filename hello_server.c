#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>

#define PORT 9000

char buffer[BUFSIZ] = "hello, world";

int main()
{
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int n;
	// socket is a telephone so, define a telephone to communicate
	// the name of telephone is s_socket.
	s_socket = socket(PF_INET, SOCK_STREAM, 0);

	// define an address of incomming call
	// s_addr is the incomming call receiving address
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);

	// binding is to connect incomming call to a telephone, socket
	if(bind(s_socket,(struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
		printf("Can't bind\n");
		return -1;
	}

	// listening is to grant a communication right
	// example shows it asks 5 times to get a comm right
	if(listen(s_socket, 5) == -1) {
		printf("listen failed\n");
		return -1;
	}
	
	// accept() receive incomming call and hand it over to another telephone
	while(1) {

		len = sizeof(c_addr);
		c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);
		n = strlen(buffer);
		write(c_socket, buffer, n);

		close(c_socket);
	}

	close(s_socket);
	return 0;
}
