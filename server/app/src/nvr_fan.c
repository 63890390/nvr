
#include <nvr_server_headers.h>
#include <gpio.h>
#include "nvr_fan.h"

#define NVR_FAN_GPIO_VAL -1	//���ȿ���IO��

/*���ȿ���
	gpio_val: д�����ֵ.
	�ɹ�����0, ʧ�ܷ���-1.
*/
int nvr_fan_ctrl(int gpio_val)
{
	long lHandle = 0;
	int  gpio_num = NVR_FAN_GPIO_VAL;
	
	gpio_val = !!gpio_val;
	lHandle = gpio_open(gpio_num);
	if(0 != lHandle)
	{
		if(0 > gpio_set_value(lHandle, gpio_val))
		{
			gpio_close(lHandle);
			return -1;
		}
		
		gpio_close(lHandle);
	}
	else
		return -1;

	return 0;
}


