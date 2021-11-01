#include "types.h"
#include "user.h"
#include "param.h"

int
main(int argc, char *argv[])
{    
    char *order = argv[1];
    int key = (int)(argv[2][0] - '0');
    int num_page = (int)(argv[3][0] - '0');
    char *content = argv[4];
    if (!key || key < 1 || key > MAX_SHP_TAB_NUM || 
    !num_page || num_page < 1 || num_page > MAX_SHP_PAGE_NUM)
    {
        return -1;
    }

    // printf(0, "start... %s %s\n", order, content);
    if (order && !strcmp(order, "free"))
    {
        // printf(0,"1\n");
        free_shared_page(key);
    } else if (order && !strcmp(order, "get")) {
        char *shm;
        printf(0,"1\n");
        if (content && strlen(content) < 16)
        {
            printf(0, "2\n");
            free_shared_page(key);
            shm = get_shared_page(key, num_page);
            strcpy(shm, content);
        } else {
            printf(0, "3\n");
            shm = get_shared_page(key, num_page);
        }
        printf(0, "4\n");
        printf(0, "%s\n", shm);
    } else {
        // printf(0, "3\n");
    }
    // printf(0, "end...\n");
    exit();
}