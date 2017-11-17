#include <unistd.h>

int main() {
  char *args[] = {"/bin/ls", "-lha", "--color", (char *) 0};
  execve("/bin/ls", args, NULL);
}
