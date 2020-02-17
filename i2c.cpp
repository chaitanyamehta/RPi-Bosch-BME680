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

int I2C::SetDeviceAddress(char dev_addr)
{
    int res = 0;
    if(ioctl(i2c_handle, I2C_SLAVE, dev_addr) < 0)
    {
        perror("Set device address failed");
        res = 1;
    }
    return res;
}

int I2C::Read(char reg_addr, char *data, int length)
{
    int res = 0;
    char reg_addr_buffer[1] = {reg_addr};
    if(write(i2c_handle, reg_addr_buffer, 1) != 1)
    {
        perror("Set register address failed");
        res = 1;
    }
    if(read(i2c_handle, data, length) != length)
    {
        perror("Read operation failed");
        res = 1;
    }
    return res;
}

int I2C::Write(char reg_addr, char *data, int length)
{
    int res = 0;
    char *write_buffer = new char[length+1];
    write_buffer[0] = reg_addr;
    for (int i = 1; i <= length; i++)
    {
        write_buffer[i] = data[i-1];
    }
    if(write(i2c_handle, write_buffer, length+1) != length+1)
    {
        perror("Write operation failed");
        res = 1;
    }
    delete[] write_buffer;
    return res;
}

I2C::~I2C()
{
    if(i2c_handle != 0)
    {
        close(i2c_handle);
    }
}