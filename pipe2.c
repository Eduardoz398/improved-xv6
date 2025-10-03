#include "types.h"
#include "user.h"
#include "fcntl.h"


//mais facil de modificar :)
static int is_sep(char *s) {
  return (s[0] == ':' );
}

int main(int argc, char *argv[])
{
  int i, sep = -1;

  //pipe2 + cmd1 + : + cm2
  if(argc < 4){
    printf(2, "uso: pipe2 <cmd1 e args> : <cmd2 e args>\n");
    exit();
  }


  for(i = 1; i < argc; i++){
    if(is_sep(argv[i])){
      sep = i;
      break;
    }
  }

  if(sep == -1 || sep == 1 || sep == argc-1){
    printf(2, "pipe2: separador ausente ou comando vazio\n");
    exit();
  }

  // separar argv
  argv[sep] = 0;
  char **left  = &argv[1];
  char **right = &argv[sep+1];

  //criar pipe
  int p[2];
  if(pipe(p) < 0){
    printf(2, " pipe2: pipe falhou\n");
    exit();
  }

  // filho 1: stdout -> p[1]
  int pid1 = fork();
  if(pid1 == 0){
    close(1);
    dup(p[1]);
    close(p[0]);
    close(p[1]);
    exec(left[0], left);
    printf(2, "pipe2: exec %s falhou\n", left[0]);
    exit();
  } 
  else if(pid1 < 0){
    printf(2, "pipe2: fork 1 falhou\n");
    close(p[0]); close(p[1]);
    exit();
  }

  // filho 2: stdin <- p[0]
  int pid2 = fork();
  if(pid2 == 0){
    close(0);
    dup(p[0]);
    close(p[1]);
    close(p[0]);
    exec(right[0], right);
    printf(2, "pipe2: exec %s falhou\n", right[0]);
    exit();
  } 
  else if(pid2 < 0){
    printf(2, "pipe2: fork 2 falhou\n");
    close(p[0]); close(p[1]);
    wait();
    exit();
  }

  // pai
  close(p[0]);
  close(p[1]);
  wait();
  wait();
  exit();
}
