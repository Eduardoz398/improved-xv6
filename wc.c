#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
wc(int fd, char *name, int l_flag)
{
  int i, n;
  int l, w, c, inword;


  l = w = c = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      c++;
      if(buf[i] == '\n')
        l++;
      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if(!inword){
        w++;
        inword = 1;
      }
    }
  }
  if(n < 0){
    printf(1, "wc: read error\n");
    exit();
  }
  if(l_flag) { 
    printf(1, "%d\n", l);
  }
  else {
     printf(1, "%d %d %d %s\n", l, w, c, name);
  }
}

int
main(int argc, char *argv[])
{
  int arg_start = 1;
  int l_flag = 0;

  
  if(argc > 1 && strcmp(argv[1], "-l") == 0) { //verfica se tem a flag -l e verificação de argc para o programar não
                                              // dá segfault
    l_flag = 1;
    arg_start = 2;
  }

  int fd, i;

 
  if(argc <= arg_start) {
    wc(0, "", l_flag);
    exit();
  }

  
  for(i = arg_start; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "wc: cannot open %s\n", argv[i]);
      exit();
    }
    wc(fd, argv[i], l_flag);
    close(fd);
  }
  exit();
}
