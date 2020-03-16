#ifndef I2C_HPP_INCLUDED
#define I2C_HPP_INCLUDED

class I2C
{
    private:
    int i2c_handle = 0;
    
    public:
    int Open();
    int Read(unsigned char dev_addr, unsigned char reg_addr, unsigned char *data, int length);
    int Write(unsigned char dev_addr, unsigned char reg_addr, unsigned char *data, int length);
    ~I2C();
};
#endif