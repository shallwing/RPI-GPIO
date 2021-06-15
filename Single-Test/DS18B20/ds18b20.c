#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
    
    int                 i;
    int                 fd = -1;
    char                path[128];
    char                temper[10];
    char                *p_str = NULL;
    char                match[][16] = {"bus", "28-", "slave"};
    DIR                 *dir = NULL;
    struct dirent       *dir_info;

    memset(path, 0, sizeof(path));
    strncpy(path, "/sys/devices/", sizeof(path));

    for(i=0; i<sizeof(match)/sizeof(match[0]); i++){
        
        dir = opendir(path);
        if(!dir){
            printf("Fail to open the path %s [%s]\n", strerror(errno));
            return -1;
        }
        do{
            dir_info = readdir(dir);
        }while(!strstr(dir_info->d_name, match[i]));

        strcat(path, strcat(dir_info->d_name, "/"));
    }
    path[strlen(path)-1] = '\0';

    fd = open(path, O_RDONLY);
    if(fd < 0){
        printf("Fail to open the file %s [%s]\n", path, strerror(errno));
        return -1;
    }
    memset(path, 0, sizeof(path));

    read(fd, path, sizeof(path));
    p_str = strstr(path, "t=");
    strncpy(temper, p_str+2, 5);

    printf("DS18B20 gets the temperature %2.2f℃\n", atof(temper)/1000);

    close(fd);
    return 1;
}
