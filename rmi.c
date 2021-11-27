#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf(2, "Usage: rmi files...\n");
    exit();
  }

  for(int i = 1; i < argc; i++){
    uint addrs[NDIRECT+2];
    getinode(argv[i], addrs);

    char savePath[DIRSIZ];
    memset(&savePath, 0, sizeof(savePath));
    strcat(savePath, "/temp/");
    strcat(savePath, argv[i]);
    int fd = open(savePath, O_CREATE|O_RDWR);
    write(fd, addrs, sizeof addrs);
    close(fd);

    if(unlink(argv[i]) < 0){
      printf(2, "rmi: %s failed to delete\n", argv[i]);
      break;
    }
  }

  exit();
}