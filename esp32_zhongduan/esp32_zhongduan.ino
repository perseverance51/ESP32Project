//外部中断端口号：GPIO 0,2,4,12-15,25-27,32-39
#include <ArduinoJson.h>
#include <Ticker.h>//定时器库非必须，只是配网时，直观一点，可以查看配网时的状态
Ticker ticker;


#define led (2)    //板载led灯
String str0="{'code':200,'msg':'success','newslist':[{'gregoriandate':'2021-08-23','lunardate':'2021-7-16','lunar_festival':'','festival':'','fitness':'经营.交易.求官.纳畜.动土','taboo':'登高.行船.安床.入宅.博彩','shenwei':'喜神：东南 福神：东北 财神：正南阳贵：东南 阴贵：正东 ','taishen':'房床若移整,大门修当避,碓磨莫移动胎神在房内南停留6天','chongsha':'兔日冲(丁酉)鸡','suisha':'岁煞西','wuxingjiazi':'金','wuxingnayear':'壁上土','wuxingnamonth':'山下火','xingsu':'南方张月鹿-吉','pengzu':'癸不词讼 卯不穿井','jianshen':'危','tiangandizhiyear':'辛丑','tiangandizhimonth':'丙申','tiangandizhiday':'癸卯','lmonthname':'孟秋','shengxiao':'牛','lubarmonth':'七月','lunarday':'十六','jieqi':'处暑'}]}";

void tick()
{
  //toggle state
  digitalWrite(led, !digitalRead(led));     // set pin to the opposite state
  Serial.printf("lubarmonth位置: %d \r\n",str0.lastIndexOf("lubarmonth"));
delay(50);
Serial.printf("lunarday位置: %d \r\n",str0.lastIndexOf("lunarday"));
String str1=str0.substring(str0.lastIndexOf("lubarmonth"),str0.lastIndexOf(",'jieqi"));

str1 = "{'" + str1 +"}";
Serial.println(str1);
//StaticJsonDocument<1024> doc;
DynamicJsonDocument doc(2048);
DeserializationError error = deserializeJson(doc, str0);

if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}
JsonObject newslist_0 = doc["newslist"][0];
const char* newslist_0_lubarmonth = newslist_0["lubarmonth"]; // "七月"
const char* newslist_0_lunarday = newslist_0["lunarday"]; // "十六"
Serial.printf("lubarmonth的值: %s \r\n",newslist_0_lubarmonth);
delay(50);
Serial.printf("lunarday的值: %s \r\n",newslist_0_lunarday);
String str2 = String(newslist_0_lubarmonth) + String(newslist_0_lunarday);
}
void setup() {
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  Serial.begin(115200);
  Serial.println();
 // esp_sleep_enable_ext0_wakeup(GPIO_NUM_4,LOW);//唤醒源中断设置,高电平或低电平触发
 ticker.attach(8, tick);
//Serial.println(str0.indexOf());
}
void loop() {
 // esp_deep_sleep_start();//进入睡眠模式之前,将刷新 UART FIFO 的内容。
  //esp_light_sleep_start();//进入轻度睡眠模式时，UART FIFO 不会被刷新。相反，UART 输出将被暂停，FIFO 中的剩余字符将在从轻度睡眠唤醒后发送出去。

}
