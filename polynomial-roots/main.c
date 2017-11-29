#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int main () {
    int i;
    pid_t pid[3], wpid;
    float delta, raiz, x1, x2, a, b, c;
    int returnStatusDelta, status;

    scanf ("%f %f %f", &a, &b, &c);

    for (i = 0; i < 3; i++) {
        pid[i] = fork();
        if (pid[i] < 0) {
            perror ("fork");
            return 1;
        }
    }

    if (pid[0] == 0) {
        printf("\n=====\nProcesso %d: Calcular descriminante\n=====\n", getpid());
        delta = b*b-4*a*c;
        printf("delta = %.2f\n\n", delta);
        raiz = sqrt(delta);
        if (delta < 0)
            return 1;
        return 0;
    }
    if (pid[1] == 0) {
        waitpid(pid[0], &returnStatusDelta, 0);
        if (returnStatusDelta == 1)
            return 1;
        else {
            printf("\n=====\nProcesso %d: Calcular primeira raiz\n=====\n", getpid());
            x1 = (-b + raiz)/2;
            printf("%.2f = (-%.2f + %.2f) / 2\n\n", x1, b, raiz);
            return 0;
        }
    }
    if (pid[2] == 0) {
        waitpid(pid[0], &returnStatusDelta, 0);
        if (returnStatusDelta == 1)
            return 1;
        printf("\n=====\nProcesso %d: calcular segunda raiz\n=====\n", getpid());
        x2 = (-b - raiz)/2;
        printf("%.2f = (-%.2f - %.2f) / 2\n\n", x2, b, raiz);
        return 0;
    }
    else {
        while ((wpid = wait(&status)) > 0);
        printf("pid do Pai: %d\n", getpid());
        printf("%.2f %.2f %.2f\n", delta, x1, x2 );
    }
    return 0;
}
