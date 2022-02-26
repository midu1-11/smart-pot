#include <lvgl.h>
#include <Arduino.h>
#include "functions.h"

void setup()
{
   buzzer_init();

   Serial.begin(115200);

   sd_init();

   lvgl_init();

   mysystem_init();

   page_init();

   wifi_init();

   Serial.println("Setup done");
}

void loop()
{

   lv_timer_handler(); /* 在循环中让lvgl处理一些相应的事件 lvgl核心函数*/

   monitor();

   delay(5);
}
