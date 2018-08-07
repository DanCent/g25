#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>


#define PORT 8080


char studid[20];

int main(int argc, char *argv[])
{

	
	int sockfd;
	//int PORT; 
	int rcv_bytes = 0;
	struct sockaddr_in serv_addr;
         pid_t childpid;
    time_t timer;
    char buffer[26],user[1024];
    struct tm* tm_info;
	char task[1024],feedback[1024];
	int result;

	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket Failed!");
		exit(EXIT_FAILURE);
	}

	
	memset(&serv_addr, '\0', sizeof(serv_addr));

	//PORT = atoi(argv[2]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
        serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) < 0)
	{
		perror("Invalid Address or Address is in use!");
		exit(EXIT_FAILURE);
	}

	bzero(&(serv_addr.sin_zero), 8);

	
    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    puts(buffer);
	
	
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Connection Failed !");
		exit(EXIT_FAILURE);
	}

	
	printf("\nEnter id: \n");

	fgets(user,1024,stdin);

	send(sockfd,user,strlen(user), 0);

	puts("Terminate your connection with 'q'.");
	puts("Endeavour to terminate each command with semi colon ie [Command][Values][;]");

	while(1)
	{
		int recieved;
		printf("\nEnter Task:");
		fgets(task,1024,stdin);

		send(sockfd,task,strlen(task), 0);
        
      
   if(task[0] !='q'){
     
			read(sockfd,&recieved,sizeof(int));
			printf("%d\n",recieved);
      
       
			for(int i=0;i < recieved;i++)
			{
				memset(feedback,0,sizeof(feedback));
				//the number of times to receive from the server before closing the socket
				result = read(sockfd,feedback,1024);

				feedback[result] = '\0';
				printf("%s \n",feedback);
			}
         
       
		}
       
		 if(task[0] =='q')
		{
			close (sockfd);
			printf("Connection lost.\n");
			break;
		}
	}

	return (0);
}
