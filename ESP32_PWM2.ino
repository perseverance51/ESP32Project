void setup() {
  // pwm通道 PWM一共有16个通道，0-7位高速通道由80Mhz时钟驱动，后面8个为低速通道由1Mhz时钟驱动
  int channel_PWM = 3;  
  int channel_PWM2 = 4; 
  //50hz pwm波
  int freq_PWM = 50;  
  // PWM分辨率，取值为 0-20 之间  
  int resolution_PWM = 10;//2的十次方 + 1 = 1025  
  
  ledcSetup(channel_PWM,freq_PWM,resolution_PWM);//通道，频率，分辨率
  ledcAttachPin(33,channel_PWM);//引脚，通道

  ledcSetup(4,freq_PWM,resolution_PWM);//通道 频率 分辨率
  ledcAttachPin(32,channel_PWM2);//引脚，通道
}

void loop() {
  ledcWrite(3,512);// 通道号 、pwm值   高电平
  ledcWrite(4,0);//低电平
  
  delay(2000);
  
  ledcWrite(3,1024); //全速运行
  ledcWrite(4,0);
  
  delay(2000);

  ledcWrite(4,512);//逆时针 半速运行 
  ledcWrite(3,0);
  
  delay(2000);
  
  ledcWrite(4,1024);//全速运行
  ledcWrite(3,0);
  
  delay(2000);
}
