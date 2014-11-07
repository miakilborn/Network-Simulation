#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "data.h"

#define MAX_BUF 1024

int main()
{
	int pipe5;
	char * link5 = "/tmp/link5";
	char buf[MAX_BUF];

	mkfifo(link5, 0666);

	while(true){
		pipe5 = open(link5, O_RDONLY);
		read(pipe5, buf, MAX_BUF);
		close(pipe5);

		if(strcmp(buf,"START") == 0){
			
			printf("[N6]== START of FILE ==\n");

		} else if(strcmp(buf,"STOP") == 0){
			
			printf("\n[N6]== END of FILE ==\n");
			
			pipe5 = open(link5, O_WRONLY);
			write(pipe5, "STOP", sizeof("STOP"));
			close(pipe5);

			continue;

		} else if(strcmp(buf,"KILL") == 0){
			exit(0);

		} else if(strcmp(buf, "INIT")==0){
			printf("[N6]INIT\n");
			
		} else {
			printf("%c", buf[0]);
			fflush(stdout);
		}

		pipe5 = open(link5, O_WRONLY);
		write(pipe5, "ACK", sizeof("ACK"));
		close(pipe5);
	}
	
	return(0);
}
