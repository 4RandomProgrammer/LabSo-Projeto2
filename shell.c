#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 256

int main() {
  char comando[MAX];
  char argv[MAX][100];
  int pid;

  while (1) {
    printf("> ");
    fgets(comando, MAX, stdin);
    printf("TESTE: %s", comando);
    if (!strcmp(comando, "exit")) {
      exit(EXIT_SUCCESS);
    }
    
    strcpy(argv[0], strtok(comando, " "));
    int argc = 1;
    char *temp_arg;
    while (1) {
      temp_arg = strtok(NULL, " ");
      if (!temp_arg)
        break;
      
      strcpy(argv[argc], temp_arg);
      argc++;
    }
    
    for (int j = 0; j < argc; j++)
      printf("%s\n", argv[j]);

    pid = fork();
    if (pid) {
      if (argc <= 1 || argumento[1][0] == "&")
        waitpid(pid, NULL, 0); 
    } else {
      execlp(argv[0], argv[0], NULL);
      printf("Erro ao executar comando!\n");
      exit(EXIT_FAILURE);
    }
  }
}
