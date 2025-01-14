#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


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
    char path[1025] = "";
    char currExt[128] = "";
    char newPath[1025] = "";


    if ((d = opendir(filepath)) == NULL){
        perror("opendir() error occurred.");
        return 1;
    } else {
        while ((ent = readdir(d)) != NULL) {
            // path is ./filename
            snprintf(path, sizeof(path), "%s/%s", filepath, ent->d_name);
            snprintf(newPath, sizeof(newPath), "%s/%s", filepath, currExt);
            if (isDir(path)|| strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0 || ent->d_name[0] == '.') {
                memset(path, 0, sizeof(path));
                memset(newPath, 0, sizeof(newPath));
                memset(currExt, 0, sizeof(currExt));
                continue;
            }
            char *ext = getExtension(ent->d_name);
            if (ext == NULL) {
                memset(path, 0, sizeof(path));
                memset(newPath, 0, sizeof(newPath));
                memset(currExt, 0, sizeof(currExt));
                continue;
            }
            // new path gets set to ./extension
            strcat(newPath, ext);
            if (mkdir(newPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 1){

                snprintf(newPath, sizeof(newPath), "%s/%s", newPath, ent->d_name);
                rename(path, newPath);
            } else {
                snprintf(newPath, sizeof(newPath), "%s/%s", newPath, ent->d_name);
                rename(path, newPath);

            }
            memset(path, 0, sizeof(path));
            memset(newPath, 0, sizeof(newPath));
            memset(currExt, 0, sizeof(currExt));
        }
    }
    closedir(d);
    return 0;
}


int main(int argc, char **argv){
    char *filepath;
    if (argc < 2){
        filepath = ".";
    } else {
        filepath = argv[1];
    }
    if (strcmp(filepath, "--help") == 0 || strcmp(filepath, "-h") == 0){
        printf("Usage: %s [directory] (defaults to current)\n", argv[0]);
        return 0;
    }
    sortByType(filepath);
}
