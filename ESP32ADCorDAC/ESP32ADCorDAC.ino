/*
 * （ESP32:ADC与DAC的使用
 */
void setup() {
  Serial.begin(115200);   //初始化调试串口，之后可以使用Ardunio ide 自带的串口调试，也可以自己用别的串口调试软件调试，波特率对上就行了
}

void loop() {
  float adc_get;
  Serial.println(analogRead(35));  //analogRead(35)获取指定IO口的模拟电压数据（该方法将阻塞直到采集完成）；数据范围为0~2^12-1,即0~4095.
  Serial.println(adc_get);
  dacWrite(25, 100);  //25,26 就是两个DAC引脚，后面的值取值范围时0-255，具体输出电压是  200/255*电源电压，200就是你填入的值
  delay(1000);

/**************************************************************************************************************************************/
/*********************************************     调整精度用的一些函数     ************************************************************/
/**************************************************************************************************************************************/
  //以下是我在网上找到的ADC的资料，如果简单使用就直接用下面的关键字读取，如果精度有一些要求就用下面注释的一些函数设置
  //void analogReadResolution(uint8_t bits)  设置模拟数据读取分辨率，取值1~16，默认为12；
  //void analogSetWidth(uint8_t bits)  设置ADC采样分辨率，取值9~12，默认为12；
  //void analogSetCycles(uint8_t cycles)  设置单次采样的周期，取值1~255，默认为8；
  //void analogSetSamples(uint8_t samples)设置单次采样的实际采样次数，取值1~255，默认为1；该项的设置相当于提高了ADC的灵敏度，比如该值为2，则采样获得数据就是真实数据的2倍；
  //void analogSetClockDiv(uint8_t clockDiv)设置ADC时钟分频系数，取值1~255，默认为1；
  
  //下面是设置ADC全局输入衰减，取值ADC_0db, ADC_2_5db, ADC_6db, ADC_11db，默认为11db；  当 VDD_A 为 3.3V 时：  0dB 下量程最大为 1.1V  2.5dB 下量程最大为 1.5V  6dB 下量程最大为 2.2V  11dB 下量程最大为 3.9V（最大可以采集到3.3V电压）
  //void analogSetAttenuation(adc_attenuation_t attenuation)  

  //void analogSetPinAttenuation(uint8_t pin, adc_attenuation_t attenuation)  设置单独某个IO口的输入衰减；
  //int hallRead()Get value for HALL sensor (without LNA) connected to pins 36(SVP) and 39(SVN)；(关于霍尔传感器)

  //下面几个是非阻塞采样 相关函数
  //bool adcAttachPin(uint8_t pin)将IO口连接到ADC;
  //bool adcStart(uint8_t pin)开启采样与转换；
  //bool adcBusy(uint8_t pin)检查采样与转换是否完成；
  //uint16_t adcEnd(uint8_t pin)读取采集到的数据（如果未完成将阻塞至完成）；
}
