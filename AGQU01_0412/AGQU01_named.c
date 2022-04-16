
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd, nbytes;
    pid_t childpid;
    char readbuffer[80];
    char string[] = "Zsigó Bence\n";

    if((childpid = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }

    char * AGQU01 = "/tmp/AGQU01";

    mkfifo(AGQU01, 0666);

    if(childpid == 0)
    {
        fd = open(AGQU01, O_WRONLY);
        printf("Child: Most irok a csovezetekbe!\n");
        write(fd, string, (strlen(string)+1));
        printf("Child: Sikeresen beirtam a csovezetekbe!\n");
        close(fd);
        exit(0);
    }
    else
    {
        fd = open(AGQU01, O_RDONLY);
        wait(NULL);
        printf("Parent: Elkezdem kiolvasni a csovezetekbe irt szoveget!\n");
        read(fd, readbuffer, sizeof(readbuffer));
        printf("Parent: Sikerult kiolvasnom a csovezetekbol a szoveget!\n");
        printf("%s", readbuffer);
        close(fd);
    }
    return 0;
}




