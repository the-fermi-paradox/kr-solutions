#define NAME_MAX 14 /* longest filename component */

/* stat takes a filename and returns all of the information
 * in the inode for that file, or -1 if error */

/*
struct stat {
  dev_t  st_dev;   device of inode
  ino_t  st_ino;   inode number
  short  st_mode;  mode bits
  short  st_nlink; number of links to file
  short  st_uid    owner's user id
  short  st_gid    owner's group id
  dev_t  st_rdev   for special files
  off_t  st_size   file size in characters
  time_t st_atime  time last accessed
  time_t st_mtime  time last modified
  time_t st_ctime  time inode last changed
}
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

void fsize(char *);

int main(int argc, char **argv)
{
  printf("%8s %8s %8s %8s %8s %8s %10s %8s\n", "size", "uid", "gid", "id", "lacc", "lmod", "lchan", "name");
  if (argc == 1)
    fsize(".");
  else
    while (--argc > 0)
      fsize(*++argv);
  return 0;
}
int stat(const char *, struct stat *);
void dirwalk(const char *, void (*fcn)(char *));

void fsize(char *name)
{
  struct stat stbuf;
  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }
  if ((stbuf.st_mode & __S_IFMT) == __S_IFDIR)
    dirwalk(name, fsize);
  printf("%8ld %8u %8u %8lu %8lu %8lu %8lu %s\n", 
      stbuf.st_size, stbuf.st_uid, stbuf.st_gid, stbuf.st_dev, 
      stbuf.st_atime, stbuf.st_mtime, stbuf.st_ctime, name);
}

#define MAX_PATH 1 << 10
void dirwalk(const char *dir, void (*fcn)(char *))
{
  char name[MAX_PATH];
  struct dirent *dp;
  DIR *dfd;

  if ((dfd = opendir(dir)) == NULL) {
    fprintf(stderr, "dirwalk: can't open %s\n", dir);
    return;
  }
  while ((dp = readdir(dfd)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0
     || strcmp(dp->d_name, "..") == 0)
      continue; /* skip self and parent */
    if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
      fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
    else {
      sprintf(name, "%s/%s", dir, dp->d_name);
      (*fcn)(name);
    }
  }
  closedir(dfd);
}
