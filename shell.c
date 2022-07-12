#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 256
#define MAX_ARGS 100

enum input_mode{NORMAL, INPUT, OUTPUT};

int main() {
    char comando[MAX];
    char argv[MAX][MAX_ARGS];
    char input_path[MAX];
    char output_path[MAX];
    int pid;

    while (1) {
        // Input
        printf("> ");
        fgets(comando, MAX, stdin);
        comando[strlen(comando)-1] = '\0';
        if (!strcmp(comando, "exit")) {
            exit(EXIT_SUCCESS);
        }
        
        // Divisão dos args
        strcpy(argv[0], strtok(comando, " "));
        int argc = 1;
        char *temp_arg;
        
        int arg_type = NORMAL;
        input_path[0] = '\0';
        output_path[0] = '\0';
        while (1) {
            temp_arg = strtok(NULL, " ");
            if (!temp_arg)
                break;
            
            if (temp_arg[0] == '<') {
                arg_type = INPUT;
            } else if (temp_arg[0] == '>') {
                arg_type = OUTPUT;
            } else {
                switch (arg_type) {
                    case NORMAL:
                        strcpy(argv[argc], temp_arg);
                        argc++;
                        break;
                    case INPUT:
                        strcpy(input_path, temp_arg);
                        break;
                    case OUTPUT:
                        strcpy(output_path, temp_arg);
                        break;
                }
            }
        }
        
        // Execução dos comandos
        pid = fork();
        if (pid) {
            int waiting = 1;
            for (int i = 0; i < argc; i++) {
                if (strcmp(argv[i], "&") == 0) {
                    waiting = 0;
                    break;
                }
            }
            if (waiting) {
                waitpid(pid, NULL, 0);
            }
            
        } else {
            // Tomando input/output redirecionados
            if (input_path[0] != '\0')
                freopen (input_path, "r", stdin);
            if (output_path[0] != '\0')
                freopen (output_path, "w", stdout);
            
            // Arrumando os args
            char command_name[MAX]; strcpy(command_name, argv[0]);

            char *args[MAX];
            for (int i = 0; i < argc; i++) {
                if (strcmp(argv[i], "&") != 0)
                    args[i] = argv[i];
            }
            args[MAX * argc] = NULL;

            // Executando
            //execlp("ls", "ls", NULL);
            if (argc == 0)
                execlp(command_name, command_name, NULL);
            else
                execvp(command_name, args);

            // Fechando os leaks
            if (input_path[0] != '\0')
                fclose (stdin);
            if (output_path[0] != '\0')
                fclose (stdout);
            
            // Erro
            printf("Erro ao executar comando!\n");
            exit(EXIT_FAILURE);
        }
    }
}
