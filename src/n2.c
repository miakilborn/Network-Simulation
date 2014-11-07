#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "data.h"

#define MAX_BUF 1024

void sendL3(char*);
void kill(void);

int dest;

int main(void)
{
	int pipe1;
	char * link1 = "/tmp/link1";
	char buf[MAX_BUF];
	char temp[2];

	mkfifo(link1, 0666);

	while(true){

		pipe1 = open(link1, O_RDONLY);
		read(pipe1, buf, MAX_BUF);
		close(pipe1);

		if(strlen(buf) == 2){
			
			temp[0] = buf[1];
			dest = atoi(temp);
	
			pipe1 = open(link1, O_WRONLY);
			write(pipe1, buf, sizeof(char) * (strlen(buf)+1));
			close(pipe1);

			continue;
	
		} else if(strcmp(buf,"KILL")==0){

			break;

		} else if(strcmp(buf,"START")==0){

			if(dest == 2){
				printf("[N2]== START of FILE ==\n");
			} else{
				sendL3("START");
			}

		} else if(strcmp(buf,"STOP")==0){

			if(dest == 2){
				printf("\n[N2]== END of FILE ==\n");
			} else{
				sendL3("STOP");
			}

			pipe1 = open(link1, O_WRONLY);
			write(pipe1, "STOP", sizeof("STOP"));
			close(pipe1);

			continue;

		} else if(strcmp(buf, "INIT")==0){
			sendL3("INIT");
			printf("[N2]INIT\n");
		} else{

			if(dest == 2){
				printf("%c", buf[0]);
				fflush(stdout);
			} else {
				sendL3(buf);
			}

		}

		pipe1 = open(link1, O_WRONLY);
		write(pipe1, "ACK", sizeof("ACK"));
		close(pipe1);
	}

	kill();
	return(0);
}

void sendL3(char* packet){
	int pipe3;
	char* link3 = "/tmp/link3";
	char buf[MAX_BUF];

	mkfifo(link3, 0666);
	
	pipe3 = open(link3, O_WRONLY);
	write(pipe3, packet, sizeof(char) * (strlen(packet) + 1));
	close(pipe3);

	pipe3 = open(link3, O_RDONLY);
	read(pipe3, buf, MAX_BUF);
	close(pipe3);
}

void kill(void){
	int pipe3;
	char* link3 = "/tmp/link3";

	mkfifo(link3, 0666);

	pipe3 = open(link3, O_WRONLY);
	write(pipe3, "KILL", sizeof("KILL"));
	close(pipe3);

	exit(0);
}
