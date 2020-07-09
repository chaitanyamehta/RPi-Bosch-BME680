#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<linux/i2c.h>
#include<linux/i2c-dev.h>
#include"i2c.hpp"

using namespace std;

int I2C::Open()
{
    if((i2c_handle=open("/dev/i2c-1", O_RDWR)) < 0)
    {
        perror ("Opening bus failed");
        return 1;
    }
    return 0;
}

int I2C::Read(unsigned char dev_addr, unsigned char reg_addr, unsigned char *data, int length)
{
    int res = 0;
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];

    messages[0].addr = dev_addr;
    messages[0].flags = 0;
    messages[0].len = sizeof(reg_addr);
    messages[0].buf = &reg_addr;

    messages[1].addr = dev_addr;
    messages[1].flags = I2C_M_RD;
    messages[1].len = length;
    messages[1].buf = data;

    packets.msgs = messages;
    packets.nmsgs = 2;

    if(ioctl(i2c_handle, I2C_RDWR, &packets) < 0)
    {
        perror("Read operation failed");
        res = 1;
    } 
    return res;
}

int I2C::Write(unsigned char dev_addr, unsigned char reg_addr, unsigned char *data, int length)
{
    int res = 0;
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    unsigned char *write_buffer = new unsigned char[length+1];
    write_buffer[0] = reg_addr;
    for (int i = 1; i <= length; i++)
    {
        write_buffer[i] = data[i-1];
    }

    messages[0].addr = dev_addr;
    messages[0].flags = 0;
    messages[0].len = length + 1;
    messages[0].buf = write_buffer;

    packets.msgs = messages;
    packets.nmsgs = 1;

    if(ioctl(i2c_handle, I2C_RDWR, &packets) < 0)
    {
        perror("Write operation failed");
        res = 1;
    }
    delete[] write_buffer;
    return res;
}

void I2C::Close()
{
    if(i2c_handle != 0)
    {
        close(i2c_handle);
    }
}