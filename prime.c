#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int number, n;
int fp;

void* numeroprimo(void* name)
{

    int* th = (int*)name;
    int mynumber;

    while (pthread_mutex_lock(&mutex), mynumber = number++, pthread_mutex_unlock(&mutex), mynumber <= n)
    {

        int check = 0;

        for (int i = 2; i <= mynumber / 2; i++)
        {
            if (mynumber % i == 0)
            {
                printf("CALC SAY: %d NON è un numero primo \n", mynumber);
                check = 1;
                break;
            }
        }

        if (check == 0)
        {
            printf("\nCALC SAY: %d è un numero primo , lo invio al memorizzatore\n\n", mynumber);
            write(fp, &mynumber, sizeof(mynumber));
        }
    }
}

int main(int argc, char* argv[])
{
    char* fifo = "myfifo";

    if (argc != 2)
    {
        printf("CALC SAY: PARAMETRI ERRATI\n ");
        return -1;
    }

    int error;
    n = atoi(argv[1]);
    pthread_t t1, t2, t3;
    pthread_t* calc_arr[3] = { &t1, &t2, &t3 }; //array per l'id dei thread

    if (error = mkfifo(fifo, 0666) == -1)
    {
        printf("CALC SAY: PIPE ERROR \n");
        perror(fifo);
        if (errno != EEXIST)
        {
            return -1;
        }
    }

    if ((fp = open(fifo, O_WRONLY)) == -1)
    {

        perror(fifo);
        return 1;
    }

    int thread[] = { 1, 2, 3 };

    for (int i = 0; i < 3; i++)
    {
        printf("CALC SAY: Creazione Thread...\n");

        if (error = pthread_create(calc_arr[i], NULL, numeroprimo, &thread[i]) != 0)
        {
            perror("CALC SAY: ERROR THREAD CREATION");
            exit(1);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (error = pthread_join(*calc_arr[i], NULL) != 0)
        {
            perror("CALC SAY: ERROR THREAD JOIN/n");
            exit(1);
        }
    }

    close(fp);
    printf("CALC SAY: Chiusura dei calcolatori...\n");
    return 0;
}
