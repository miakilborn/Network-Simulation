#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "data.h"

#define MAX_BUF 1024

int main()
{
	int pipe3;
	char * link3 = "/tmp/link3";
	char buf[MAX_BUF];

	mkfifo(link3, 0666);

	while(true){
		pipe3 = open(link3, O_RDONLY);
		read(pipe3, buf, MAX_BUF);
		close(pipe3);

		if(strcmp(buf,"START") == 0){
			
			printf("[N4]== START of FILE ==\n");

		} else if(strcmp(buf,"STOP") == 0){
			
			printf("\n[N4]== END of FILE ==\n");
			
			pipe3 = open(link3, O_WRONLY);
			write(pipe3, "STOP", sizeof("STOP"));
			close(pipe3);

			continue;

		} else if(strcmp(buf,"KILL") == 0){
			exit(0);

		} else if(strcmp(buf, "INIT")==0){
			printf("[N4]INIT\n");
			
		} else {
			printf("%c", buf[0]);
			fflush(stdout);
		}

		pipe3 = open(link3, O_WRONLY);
		write(pipe3, "ACK", sizeof("ACK"));
		close(pipe3);
	}

	return(0);
}
