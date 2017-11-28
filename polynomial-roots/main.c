#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int i;
    pid_t pid[3];
    float delta, x1, x2;
    int a, b, c;

    scanf("%d %d %d", &a, &b, &c);

    for(i=0;i<3;i++) {
        pid[i] = fork();
        if (pid[i] < 0)
        {
            perror("fork");
            return 1;
        }
    }

    if (pid[0] == 0)
    {
        //O código aqui dentro será executado no processo filho
        printf("pid do Filho: %d\n", getpid());
        delta = b*b-4*a*c;;
    }
    if (pid[1] == 0)
    {
        //O código aqui dentro será executado no processo filho
        printf("pid do Filho: %d\n", getpid());
        x1 = (-b + sqrt(delta))/2;
    }
    if (pid[2] == 0)
    {
        //O código aqui dentro será executado no processo filho
        printf("pid do Filho: %d\n", getpid());
        x2 = (-b - sqrt(delta))/2;
    }
    else
    {
        //O código neste trecho será executado no processo pai
        printf("pid do Pai: %d\n", getpid());
    }


    printf("Esta regiao sera executada por ambos processos\n\n");
    printf("%f %f %f\n", delta, x1, x2 );
    return 0;
}
