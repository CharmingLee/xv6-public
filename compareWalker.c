#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(2, "Usage:compareWalker path\n");
        exit();
    }

    compareWalker(argv[1], 0);
    exit();
}