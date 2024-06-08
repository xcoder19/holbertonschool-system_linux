#include <stdio.h>
#include <dirent.h>

int main() {
    struct dirent *entry;
    DIR *dp = opendir(".");

    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_name[0] != '.') {
            printf("%s  ", entry->d_name);
        }
    }

    closedir(dp);
    printf("\n");

    return 0;
}

