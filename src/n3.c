#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "data.h"

#define MAX_BUF 1024

void sendL4(char*);
void sendL5(char*);
void sendL6(char*);
void kill();

int dest;

int main()
{
	int pipe2;
	char * link2 = "/tmp/link2";
	char buf[MAX_BUF];
	char temp[2];

	mkfifo(link2, 0666);

	while(true){
		pipe2 = open(link2, O_RDONLY);
		read(pipe2, buf, MAX_BUF);
		close(pipe2);

		if(strlen(buf) == 2){
			
			temp[0] = buf[1];
			dest = atoi(temp);

			pipe2 = open(link2, O_WRONLY);
			write(pipe2, buf, sizeof(char) * (strlen(buf)+1));
			close(pipe2);

			continue;

		} else if(strcmp(buf,"KILL") == 0){

			break;

		} else if(strcmp(buf,"START") == 0){

			if(dest == 3){
				printf("[N3]== START of FILE ==\n");
			} else if(dest == 5){
				sendL4("START");
			} else if(dest == 6){
				sendL5("START");
			} else if(dest == 7){
				sendL6("START");
			}

		} else if(strcmp(buf,"STOP") == 0){

			if(dest == 3){
				printf("\n[N3]== END of FILE ==\n");
			} else if(dest == 5){
				sendL4("STOP");
			} else if(dest == 6){
				sendL5("STOP");
			} else if(dest == 7){
				sendL6("STOP");
			}

			pipe2 = open(link2, O_WRONLY);
			write(pipe2, "STOP", sizeof("STOP"));
			close(pipe2);

			continue;

		} else if(strcmp(buf, "INIT")==0){
			sendL4("INIT");
			sendL5("INIT");
			sendL6("INIT");
			printf("[N3]INIT\n");
		}  else {
	
			if(dest == 3){
				printf("%c", buf[0]);
				fflush(stdout);
			} else if(dest == 5){
				sendL4(buf);
			} else if(dest == 6){
				sendL5(buf);
			} else if(dest == 7){
				sendL6(buf);
			}

		}

		pipe2 = open(link2, O_WRONLY);
		write(pipe2, "ACK", sizeof("ACK"));
		close(pipe2);
	}

	kill();
	return 0;
}

void sendL4(char* packet){
	int pipe4;
	char* link4 = "/tmp/link4";
	char buf[MAX_BUF];

	mkfifo(link4, 0666);
	
	pipe4 = open(link4, O_WRONLY);
	write(pipe4, packet, sizeof(char) * (strlen(packet) + 1));
	close(pipe4);

	pipe4 = open(link4, O_RDONLY);
	read(pipe4, buf, MAX_BUF);
	close(pipe4);
}

void sendL5(char* packet){
	int pipe5;
	char* link5 = "/tmp/link5";
	char buf[MAX_BUF];

	mkfifo(link5, 0666);
	
	pipe5 = open(link5, O_WRONLY);
	write(pipe5, packet, sizeof(char) * (strlen(packet) + 1));
	close(pipe5);

	pipe5 = open(link5, O_RDONLY);
	read(pipe5, buf, MAX_BUF);
	close(pipe5);
}

void sendL6(char* packet){
	int pipe6;
	char* link6 = "/tmp/link6";
	char buf[MAX_BUF];

	mkfifo(link6, 0666);
	
	pipe6 = open(link6, O_WRONLY);
	write(pipe6, packet, sizeof(char) * (strlen(packet) + 1));
	close(pipe6);

	pipe6 = open(link6, O_RDONLY);
	read(pipe6, buf, MAX_BUF);
	close(pipe6);
}

void kill(){
	int pipe4, pipe5, pipe6;
	
	char* link4;
	char* link5;
	char* link6;

	link4 = "/tmp/link4";
	link5 = "/tmp/link5";
	link6 = "/tmp/link6";

	mkfifo(link4, 0666);
	mkfifo(link5, 0666);
	mkfifo(link6, 0666);

	pipe4 = open(link4, O_WRONLY);
	write(pipe4, "KILL", sizeof("KILL"));
	close(pipe4);

	pipe5 = open(link5, O_WRONLY);
	write(pipe5, "KILL", sizeof("KILL"));
	close(pipe5);

	pipe6 = open(link6, O_WRONLY);
	write(pipe6, "KILL", sizeof("KILL"));
	close(pipe6);

	exit(0);
}
