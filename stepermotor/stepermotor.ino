/*28BYJ-48单极性步进电机
 * 28BYJ-48的含义为外径28毫米四相八拍式永磁减速型步进电机
 * 减速比1:63.684
 *可以得出转过一圈所需要节拍数是6463.684≈4076。
 *但实际上误差还是存在的，因为上面的计算结果都是约等得出的，实际误差大约是0.000056，即万分之0.56，转一万圈才会差出半圈，已经可以忽略不计了。
 */
//使用arduino IDE自带的Stepper.h库文件
#include <Stepper.h>

// 这里设置步进电机旋转一圈是多少步
#define STEPS 100

//设置步进电机的步数和引脚（就是注意点2里面说的驱动板上IN1～IN4连接的四个数字口）。
Stepper stepper(STEPS, 8, 9, 10, 11);

void setup()
{
  // 设置电机的转速：每分钟为90步
  stepper.setSpeed(90);
  // 初始化串口，用于调试输出信息
  Serial.begin(115200);
}

void loop()
{
    // 顺时针旋转一周
    Serial.println("shun");
    stepper.step(2048); //4步模式下旋转一周用2048 步。
    delay(500);

    // 逆时针旋转半周
    Serial.println("ni");
    stepper.step(-1024); //4步模式下旋转一周用2048 步。
    delay(500);
}
