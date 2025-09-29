#include "types.h"
#include "stat.h"
#include "user.h"

char buf[1024];



void
grep(char *pattern, int fd, int o_flag)
{
  int n, m;
  char *p, *q;

  m = 0;
  while((n = read(fd, buf + m, sizeof(buf) - m - 1)) > 0){
    m += n;
    buf[m] = '\0';
    p = buf;
    while((q = strchr(p, '\n')) != 0){
      *q = 0;  // Termina a linha
      
      //implementação da flag -o
      if(o_flag){
        char *r = p;
        while((r = strstr(r, pattern)) != 0){ //strstr busca pattern - palavra passada como parametro
          write(1, r, strlen(pattern));
          write(1, "\n", 1);
          r += strlen(pattern); 
        }
      } else {
        ///Modo como já estava implementado - retirada da função match
        if(strstr(p, pattern) != 0){
          *q = '\n';
          write(1, p, q - p + 1);
        }
      }
      p = q + 1;
    }
    if(p == buf)
      m = 0;
    if(m > 0){
      m -= p - buf;
      memmove(buf, p, m);
    }
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;
  char *pattern;
  int o_flag = 0;
  int arg_start = 1;

  if(argc <= 1){
    printf(2, "usage: grep [-o] pattern [file ...]\n");
    exit();
  }

  ///Analogo ao arquivo wc para obter as flags
  if(strcmp(argv[1], "-o") == 0){
    o_flag = 1;
    arg_start = 2;
  }

  if(argc <= arg_start){
    printf(2, "usage: grep [-o] pattern [file ...]\n");
    exit();
  }

  pattern = argv[arg_start];
  arg_start++;

  if(arg_start >= argc){
    grep(pattern, 0, o_flag);
    exit();
  }

  // Processa cada arquivo
  for(i = arg_start; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(2, "grep: cannot open %s\n", argv[i]);
      exit();
    }
    grep(pattern, fd, o_flag);
    close(fd);
  }
  exit();
}
