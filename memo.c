#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024
#define MAX_PID 8

int main()
{
    int fd;
    
    char *myfifo = "myfifo";
    char *prime = "prime.txt";
    int number;

    fd = open(myfifo, O_RDONLY);
    FILE *fp = fopen(prime, "w");

    if (fp == NULL)
    {
        printf("MEMO SAY: ERRORE NELL'APERTURA DEL FILE DI SCRITTURA %s", prime);
        return -1;
    }

    while (1) {
        if ((read(fd, &number, sizeof(number))) > 0) {
            printf("MEMO SAY: RICEVUTO: %d\n", number);
            
            fprintf(fp, "%d\n", number);
            printf("MEMO SAY: ..... E SCRITTO NEL FILE!\n\n");
            
        } else
            break;
    }
    close(fd);

    return 0;
}
