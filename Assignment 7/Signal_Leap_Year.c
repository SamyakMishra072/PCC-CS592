#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int leap(int y) {
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        return 1; // Leap year
    }
    return 0; // Not a leap year
}

void handle_signal(int sig) {
    int y;
    printf("\nChild Process received SIGUSR1. Enter a year to check: ");
    scanf("%d", &y);

    if (leap(y)) {
        printf("%d is a leap year.\n", y);
    } else {
        printf("%d is NOT a leap year.\n", y);
    }
}

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("FORK FAILED");
        exit(1);
    } else if (pid == 0) {
        signal(SIGUSR1, handle_signal);
        printf("Child Process Started and waiting for SIGUSR1 from Parent.\n");
        while (1) {
            pause();
        }
    } else {
        printf("Parent Process has Started and is Sending SIGUSR1 to the child every 5 seconds.\n");
        while (1) {
            sleep(5);
            kill(pid, SIGUSR1);
            printf("\nSIGUSR1 HAS BEEN SENT TO THE CHILD BY PARENT.\n");
        }
    }

    return 0;
}
