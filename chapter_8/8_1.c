/*
 * file pointer cat:

              0.28 msec task-clock                #    0.508 CPUs utilized          
                 0      context-switches          #    0.000 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
                51      page-faults               #    0.185 M/sec                  
         1,011,278      cycles                    #    3.671 GHz                    
           841,310      instructions              #    0.83  insn per cycle         
           177,680      branches                  #  645.009 M/sec                  
             7,684      branch-misses             #    4.32% of all branches        

       0.000542390 seconds time elapsed

       0.000618000 seconds user
       0.000000000 seconds sys

  * current program:
              0.25 msec task-clock                #    0.413 CPUs utilized          
                 0      context-switches          #    0.000 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
                46      page-faults               #    0.186 M/sec                  
           809,635      cycles                    #    3.269 GHz                    
           598,866      instructions              #    0.74  insn per cycle         
           122,059      branches                  #  492.789 M/sec                  
             4,954      branch-misses             #    4.06% of all branches        

       0.000600277 seconds time elapsed

       0.000670000 seconds user
       0.000000000 seconds sys
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <error.h>
#define ERROR -1
#define fd_stdin  0
#define fd_stdout 1

/* On Debian Linux, BUFSIZ is 8192! Not bad! */
char buf[BUFSIZ] = {};

int filecopy(int ifd, int ofd);
int main(int argc, char **argv)
{
  int fd, n;
  if (argc == 1) {
    filecopy(fd_stdin, fd_stdout);
  }
  while (--argc > 0) {
    if ((fd = open(*++argv, O_RDONLY, 0)) == ERROR) {
      error(0, 0, "failed to open %s\n", *argv);
      continue;
    }
    n = filecopy(fd, fd_stdout);
    if (n == ERROR)
      error(3, 0, "failed to read %s\n", *argv);
    close(fd);
  }
  return 0;
}

int filecopy(int ifd, int ofd)
{
  int n;
  while ((n = read(ifd, buf, BUFSIZ))) {
    write(ofd, buf, n);
  }
  return n;
}
