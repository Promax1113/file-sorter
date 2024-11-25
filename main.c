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


int existsCheck(char *filePath, char *dirName){
    DIR *d;
    struct dirent *ent;
    struct stat info;
    if ((d = opendir(filePath)) == NULL){
        perror("opendir() error occurred.");
    } else {
        while ((ent = readdir(d)) != NULL){
            if (strcmp(ent->d_name, dirName) == 0){
                closedir(d);
                return  1;
            }
        }

    }
    closedir(d);

    return  0;
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
    char path[1025] = "";
    char currExt[128] = "";
    char newPath[1025] = "";


    if ((d = opendir(filepath)) == NULL){
        perror("opendir() error occurred.");
        return 1;
    } else {
        while ((ent = readdir(d)) != NULL) {
            strcat(path, filepath);
            strcat(path, "/");
            strcat(path, ent->d_name);
            strcat(newPath, filepath);
            strcat(newPath, "/");
            strcat(newPath, currExt);
            if (isDir(path)|| strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0 || ent->d_name[0] == '.') {
                currExt[0] = '\0';
                path[0] = '\0';
                newPath[0] = '\0';
                continue;
            }
            char *ext = getExtension(ent->d_name);
            if (ext == NULL) {
                currExt[0] = '\0';
                path[0] = '\0';
                newPath[0] = '\0';
                continue;
            }
            strcat(newPath, ext);
            if (mkdir(newPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 1){
                strcat(newPath, "/");
                strcat(newPath, ent->d_name);
                rename(path, newPath);
            } else {
                strcat(newPath, "/");
                strcat(newPath, ent->d_name);
                rename(path, newPath);


            }
            // Unnecessary "debug" print line.
            //printf("\npath: %s\n, currext: %s\n newpath: %s\n", path, currExt, newPath);
            // Reset the arrays.
            currExt[0] = '\0';
            path[0] = '\0';
            newPath[0] = '\0';

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

    sortByType(filepath);

}
