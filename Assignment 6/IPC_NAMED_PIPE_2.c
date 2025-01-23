#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ipc.h>
#define DATASIZE 64
int main() {
	mkfifo("./myfifo2",0666|IPC_CREAT);
	char data3[DATASIZE];
	char data4[DATASIZE];
	char data5[DATASIZE];
	int fd = open("./myfifo1",O_RDONLY);
	read(fd,data3,DATASIZE);
	read(fd,data4,DATASIZE);
        if(strcmp(data3,data4) == 0) {
		strcpy(data5, "SAME");
	}
	else {
		strcpy(data5, "NOT SAME");
	}
	int fd2 = open("./myfifo2",O_WRONLY);
	write(fd2,data5,strlen(data5)+1);
	close(fd);
	close(fd2);
	return 0;
}
