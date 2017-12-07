#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int main () {
    int i;
    int fd[2];
    pid_t pid[3];
    float a, b, c;

    printf ("Valores de 'a', 'b' e 'c': ");
    scanf ("%f %f %f", &a, &b, &c);

    //for (i = 0; i < 3; i++) {
        if (pipe(fd) < 0) {
            perror("pipe") ;
            return -1 ;
        }
    //}

    for (i = 0; i < 3; i++) {
        pid[i] = fork();
        if (pid[i] < 0) {
            perror ("fork");
            exit(1);
        } else if (pid[i] == 0)
            break;
    }

    if (pid[0] == 0) {
        close(fd[0]); // Bloqueando leitura
        float delta, raiz;
        float *p = &raiz;

        printf("\n===== Processo %d: Calcular descriminante =====\n", getpid());

        delta = b*b-4*a*c;
        printf ("Calculando: %.0f = %.0f^2 - 4*%.0f*%.0f\n", delta, b, a, c);

        if (delta < 0)
            exit (1);
        raiz = sqrt(delta);

        write(fd[1], p, sizeof(float));
        printf("Enviando valor da raiz quadrado do delta: %.2f\n", *p);

        exit (0);
    }
    if (pid[1] == 0) {
        close(fd[1]); // Bloqueando escrita
        float x;
        float *raiz;

        printf("\n===== Processo %d: Calcular primeira raiz =====\n", getpid());

        read(fd[0], raiz, sizeof(float));
        printf("Recebendo valor da raiz: %f\n", *raiz);

        x = (-b + (*raiz))/2;
        printf("Primeira Raiz = %f\n", x);

        exit(0);
    }
    /*if (pid[2] == 0) {
        close(fd[0][1]);
        float x;
        float *raiz;
        float *ponteiro = &x;

        printf("\n===== Processo %d: calcular segunda raiz =====\n", getpid());
        x2 = (-b - raiz)/2;
        exit(0);
    }*/
    else {
        //printf("\n===== Processo %d: PAI =====\n", getpid());
        //printf("Raiz 1 = %d\nRaiz 2 = %d\n", x1, x2);
    }
    return 0;
}
