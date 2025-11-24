#include "myMath.h"


void get_hum_temp(float* humidity, float* temperature, uint8_t data[])
{
	//湿度计算
	uint32_t rawData = (data[1] << 12) + (data[2] << 4) + ((data[3]&0xf0) >> 4);
	*humidity = ((float)(rawData)/1048576) * 100;
	//温度计算
	rawData = (data[4] << 8) + data[5] + ((data[3]&0x0f) << 16);
	*temperature = (float)(rawData)/5242 - 50;
}


