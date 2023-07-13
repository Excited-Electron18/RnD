// server

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void delay();

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9734


int main(void)
{
    	int server_sockfd, client_sockfd;
    
	int server_len, client_len;
    	
	struct sockaddr_in server_address;
    	
	struct sockaddr_in client_address;

    	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
    	server_address.sin_family = AF_INET;

    	server_address.sin_addr.s_addr = inet_addr(SERVER_IP);

    	server_address.sin_port = SERVER_PORT;

    	server_len = sizeof(server_address);

    	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	
    	listen(server_sockfd, 5);					//  Create a connection queue, ignore child exit details and wait for clients.
    	
	signal(SIGCHLD, SIG_IGN);
	
    	while(1) 
	{
    	    char ch[100],ss[100];
    	    printf("server waiting...\n");	

    	    client_len = sizeof(client_address);			// Accept connection.
    	    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
	
		if(fork() == 0) 					// If we're the child, we can now read/write to the client on client_sockfd.
			{			
/*			while((strcmp(ss,"close")))	
		        	{
					printf("client :");
			        	recv(client_sockfd, ch, sizeof(ch)-1,0);
			        	printf("%s\n",ch);
			        	printf("server :");
			        	send(client_sockfd, ss, sizeof(ss)-1,0);
					if(!(strcmp(ss,"close")))dea
						break;
				}*/
			//close(server_sockfd);
			//return 0;
  			read(client_sockfd,ch, 1);
    	        	printf("input from client %s\n",ss);
    	       		write(client_sockfd,ch, 1);
    	      	//	getch();
    	        	close(client_sockfd);
			sleep(1);
    	        	exit(0); 					// Terminating the child process created to serve the client
    	    		}

   	    else 
			{
				//delay();
    	        		close(client_sockfd);			// Otherwise, we must be the parent and our work for this client is finished.  
    	    		}
    	}
}
	
void delay()
{
int i,j;
for (i=0;i<=100;i++)
{
for (j=0;j<=50;j++);
}
}
	
