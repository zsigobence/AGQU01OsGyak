#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>


void exit(int status);
void abort(void);

int main(void)
{
    int pid;
    int status;
    if ((pid = fork()) < 0) perror("fork error");
    else if (pid == 0) exit(7);

    if (wait(&status) != pid)
        perror("wait error");

    if (WIFEXITED(status))
        printf("Normal visszateresi ertek = %d\n", WEXITSTATUS(status));

    if ( (pid = fork()) < 0) perror("fork error");
    else if (pid == 0)
    abort();

    if (wait(&status) != pid) perror("wait error");
    if (WIFSIGNALED(status))
        printf("Abnormal visszateresi ertek = %d\n", WTERMSIG(status));

    return 0;
}
