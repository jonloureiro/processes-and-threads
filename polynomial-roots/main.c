#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int main () {
    int i;
    int fd[4][2];
    pid_t pid[3];
    float a, b, c;

    printf ("Valores de 'a', 'b' e 'c': ");
    scanf ("%f %f %f", &a, &b, &c);

    for (i = 0; i < 4; i++) {
        if (pipe(fd[i]) < 0) {
            perror("pipe") ;
            return -1 ;
        }
    }

    for (i = 0; i < 3; i++) {
        pid[i] = fork();
        if (pid[i] < 0) {
            perror ("fork");
            exit(1);
        } else if (pid[i] == 0) {
            break;
        }
    }

    if (pid[0] == 0) {
        close(fd[0][0]); // Bloqueando leitura
        close(fd[1][0]); // Bloqueando leitura
        int id = getpid();
        float delta, raiz;

        printf("===== Processo %d: Calcular descriminante =====\n", id);

        delta = b*b-4*a*c;
        printf ("%d: Calculando descriminante: %.0f\n", id, delta);

        if (delta < 0)
            exit (1);
        raiz = sqrt(delta);

        printf("%d: Enviando valor da raiz quadrado do descriminante: %.2f\n", id, raiz);
        write(fd[0][1], &raiz, sizeof(raiz));
        write(fd[1][1], &raiz, sizeof(raiz));

        exit (0);
    }
    if (pid[1] == 0) {
        close(fd[0][1]); // Bloqueando escrita
        close(fd[2][0]); // Bloqueando leitura
        int id = getpid();
        float x, raiz;

        printf("===== Processo %d: Calcular primeira raiz =====\n", id);

        printf("%d: Esperando valor da raiz quadrada do descriminante\n", id);
        read(fd[0][0], &raiz, sizeof(raiz));
        printf("%d: Recebendo valor da raiz quadrada do descriminante: %.2f\n", id, raiz);

        x = (-b + raiz)/2;

        printf("%d: Enviando valor da primeira Raiz = %.2f\n", id, x);
        write(fd[2][1], &x, sizeof(x));

        exit(0);
    }
    if (pid[2] == 0) {
        close(fd[1][1]); // Bloqueando escrita
        close(fd[3][0]); // Bloqueando leitura
        int id = getpid();
        float x, raiz;

        printf("===== Processo %d: calcular segunda raiz =====\n", id);

        printf("%d: Esperando valor da raiz quadrada do descriminante\n", id);
        read(fd[1][0], &raiz, sizeof(raiz));
        printf("%d: Recebendo valor da raiz quadrada do descriminante: %.2f\n", id, raiz);

        x = (-b - raiz)/2;

        printf("%d: Enviando valor da segunda Raiz = %.2f\n", id, x);
        write(fd[3][1], &x, sizeof(x));

        exit(0);
    }
    else {
        close(fd[2][1]); // Bloqueando escrita
        close(fd[3][1]); // Bloqueando escrita
        int id = getpid();
        float x1, x2;

        printf("===== Processo %d: PAI =====\n", id);

        printf("%d: Esperando valor da primeira Raiz\n", id);
        read(fd[2][0], &x1, sizeof(x1));
        printf("%d: Recebendo valor da primeira Raiz = %.2f\n", id, x1);

        printf("%d: Esperando valor da segunda Raiz\n", id);
        read(fd[3][0], &x2, sizeof(x2));
        printf("%d: Recebendo valor da segunda Raiz = %.2f\n", id, x2);
    }
    return 0;
}
