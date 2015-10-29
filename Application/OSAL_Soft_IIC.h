#ifndef _OSAL_SOFT_IIC_H_
#define _OSAL_SOFT_IIC_H_


typedef enum{
	EPROM=0,
	IIC_DEVICE_NUM
}iic_device_t;


#define IIC_HALF_DEALY_TIME  15
#define IIC_DELAY_TIME     30


int osal_iic_write_buf(iic_device_t device, uint32 map, uint8 *buf, size_t cnt);

int osal_iic_write_byte(iic_device_t device, uint32 map, uint8 data);

int osal_iic_read_buf(iic_device_t device, uint32 map, uint8 *buf, size_t cnt);


#endif







