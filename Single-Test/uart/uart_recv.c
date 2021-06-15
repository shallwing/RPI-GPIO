#include <sys/select.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
    
    struct termios                  comport;
    int                             fd = -1;
    char                            buffer[128];
    fd_set                          rdset;
    int                             rv = -1;

    fd = open("/dev/ttyAMA0", O_RDWR | O_NONBLOCK | O_NOCTTY);
    if(fd < 0){
        printf("Fail to open the comport file! [%s]\n", strerror(errno));
        return -1;
    }

    if(tcgetattr(fd, &comport) < 0){
        printf("Fail to get the attribute of the uart!", strerror(errno));
        return -1;
    }
    
    comport.c_cflag |= (CLOCAL | CREAD);
    comport.c_cflag &= ~CSIZE;
    comport.c_cflag |= CS8;
    comport.c_cflag &= ~PARENB;
    comport.c_cflag &= ~CSTOPB;

    cfsetispeed(&comport, B115200);
    cfsetospeed(&comport, B115200);

    comport.c_cc[VTIME] = 0;
    comport.c_cc[VMIN] = 0;

    tcflush(fd, TCIFLUSH);

    if(tcsetattr(fd, TCSANOW, &comport) != 0){
        printf("Fail to set the comport attribute! [%s]\n", strerror(errno));
        return -1;
    }

    while(1){
        
        FD_ZERO(&rdset);
        FD_SET(fd, &rdset);

        rv = select(fd+1, &rdset, NULL, NULL, NULL);

        if(rv < -1){
            printf("Fail to select! [%s]\n", strerror(errno));
            return -1;
        }

        if(rv == 0){
            printf("Select time out!\n", strerror(errno));
            return -1;
        }

        memset(buffer, 0, sizeof(buffer));
        
        rv = read(fd, buffer, sizeof(buffer));
        printf("Uart:    %s\n", buffer);
                
        
    }

    
    close(fd);
    close(rv);
    return 0;
}
