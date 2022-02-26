#include <lvgl.h>
#include <TFT_eSPI.h>
#include <lv_demo.h>
#include "lv_port_fatfs.h"
#include "sd_card.h"
#include <Arduino.h>
#include <FS.h>
#include <SPI.h>
#include <SD.h>
#include "light_intensity.h"
#include "home.h"
#include "humi_soil.h"
#include "luminance.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include <iostream>
#include <string>

/*时间api*/
#define NTP1 "ntp1.aliyun.com"
#define NTP2 "ntp2.aliyun.com"
#define NTP3 "ntp3.aliyun.com"
/*wifi*/
const char *ssid = "dyp";          // WIFI账户
const char *password = "00000000"; // WIFI密码

/*心知天气api*/
const char *host = "api.seniverse.com";
const char *privateKey = "SvbWq65M_Nn6d0gBt";
const char *city = "beijing";
const char *language = "en";

/*天气信息结构体*/
struct WetherData
{
    char city[32];
    char weather[64];
    char high[32];
    char low[32];
    char humi[32];
    char date[32];
    char fengsu[32];
};

extern lv_obj_t *two;
extern lv_obj_t *three;
extern lv_obj_t *four;
extern lv_obj_t *five;

extern lv_style_t font_style;
extern lv_obj_t *label3;
extern lv_obj_t *label4;
extern lv_obj_t *label5;
extern lv_obj_t *bar1;
extern lv_obj_t *bar2;
extern lv_obj_t *slider1;

char s[100];
//当前页面号
int state = 0;
//当前页面是否在调节亮度界面
int condition = 0;
char str1[10];
//亮度  0-100
float screen_luminance = 70;

TFT_eSPI tft = TFT_eSPI();

/*屏幕的宽高在这里修改*/
static const uint32_t screenWidth = 240;
static const uint32_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

//开启日志后调用的函数，启用该功能需要修改lvgl_conf.h的对应功能
#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(lv_log_level_t level, const char *file, uint32_t line, const char *fn_name, const char *dsc)
{
    Serial.printf("%s(%s)@%d->%s\r\n", file, fn_name, line, dsc);
    Serial.flush();
}
#endif

/*页面切换动画 左*/
void page_change1(lv_obj_t *from_page, lv_obj_t *to_page)
{
    lv_anim_t a;
    lv_anim_init(&a);                                          //初始化动画对象
    lv_anim_set_var(&a, from_page);                            //为对象设置一个动画
    lv_anim_set_values(&a, 0, -lv_obj_get_width(two));         //设置一个动画的开始和结束值
    lv_anim_set_time(&a, 1000);                                //设置一个动画时间
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x); //设置一个动画回调
    lv_anim_set_path_cb(&a, lv_anim_path_linear);              //设置一个动画的路径
    lv_anim_start(&a);                                         //开始动画

    lv_anim_t b;
    lv_anim_init(&b);                                          //初始化动画对象
    lv_anim_set_var(&b, to_page);                              //为对象设置一个动画
    lv_anim_set_values(&b, lv_obj_get_width(two), 0);          //设置一个动画的开始和结束值
    lv_anim_set_time(&b, 1000);                                //设置一个动画时间
    lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t)lv_obj_set_x); //设置一个动画回调
    lv_anim_set_path_cb(&b, lv_anim_path_linear);              //设置一个动画的路径
    lv_anim_start(&b);                                         //开始动画
}

/*页面切换动画 右*/
void page_change2(lv_obj_t *from_page, lv_obj_t *to_page)
{
    lv_anim_t a;
    lv_anim_init(&a);                                          //初始化动画对象
    lv_anim_set_var(&a, from_page);                            //为对象设置一个动画
    lv_anim_set_values(&a, 0, lv_obj_get_width(two));          //设置一个动画的开始和结束值
    lv_anim_set_time(&a, 1000);                                //设置一个动画时间
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x); //设置一个动画回调
    lv_anim_set_path_cb(&a, lv_anim_path_linear);              //设置一个动画的路径
    lv_anim_start(&a);                                         //开始动画

    lv_anim_t b;
    lv_anim_init(&b);                                          //初始化动画对象
    lv_anim_set_var(&b, to_page);                              //为对象设置一个动画
    lv_anim_set_values(&b, -lv_obj_get_width(two), 0);         //设置一个动画的开始和结束值
    lv_anim_set_time(&b, 1000);                                //设置一个动画时间
    lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t)lv_obj_set_x); //设置一个动画回调
    lv_anim_set_path_cb(&b, lv_anim_path_linear);              //设置一个动画的路径
    lv_anim_start(&b);                                         //开始动画
}

/* 刷新屏幕 */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

/* 蜂鸣器初始化 */
void buzzer_init()
{
    pinMode(25, OUTPUT);
    digitalWrite(25, 1);
}

/* lvgl初始化 */
void lvgl_init()
{
    lv_init();
    tft.begin();        /* TFT init */
    tft.setRotation(0); /* 旋转屏幕，n * 90度 ，3表示270度*/

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10); /*建立一个屏幕宽*10大小的缓冲区*/

    /*初始化屏幕*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*设置参数*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*初始化输入设备*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);

    /*初始化文件系统*/
    lv_fs_if_init();
}

/* sd卡初始化 */
void sd_init()
{
    SPIClass *sd_spi = new SPIClass(HSPI);
    if (!SD.begin(15, *sd_spi)) // SD-Card SS pin is 15
    {
        Serial.println("Card Mount Failed");
    }
}

/* 系统初始化 */
void mysystem_init()
{
    pinMode(5, INPUT);  // KEY1
    pinMode(17, INPUT); // KEY_OK
    pinMode(16, INPUT); // KEY2

    /*背光引脚输出pwm*/
    ledcSetup(0, 10000000, 8);
    ledcAttachPin(22, 0);
    ledcWrite(0, screen_luminance);
}

/* 页面初始化 lvgl按照创建的顺序默认覆盖 所以注意初始化顺序*/
void page_init()
{
    page5_init();
    page4_init();
    page2_init();
    page3_init();
}

int wind_spend_set(char *x)
{
    if (x[1] == '.')
        return x[0] - 48;
    else if (x[2] = '.')
        return (x[0] - 48) * 10 + x[1] - 48;
}

/* 设置时间 */
void setClock()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    { //如果获取失败，就开启联网模式，获取时间
        Serial.println("Failed to obtain time");
        WiFi.disconnect(false);
        WiFi.mode(WIFI_STA); //开启网络
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        configTime(8 * 3600, 0, NTP1, NTP2, NTP3);
        return;
    }
    Serial.println(&timeinfo, "%F %T %A"); // 格式化输出:2021-10-24 23:00:44 Sunday
    Serial.print(asctime(&timeinfo));      //默认打印格式：Mon Oct 25 11:13:29 2021
    WiFi.disconnect(true);
}

/* wifi初始化并获取天气和时间信息 */
void wifi_init()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected!");
    WiFiClient client;
    if (!client.connect(host, 80))
    {
        Serial.println("Connect host failed!");
        return;
    }
    String getUrl = "/v3/weather/daily.json?key=";
    getUrl += privateKey;
    getUrl += "&location=";
    getUrl += city;
    getUrl += "&language=";
    getUrl += language;
    client.print(String("GET ") + getUrl + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    char endOfHeaders[] = "\r\n\r\n";
    bool ok = client.find(endOfHeaders);
    if (!ok)
    {
        Serial.println("No response or invalid response!");
    }
    String line = "";
    line += client.readStringUntil('\n');
    DynamicJsonDocument doc(1400);

    DeserializationError error = deserializeJson(doc, line);
    if (error)
    {
        Serial.println("deserialize json failed");
        return;
    }
    Serial.println("deserialize json success");

    struct WetherData weatherdata = {0};

    strcpy(weatherdata.city, doc["results"][0]["location"]["name"].as<const char *>());
    strcpy(weatherdata.weather, doc["results"][0]["daily"][0]["text_day"].as<const char *>());
    strcpy(weatherdata.high, doc["results"][0]["daily"][0]["high"].as<const char *>());
    strcpy(weatherdata.low, doc["results"][0]["daily"][0]["low"].as<const char *>());
    strcpy(weatherdata.humi, doc["results"][0]["daily"][0]["humidity"].as<const char *>());
    strcpy(weatherdata.date, doc["results"][0]["daily"][0]["date"].as<const char *>());
    strcpy(weatherdata.fengsu, doc["results"][0]["daily"][0]["wind_speed"].as<const char *>());

    Serial.println("City");
    Serial.println(weatherdata.city);
    lv_label_set_text(label4, weatherdata.city);
    Serial.println("textDay");
    Serial.println(weatherdata.weather);
    Serial.println("temp high");
    Serial.println(weatherdata.high);
    Serial.println("temp low");
    Serial.println(weatherdata.low);
    Serial.println("humi");
    Serial.println(weatherdata.humi);
    lv_bar_set_value(bar2, (weatherdata.humi[0] - 48) * 10 + weatherdata.humi[1] - 48, LV_ANIM_OFF);
    lv_bar_set_value(bar1, wind_spend_set(weatherdata.fengsu), LV_ANIM_OFF);
    Serial.println("date");
    Serial.println(weatherdata.date);
    lv_label_set_text(label3, weatherdata.date);
    strcpy(str1, weatherdata.low);
    strcpy(str1 + strlen(str1), "~");
    strcpy(str1 + strlen(str1), weatherdata.high);
    strcpy(str1 + strlen(str1), "℃");
    Serial.println(str1);
    lv_label_set_text(label5, str1);

    Serial.println("read json success");
    Serial.println();
    Serial.println("closing connection");
    client.stop();

    WiFi.disconnect(true);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected!");
    WiFi.mode(WIFI_STA);

    configTime(8 * 3600, 0, NTP1, NTP2, NTP3);
    setClock();

    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF); //关闭网络
    Serial.println("WiFi disconnected!");
}

/*每次循环的监视器*/
void monitor()
{
    if (digitalRead(17) == 0)
    {
        if (state == 3)
            condition = !condition;
        delay(300);
    }

    if (digitalRead(5) == 0)
    {

        if (condition == 0)
        {
            if (state == 0)
            {
                page_change1(three, two);
                // lv_obj_add_flag(three, LV_OBJ_FLAG_HIDDEN);
            }
            else if (state == 1)
            {
                page_change1(two, four);
                // lv_obj_clear_flag(three, LV_OBJ_FLAG_HIDDEN);
            }
            else if (state == 2)
            {
                page_change1(four, five);
            }
            else
            {
                page_change1(five, three);
            }
            state++;
            state %= 4;
            delay(300);
            Serial.println((int)LV_HOR_RES);
            Serial.println((int)LV_VER_RES);
        }
        else
        {
            screen_luminance -= 0.5;
            if ((int)screen_luminance < 0)
                screen_luminance = 0;
            ledcWrite(0, (int)screen_luminance);
            lv_bar_set_value(slider1, 100 - (screen_luminance / 255) * 100, LV_ANIM_OFF);
        }
    }
    if (digitalRead(16) == 0)
    {
        if (condition == 0)
        {
            if (state == 0)
            {
                page_change2(three, five);
                // lv_obj_add_flag(three, LV_OBJ_FLAG_HIDDEN);
            }
            else if (state == 1)
            {
                page_change2(two, three);
                // lv_obj_clear_flag(three, LV_OBJ_FLAG_HIDDEN);
            }
            else if (state == 2)
            {
                page_change2(four, two);
            }
            else
            {
                page_change2(five, four);
            }
            state--;
            if (state < 0)
                state = 3;
            delay(300);
            Serial.println((int)LV_HOR_RES);
            Serial.println((int)LV_VER_RES);
        }
        else
        {
            screen_luminance += 0.5;
            if ((int)screen_luminance < 0)
                screen_luminance = 0;
            ledcWrite(0, (int)screen_luminance);
            lv_bar_set_value(slider1, 100 - (screen_luminance / 255) * 100, LV_ANIM_OFF);
        }
    }

    /*动态界面信息更新*/
    page3_refresh();
    page2_refresh();
    page4_refresh();
}