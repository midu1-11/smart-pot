#include <lvgl.h>
#include <stdlib.h>
#include <wifi.h>

LV_IMG_DECLARE(humi_soil1);
LV_IMG_DECLARE(humi_soil2);
LV_IMG_DECLARE(humi_soil3);
LV_IMG_DECLARE(humi_soil4);
LV_FONT_DECLARE(font);

/*存储动画每帧图片的数组*/
static const lv_img_dsc_t *humi_soil_anim_imgs[4] = {
    &humi_soil1,
    &humi_soil2,
    &humi_soil3,
    &humi_soil4,
};

lv_obj_t *four = NULL;
lv_style_t style3;
lv_obj_t *label8;
char *humi_soil_s = (char *)malloc(4 * sizeof(char));

/*page4初始化*/
void page4_init()
{
    four = lv_obj_create(lv_scr_act());
    lv_obj_set_size(four, LV_HOR_RES, LV_VER_RES);

    lv_obj_t *anim1 = lv_animimg_create(four);
    lv_animimg_set_src(anim1, (lv_img_dsc_t **)humi_soil_anim_imgs, 4);
    lv_animimg_set_duration(anim1, 1600);
    lv_animimg_set_repeat_count(anim1, LV_ANIM_REPEAT_INFINITE);
    lv_obj_align(anim1, LV_ALIGN_CENTER, 0, -20);
    lv_animimg_start(anim1);

    lv_style_init(&style3);
    lv_style_set_text_font(&style3, &font);

    lv_obj_t *label7 = lv_label_create(four);
    lv_obj_add_style(label7, &style3, 0);
    lv_label_set_text(label7, "土壤湿度:");
    lv_obj_align(label7, LV_ALIGN_CENTER, 0, 60);

    sprintf(humi_soil_s, "00%");
    label8 = lv_label_create(four);
    lv_obj_add_style(label8, &style3, 0);
    lv_label_set_text(label8, humi_soil_s);
    lv_obj_align(label8, LV_ALIGN_CENTER, 55, 60);
}

/*湿度int转字符串*/
void humi_soil_int_to_s(int a)
{
    if (a < 10)
    {
        *(humi_soil_s + 0) = a + 48;
        *(humi_soil_s + 1) = '%';
        *(humi_soil_s + 2) = 0;
    }
    else
    {
        *(humi_soil_s + 0) = a / 10 + 48;
        *(humi_soil_s + 1) = a % 10 + 48;
        *(humi_soil_s + 2) = '%';
        *(humi_soil_s + 3) = 0;
    }
}

/*page4刷新*/
void page4_refresh()
{
    int humi_soil_int = (int)(((3.3 - (analogRead(33) * 3.3 / 4095)) / 3.3) * 100);
    humi_soil_int_to_s(humi_soil_int);
    lv_label_set_text(label8, humi_soil_s);
}