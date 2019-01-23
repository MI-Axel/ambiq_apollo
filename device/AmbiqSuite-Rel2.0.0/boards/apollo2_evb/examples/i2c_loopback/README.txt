SWO is configured in 1M baud, 8-n-1 mode.
@verbatim
PIN Fly Lead Assumptions for the I/O Master (IOM):
IOM0
GPIO[5] == IOM4 I2C SCL
GPIO[6] == IOM4 I2C SDA

IOS
PIN Fly Lead Assumptions for the I/O Slave (IOS):
GPIO[0] == IOS I2C SCL
GPIO[1] == IOS I2C SDA

Connect IOM4 I2C pins to corresponding IOS I2C pins

@endverbatim

