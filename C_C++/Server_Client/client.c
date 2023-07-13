// client

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9734

int main(void)
{
    	int sockfd;
    	int len;
    	struct sockaddr_in address;
    	int result;
    	unsigned char ch[100],ss[100];
	
    	sockfd = socket(AF_INET, SOCK_STREAM, 0);				//  Create a socket for the client.

    	address.sin_family = AF_INET;						// Name the socket, as agreed with the server.
    	
	address.sin_addr.s_addr = inet_addr(SERVER_IP);

    	address.sin_port = SERVER_PORT;

    	len = sizeof(address);
	
    	result = connect(sockfd, (struct sockaddr *)&address, len);		//  Now connect our socket to the server's socket.

    	if(result == -1) 
		{
    	    		perror("oops: client2");
    	    		exit(1);
    		}

/*	while((strcmp(ss,"close")))						// We can now read/write via sockfd.
    	    	{
        		printf("client :");
			send(sockfd, ss, sizeof(ss)-1,0);
	 		recv(sockfd, ch, sizeof(ch)-1,0);
        		printf ("server : %s\n",ch);
 			if((strcmp(ch,"close"))==0)
        		break;
        	}*/

		while(strcmp(ss,"ls"))							
    	    	{
			send(sockfd, ss, sizeof(ss)-1,0);
	 		*ch = system("ls");
			recv(sockfd, ch, sizeof(ch)-1,0);
			exit 0;
        	}
																																																																																													
//	close(sockfd);
   	write(sockfd, &ch, 1);
   	read(sockfd, &ch, 1);
   	printf("char from server = %s\n",ch); 
	close(sockfd);
    	exit(0);
}

