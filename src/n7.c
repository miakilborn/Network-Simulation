#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "data.h"

#define MAX_BUF 1024

int main()
{
	int pipe6;
	char * link6 = "/tmp/link6";
	char buf[MAX_BUF];

	mkfifo(link6, 0666);

	while(true){
		pipe6 = open(link6, O_RDONLY);
		read(pipe6, buf, MAX_BUF);
		close(pipe6);

		if(strcmp(buf,"START") == 0){
			
			printf("[N7]== START of FILE ==\n");

		} else if(strcmp(buf,"STOP") == 0){
			
			printf("\n[N7]== END of FILE ==\n");
		
			pipe6 = open(link6, O_WRONLY);
			write(pipe6, "STOP", sizeof("STOP"));
			close(pipe6);

			continue;

		} else if(strcmp(buf,"KILL") == 0){
			exit(0);

		} else if(strcmp(buf, "INIT")==0){
			printf("[N7]INIT\n");
			
		} else {
			printf("%c", buf[0]);
			fflush(stdout);
		}

		pipe6 = open(link6, O_WRONLY);
		write(pipe6, "ACK", sizeof("ACK"));
		close(pipe6);
	}
	
	return(0);
}
