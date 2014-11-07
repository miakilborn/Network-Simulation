#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "data.h"

#define MAX_BUF 1024

int main()
{
	int pipe4;
	char * link4 = "/tmp/link4";
	char buf[MAX_BUF];

	mkfifo(link4, 0666);

	while(true){
		pipe4 = open(link4, O_RDONLY);
		read(pipe4, buf, MAX_BUF);
		close(pipe4);

		if(strcmp(buf,"START") == 0){
			
			printf("[N5]== START of FILE ==\n");

		} else if(strcmp(buf,"STOP") == 0){
			
			printf("\n[N5]== END of FILE ==\n");
			
			pipe4 = open(link4, O_WRONLY);
			write(pipe4, "STOP", sizeof("STOP"));
			close(pipe4);

			continue;

		} else if(strcmp(buf,"KILL") == 0){
			exit(0);

		} else if(strcmp(buf, "INIT")==0){
			printf("[N5]INIT\n");
			
		} else {
			printf("%c", buf[0]);
			fflush(stdout);
		}

		pipe4 = open(link4, O_WRONLY);
		write(pipe4, "ACK", sizeof("ACK"));
		close(pipe4);
	}
	
	return(0);
}
