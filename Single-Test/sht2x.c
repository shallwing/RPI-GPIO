#include <sys/ioctl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define SHT2X_ADDR              0x40
#define SHT2X_NO_TENBIT         0x00
#define SHT2X_RESET             0xFE
#define SHT2X_NOHOLD_TEMPER     0XF3
#define SHT2X_NOHOLD_HUMIDI     0XF5

void delay_ms(int ms);
int sht2x_init(int sht2x_id);
int sht2x_softreset(int fd_i2c);
int sht2x_sample(int fd_i2c, double *temperature, double *humidity);

void delay_ms(int ms){
    
    struct timespec         sleep, tmp;

    sleep.tv_sec = ms / 1000;
    sleep.tv_nsec = (long)(ms % 1000) * 1000000;

    nanosleep(&sleep, &tmp);
    return ;
}

int sht2x_init(int sht2x_id){
    
    int                     fd_i2c = -1;
    char                    path[16];

    sprintf(path, "/dev/i2c-%d", sht2x_id);
    fd_i2c = open(path, O_RDWR);
    if(fd_i2c < 0){
        printf("Fail to open the dev file %s! [%s]\n", path, strerror(errno));
        return -1;
    }
    
    ioctl(fd_i2c, I2C_SLAVE, SHT2X_ADDR);
    
    return fd_i2c;
}

int sht2x_softreset(int fd_i2c){
    
    uint8_t                 reset[4];

    memset(reset, 0, sizeof(reset));
    reset[0] = SHT2X_RESET;
    if(write(fd_i2c, reset, 1) < 0){
        return -1;
    }
    
    delay_ms(20);
    return 1;
}

int sht2x_sample_t(int fd_i2c, double *temperature){
    
    uint8_t                 buffer[4];
    double                  value = 0.0;

    memset(buffer, 0, sizeof(buffer));
    buffer[0] = SHT2X_NOHOLD_TEMPER;
    write(fd_i2c, buffer, 1);
    delay_ms(85);
    memset(buffer, 0, sizeof(buffer));
    read(fd_i2c, buffer, 3);
    value = ((int)buffer[0] << 8) + (int)buffer[1];
    *temperature = -46.85 + 175.72 * value / 65536.0;
    
    return 1;
}

int sht2x_sample_rh(int fd_i2c, double *humidity){
    
    uint8_t                 buffer[4];
    double                  value = 0.0;

    memset(buffer, 0, sizeof(buffer));
    buffer[0] = SHT2X_NOHOLD_HUMIDI;
    write(fd_i2c, buffer, 1);
    memset(buffer, 0, sizeof(buffer));
    delay_ms(29);
    read(fd_i2c, buffer, 3);
    value = ((int)buffer[0] << 8) + (int)buffer[1];
    *humidity = -6.0 + 125.0 * value / 65536.0;
    
    return 1;
}


int main(int argc, char **argv){

    double                  temperature, humidity;
    int                     fd_i2c = -1;
    
    fd_i2c = sht2x_init(1);
    if(fd_i2c < 0){
        return fd_i2c;
    }

    if(sht2x_softreset(fd_i2c) < 0){
        return -1;
    }

    sht2x_sample_t(fd_i2c, &temperature);
    sht2x_sample_rh(fd_i2c, &humidity);

    printf("T == %2.2f℃\nH == %2.2f%%\n", temperature, humidity);
    
    return 1;
}
