#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


struct file_t {
    struct dirent file_o;
    char ext[128];
};

int isDir(char *file){
    struct stat path_stat;
    return !stat(file, &path_stat) && S_ISDIR(path_stat.st_mode);
}


char *getExtension(char *filename){
    char *loc;
    int _ch = '.';
    loc = strrchr(filename, _ch);
    if (loc == NULL){
        return NULL;
    }
    return loc + 1;
}


int sortByType(char *filepath){
    DIR *d;
    struct dirent *ent;
    struct stat info;
    char path[1025];

    if ((d = opendir(filepath)) == NULL){
        perror("opendir() error occurred.");
    } else {
        while ((ent = readdir(d)) != NULL) {
            strcat(path, filepath);
            strcat(path, "/");
            strcat(path, ent->d_name);
            if (isDir(path)|| strcmp(path, "./..") == 0 || strcmp(path, "./.") == 0) {
                path[0] = '\0';
                continue;
            }
            printf("%s\n", path);
            // Reset the char array.
            path[0] = '\0';


        }
    }
}


int main(int argc, char **argv){
    char *filepath;
    if (argc < 2){
        filepath = ".";
    } else {
        filepath = argv[1];
    }

    sortByType(filepath);

}
