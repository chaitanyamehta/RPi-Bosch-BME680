#ifndef I2C_HPP_INCLUDED
#define I2C_HPP_INCLUDED

class I2C
{
    private:
    int i2c_handle = 0;
    
    public:
    int Open();
    int SetDeviceAddress(char dev_addr);
    int Read(char reg_addr, char *data, int length);
    int Write(char reg_addr, char *data, int length);
    ~I2C();
};
#endif