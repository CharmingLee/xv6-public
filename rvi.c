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

    for(int i = 1; i < argc; i++){
        printf(1, "before:%s\n", argv[1]);
        char filePath[DIRSIZ];
        memset(&filePath, 0, sizeof(filePath));
        strcat(filePath, "/temp/");
        strcat(filePath, argv[1]);
        printf(1, "after:%s\n", filePath);
        int fd = open(filePath, O_RDONLY);
        if (fd < 1)
        {
            printf(1, "path:%s not exist\n", filePath);
            exit();
            return -1;
        }
        
        uint addrs[NDIRECT + 2];
        memset(&addrs, 0, sizeof(addrs));
        read(fd, addrs, sizeof addrs);
        close(fd);
        for (int i = 0; i < NDIRECT + 2; i++)
        {
            printf(1, "addrs[%d]:%d\n", i, addrs[i]);
        }

        printf(1, "before:%s\n", argv[1]);
        char savePath[DIRSIZ];
        memset(&savePath, 0, sizeof(savePath));
        strcat(savePath, "/recover/");
        strcat(savePath, argv[1]);
        printf(1, "after:%s\n", savePath);
        fd = open(savePath, O_CREATE | O_RDWR);
        if (fd < 1)
        {
            printf(2, "path:%s not exist\n", savePath);
            return -1;
        }

        char buf[BSIZE];
        uint size = addrs[NDIRECT + 1];
        for (int i = 0; i < NDIRECT + 1 && addrs[i] != 0; i++)
        {
            printf(1, "loop\n");
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