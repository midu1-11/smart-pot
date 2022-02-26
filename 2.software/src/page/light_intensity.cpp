#include <lvgl.h>
#include <WiFi.h>
#include <stdlib.h>

LV_IMG_DECLARE(light_intensity1);
LV_IMG_DECLARE(light_intensity2);
LV_IMG_DECLARE(light_intensity3);
LV_IMG_DECLARE(light_intensity4);
LV_IMG_DECLARE(light_intensity5);
LV_FONT_DECLARE(font);

/*存储动画每帧图片的数组*/
static const lv_img_dsc_t *light_intensity_anim_imgs[5] = {
    &light_intensity1,
    &light_intensity2,
    &light_intensity3,
    &light_intensity4,
    &light_intensity5,
};

lv_obj_t *two = NULL;
lv_style_t style2;
lv_obj_t *label9;
char *light_intensity_s = (char *)malloc(4 * sizeof(char));

/*page2初始化*/
void page2_init()
{
   two = lv_obj_create(lv_scr_act());
   lv_obj_set_size(two, LV_HOR_RES, LV_VER_RES);

   lv_obj_t *anim1 = lv_animimg_create(two);
   lv_animimg_set_src(anim1, (lv_img_dsc_t **)light_intensity_anim_imgs, 5);
   lv_animimg_set_duration(anim1, 800);
   lv_animimg_set_repeat_count(anim1, LV_ANIM_REPEAT_INFINITE);
   lv_obj_align(anim1, LV_ALIGN_CENTER, 0, -20);
   lv_animimg_start(anim1);

   lv_style_init(&style2);
   lv_style_set_text_font(&style2, &font);

   lv_obj_t *label6 = lv_label_create(two);
   lv_obj_add_style(label6, &style2, 0);
   lv_label_set_text(label6, "光照强度:");
   lv_obj_align(label6, LV_ALIGN_CENTER, 0, 60);

   sprintf(light_intensity_s, "00%");
   label9 = lv_label_create(two);
   lv_obj_add_style(label9, &style2, 0);
   lv_label_set_text(label9, light_intensity_s);
   lv_obj_align(label9, LV_ALIGN_CENTER, 55, 60);
}

/*光强int转字符串*/
void light_intensity_int_to_s(int a)
{
   if (a < 10)
   {
      *(light_intensity_s + 0) = a + 48;
      *(light_intensity_s + 1) = '%';
      *(light_intensity_s + 2) = 0;
   }
   else
   {
      *(light_intensity_s + 0) = a / 10 + 48;
      *(light_intensity_s + 1) = a % 10 + 48;
      *(light_intensity_s + 2) = '%';
      *(light_intensity_s + 3) = 0;
   }
}

/*page2刷新*/
void page2_refresh()
{
   int light_intensity_int = (int)((((analogRead(34) * 3.3 / 4095)) / 2.4) * 100);
   light_intensity_int_to_s(light_intensity_int);
   lv_label_set_text(label9, light_intensity_s);
}