#include "types.h"
#include "user.h"
#include "param.h"

int
main(int argc, char *argv[])
{  
    int pid = fork();
    if (pid == 0)
    {
        sleep(10);
        char *shp = (char *)get_shared_page(1, 3);
        printf(0, "process pid:%d read share pages content:%s\n", pid, shp);
        free_shared_page(1);
        printf(0, "process pid:%d free share pages\n", pid);
    } else {
        char *shp = (char *)get_shared_page(1, 3);
        char *content = "hello";
        strcpy(shp, content);
        printf(0, "process pid:%d write share pages content:%s\n", pid, content);
        wait();
        printf(0, "process pid:%d read share pages content:%s\n", pid, shp);
    }
    exit();
}