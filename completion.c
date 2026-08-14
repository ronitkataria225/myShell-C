#include "headers.h"

char** makeExecutablesList(){
    char* localPath = getenv("PATH");
    char* copy_localPath = strdup(localPath);
    char* dir;
    DIR* currDir;
    struct dirent* entry;
    char fullPath[4096];

    char** list = NULL;
    char* filename;
    int count = 0;
    char** temp;

    while ((dir = strsep(&copy_localPath, ":")) != NULL)
    {
        //printf("%s\n", dir);
        if((currDir = opendir(dir)) != NULL){
            while ((entry = readdir(currDir)) != NULL)
            {
                filename = strdup(entry->d_name);
                snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, entry->d_name);
                //printf("%s\n", fullPath);
                //printf("Before if : %s\n", filename);
                if(access(fullPath, X_OK) == 0){
                    temp = realloc(list, (count + 1) * sizeof(char*));
                    if (temp == NULL) {
                        printf("Return failed\n");
                        return NULL;
                    }
                    list = temp;
                    list[count] = strdup(filename);
                    count++;
                }
            }
            closedir(currDir);
        }
    }

    // for(int i = 0; i<count; i++){
    //     printf("%s\n", list[i]);
    // }
    temp = realloc(list, (count + 1) * sizeof(char*));
    if (temp == NULL) {
        printf("Return failed\n");
        return NULL;
    }
    list = temp;
    list[count] = NULL;
    return list;
}

// int main(){
//     char** list;
//     makeList(list);
//     return 0;
// }