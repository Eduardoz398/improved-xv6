#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define stdin 0
#define stdout 1

void readshell(int fd) {
    int len = 0;
    char bufferTEMP; //onde vai ficar o conteúdo
    char *buffer;
    read(0, bufferTEMP, 1);
    len++;
    buffer[0] = bufferTEMP;
    while(bufferTEMP != 0xA) {
        read(stdin, bufferTEMP, 1);  
        buffer[len] = bufferTEMP;
        len++;
    }
    write(fd, buffer, len);
    write(stdout, buffer, len);
}



int main(int argc, char* argv[]) {
    int fd = 0; //entrada padrão
    fd = open(argv[1], O_CREATE | O_RDWR);
    readshell(fd);   
    exit();     
}


 

