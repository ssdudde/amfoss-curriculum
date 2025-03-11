#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
//defining prototypes of func to avoid conflicts from implicit conversion
char *read_line(void);
void w_loop(void);
char **parse_intp(char aug[],int saug_size);
void print_commands(char **commands);
int chang_dir(char **line);
int print_pwd(char **tokens);
void execute_command(char **tokens);
int done(char **tokens);

int status = 1;
int main(){
  while(1){
    w_loop();

    
  }
  return EXIT_SUCCESS;
}
void w_loop() {
    char *line;
    char **commands;
    

    while (status!=0) {
        line = read_line();
        if (line == NULL) {
            continue;  // Ignore empty input
        }

        commands = parse_intp(line, strlen(line));
        if (commands == NULL || commands[0] == NULL) { 
            free(line);
            free(commands);
            continue;  // Ignore empty input or blank spaces
        }

        
        if (strcmp(commands[0], "cd") == 0) {
          chang_dir(commands);  // Handle `cd` internally
        } 
        else {
            execute_command(commands);  // Execute external commands
          }         

        //print_pwd(commands);
        done(commands);
        free(line);
        free(commands);
        
    }
}
  

char *read_line(void) {
    char *m = NULL;
    size_t len = 0;
    printf(">> ");
    fflush(stdout);

    if (getline(&m, &len, stdin) == -1) {
        perror("Error reading line");
        return NULL;
    }

    // Remove the trailing newline character
    size_t line_length = strlen(m);
    if (line_length > 0 && m[line_length - 1] == '\n') {
        m[line_length - 1] = '\0';
    }

    return m;
}
char **parse_intp(char aug[],int aug_ize){
  char **tokens = NULL;
  char *tok = strtok(aug," ");
  int count = 0;
  while (tok!=NULL){
    //tok points char* and char* is pointer to the word we enter
    tokens = realloc(tokens, sizeof(char *) * (count +  1));
    tokens[count] = strdup(tok);
    count++;
    //using null so strtok knows from where to continue ,as strtok returns a pointer to 1st char of null terminated array
    tok = strtok(NULL, " ");
  }
    tokens = realloc(tokens, sizeof(char *) * (count + 1));
    tokens[count] = NULL;
  return tokens;
}
  void print_commands(char **commands) {
    for (int i = 0; commands[i] != NULL; i++) {
        printf("Command %d:%s\n", i, commands[i]);
    }
  }
  int chang_dir(char **tokens){
    // Check if the command is "cd"
    if(tokens[0] == NULL || strcmp(tokens[0], "cd") != 0) {
        // Not a cd command, so do nothing.
        return 1;
    }
      if(tokens[1] == NULL){
        fprintf(stderr, "Enter a valid path\n");
        return 0;
    } else {
        // Attempt to change directory  cd
        if(chdir(tokens[1]) != 0) {
            perror("erro in changing directory");
        } 
        return 1;
    } 
  }
  /*int print_pwd(char **tokens){
    if(strcmp(tokens[0],"pwd")==0){
      char cwd[1024];
            if(getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Directory changed to: %s\n", cwd);
    }else{
      perror("error");
    }
    }
    return 1;
  }*/
  void execute_command(char **tokens) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return;
    }

    if (pid == 0) {  // Child process
        if (execvp(tokens[0], tokens) == -1) {
            perror("Execution failed");
        }
        exit(EXIT_FAILURE);
    } else {  // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}
    int done(char **tokens){
      if(strcmp(tokens[0],"exit")==0){
        printf("in exit");
        status=0;
      }
      return 1;
    }
  
  
  
  



  
