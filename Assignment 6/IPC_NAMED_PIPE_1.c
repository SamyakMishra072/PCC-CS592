//1st File 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define DATASIZE 64
int main() {
	mkfifo("./myfifo1", 0666|IPC_CREAT);
	char data1[DATASIZE];
	char data2[DATASIZE];
	char data6[DATASIZE];
	printf("Enter the two strings : \n");
	fgets(data1,DATASIZE,stdin);
	fgets(data2,DATASIZE,stdin);
	int fd = open("./myfifo1",O_WRONLY);
	write(fd,data1,strlen(data1)+1);
	write(fd,data2,strlen(data2)+1);
	int fd2 = open("./myfifo2", O_RDONLY);
	read(fd2,data6,DATASIZE);
	printf("The two strings are : ");
	printf("%s\n",data6);
	close(fd);
	close(fd2);
	return 0;
}
