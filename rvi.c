#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
    if(argc < 2){
        printf(2, "Usage: rvi files...\n");
        exit();
    }

    mkdir("/recover");
    for(int i = 1; i < argc; i++){
        char filePath[DIRSIZ];
        memset(&filePath, 0, sizeof(filePath));
        strcat(filePath, "/recycle/");
        strcat(filePath, argv[1]);
        int fd = open(filePath, O_RDONLY);
        if (fd < 1)
        {
            printf(1, "path:%s not exist\n", filePath);
            continue;	
	}
        
        uint addrs[NDIRECT + 2];
        memset(&addrs, 0, sizeof(addrs));
        read(fd, addrs, sizeof addrs);
        close(fd);

        char savePath[DIRSIZ];
        memset(&savePath, 0, sizeof(savePath));
        strcat(savePath, "/recover/");
        strcat(savePath, argv[1]);
        fd = open(savePath, O_CREATE | O_RDWR);
        if (fd < 1)
        {
            printf(2, "path:%s not exist\n", savePath);
            continue;
        }

        char buf[BSIZE];
        uint size = addrs[NDIRECT + 1];
        for (int i = 0; i < NDIRECT + 1 && addrs[i] != 0; i++)
        {
            memset(&buf, 0, sizeof(buf));
            uint blockSize = size;
            if (blockSize > BSIZE)
            {
                blockSize = BSIZE;
            }
        
            recoverb(T_DIR, addrs[i], buf, blockSize);
            write(fd, buf, blockSize);
            size -= blockSize;
        }
        close(fd);
    }
    exit();
}
