#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "data.h"

#define MAX_BUF 1024

allData getAllData();
void intHandler(int);
void sendAllData(allData);
void processData(allData);
void sendL1(allData data);
void sendL2(allData data);
void getData(allData*);
boolean validFile(char*);
boolean validNode(char*);
void exitProcesses();
void init();

boolean verbose = false;

int main(int argc, char **argv){
	allData data;
	char* cont;

	cont = malloc(sizeof(char) * 2);
	signal(SIGINT, intHandler);

	init();

	while(true){
		data = getAllData();
		sendAllData(data);
		
		printf("Do you wish to send another message (Y/N): ");
		scanf("%s", cont);

		if((cont[0] == 'N') || (cont[0] == 'n')){
			printf("Exiting.\n");
			exitProcesses();
			break;
		} else if((cont[0] == 'Y') || (cont[0] == 'y')) {
			continue;
		} else {
			printf("Bad input. Exiting...\n");
			exitProcesses();
			break;
		}
	}

	return(0);
}

void init(){
	char* link1 = "/tmp/link1";
	char* link2 = "/tmp/link2";
	int pipe1, pipe2;
	char buf[MAX_BUF];

	mkfifo(link1, 0666);
	mkfifo(link2, 0666);

	printf("[N1]INIT\n");

	pipe1 = open(link1, O_WRONLY);
	write(pipe1, "INIT", sizeof("INIT"));
	close(pipe1);

	pipe1 = open(link1, O_RDONLY);
	read(pipe1, buf, MAX_BUF);
	close(pipe1);

	pipe2 = open(link2, O_WRONLY);
	write(pipe2, "INIT", sizeof("INIT"));
	close(pipe2);

	pipe2 = open(link2, O_RDONLY);
	read(pipe2, buf, MAX_BUF);
	close(pipe2);

}

void intHandler(int dummy) {
	printf("\nEnding.\n");
	exitProcesses();
	exit(0);
}

allData getAllData(){
	allData data;

	data.fileName = malloc(sizeof(char) * 21);
	data.nodeName = malloc(sizeof(char) * 3);

	printf("File name can be no longer than 20 chars, node can be no longer than 2 chars.\n");
	printf("Please enter file and destination node (test.txt n2): ");
	scanf("%s %s", data.fileName, data.nodeName);

	if(validNode(data.nodeName)){
		char temp[2];
		temp[0] = data.nodeName[1];
		temp[1] = '\0';

		data.nodeNum = atoi(temp);
	} else {
		printf("Bad node input. Destination node should be in the format 'N2' between N1 and N7. Exiting.\n");
		exitProcesses();
		exit(1);
	}

	if(!validFile(data.fileName)){
		printf("The file: %s could not be opened. Ensure path, name and extension are correct. Exiting.\n", data.fileName);
		exitProcesses();
		exit(1);
	}

	/*parse file for data*/
	getData(&data);

	return data;
}

void sendAllData(allData data){
	switch(data.nodeNum){
		case 1:
			processData(data);
			break;
		case 2:
		case 4:
			sendL1(data);
			break;
		case 3:
		case 5:
		case 6:
		case 7:
			sendL2(data);
			break;
		default:
			return;
	}
}

void processData(allData data){
	int i, max;
	packet p;
	i = 0;
	max = data.dataQ->length;

	printf("[N1]== START of FILE ==\n");
	for(i=0; i<max; i++){
		p = pop(data.dataQ)->data;
		printf("%c", p[0]);
	}
	printf("\n[N1]== END of FILE ==\n");
}

void sendL1(allData data){
	int pipe1;
	char* link1 = "/tmp/link1";
	int i, max;
	packet p;
	char buf[MAX_BUF];
	int delay = 0;
	
	i = 0;
	max = data.dataQ->length;

	mkfifo(link1, 0666);

	pipe1 = open(link1, O_WRONLY);
	write(pipe1, data.nodeName, sizeof(char) * (strlen(data.nodeName)+1));
	close(pipe1);

	pipe1 = open(link1, O_RDONLY);
	read(pipe1, buf, MAX_BUF);
	close(pipe1);

	pipe1 = open(link1, O_WRONLY);
	write(pipe1, "START", sizeof("START"));
	close(pipe1);

	pipe1 = open(link1, O_RDONLY);
	read(pipe1, buf, MAX_BUF);
	close(pipe1);
	
	for(i=0; i<max; i++){

		srand(time(NULL));
		delay = (rand() % 1999) + 1;
		delay = delay * 1000;

		/*printf("\t[N1]Network delay: %d milliseconds ...\n", delay/1000);*/
		usleep(delay);
		
		pipe1 = open(link1, O_WRONLY);
		p = pop(data.dataQ)->data;
		write(pipe1, p, sizeof(char) * (strlen(p)+1));
		close(pipe1);

		pipe1 = open(link1, O_RDONLY);
		read(pipe1, buf, MAX_BUF);
		/*printf("\t[N1]Received: %s\n", buf);*/
		close(pipe1);
	
	}

	pipe1 = open(link1, O_WRONLY);
	write(pipe1, "STOP", sizeof("STOP"));
	close(pipe1);

	pipe1 = open(link1, O_RDONLY);
	read(pipe1, buf, MAX_BUF);
	printf("[N1]Received: %s\n", buf);
	close(pipe1);

}

void sendL2(allData data){
	int pipe2;
	char* link2 = "/tmp/link2";
	int i, max;
	packet p;
	char buf[MAX_BUF];
	int delay = 0;
	
	i = 0;
	max = data.dataQ->length;

	mkfifo(link2, 0666);

	pipe2 = open(link2, O_WRONLY);
	write(pipe2, data.nodeName, sizeof(char) * (strlen(data.nodeName)+1));
	close(pipe2);

	pipe2 = open(link2, O_RDONLY);
	read(pipe2, buf, MAX_BUF);
	close(pipe2);

	pipe2 = open(link2, O_WRONLY);
	write(pipe2, "START", sizeof("START"));
	close(pipe2);

	pipe2 = open(link2, O_RDONLY);
	read(pipe2, buf, MAX_BUF);
	close(pipe2);
	
	for(i=0; i<max; i++){

		srand(time(NULL));
		delay = (rand() % 1999) + 1;
		delay = delay * 1000;

		/*printf("\t[N1]Network delay: %d milliseconds ...\n", delay/1000);*/
		usleep(delay);
		
		pipe2 = open(link2, O_WRONLY);
		p = pop(data.dataQ)->data;
		write(pipe2, p, sizeof(char) * (strlen(p)+1));
		close(pipe2);

		pipe2 = open(link2, O_RDONLY);
		read(pipe2, buf, MAX_BUF);
		/*printf("\t[N1]Received: %s\n", buf);*/
		close(pipe2);
	
	}

	pipe2 = open(link2, O_WRONLY);
	write(pipe2, "STOP", sizeof("STOP"));
	close(pipe2);

	pipe2 = open(link2, O_RDONLY);
	read(pipe2, buf, MAX_BUF);
	printf("[N1]Received: %s\n", buf);
	close(pipe2);

}

void getData(allData* data){
	FILE* fp;
	char temp;
	packet p;

	fp = fopen(data->fileName, "r");

	/*Initialize the queue*/
	data->dataQ = createList();

	while((temp = fgetc(fp)) != EOF){
		p = malloc(sizeof(char) * 4);
		p[0] = temp;
		p[1] = data->nodeName[0];
		p[2] = data->nodeName[1];
		push(data->dataQ, p);
	}

	fclose(fp);
}

boolean validFile(char* fileName){
	FILE* fp;
	fp = fopen(fileName, "r");
	if(fp == NULL){
		return false;
	} else{
		fclose(fp);
		return true;
	}
}

boolean validNode(char* nodeString){
	if((strcmp(nodeString, "N1") == 0) || (strcmp(nodeString, "n1") == 0)){
		return true;
	} else if((strcmp(nodeString, "N2") == 0) || (strcmp(nodeString, "n2") == 0)){
		return true;
	} else if((strcmp(nodeString, "N3") == 0) || (strcmp(nodeString, "n3") == 0)){
		return true;
	} else if((strcmp(nodeString, "N4") == 0) || (strcmp(nodeString, "n4") == 0)){
		return true;
	} else if((strcmp(nodeString, "N5") == 0) || (strcmp(nodeString, "n5") == 0)){
		return true;
	} else if((strcmp(nodeString, "N6") == 0) || (strcmp(nodeString, "n6") == 0)){
		return true;
	} else if((strcmp(nodeString, "N7") == 0) || (strcmp(nodeString, "n7") == 0)){
		return true;
	} else {
		return false;
	}
}

void exitProcesses(){
	/*TODO*/
	int pipe1;
	int pipe2;
	char* link1;
	char* link2;

	link1 = "/tmp/link1";
	mkfifo(link1, 0666);

	pipe1 = open(link1, O_WRONLY);
	write(pipe1, "KILL", sizeof("KILL"));
	close(pipe1);

	link2 = "/tmp/link2";
	mkfifo(link2, 0666);

	pipe2 = open(link2, O_WRONLY);
	write(pipe2, "KILL", sizeof("KILL"));
	close(pipe2);

	exit(0);
}
