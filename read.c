#include "types.h"t
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void readshell(int fd) {
    char *buffer; //onde vai ficar o conteúdo
    read(fd,buffer, 5);
    write(0, buffer, 5);
}



int main(int argc, char* argv[]) {
    int fd = 0; //entrada padrão
    fd = open(argv[1], O_CREATE | O_RDWR);
    readshell(fd);   
    exit();     
}


 

