#include <lvgl.h>
#include <WiFi.h>

LV_IMG_DECLARE(battery);
LV_IMG_DECLARE(sun);
LV_IMG_DECLARE(fengsu);
LV_IMG_DECLARE(humi);
LV_IMG_DECLARE(jiafei1);
LV_IMG_DECLARE(jiafei2);
LV_IMG_DECLARE(jiafei3);
LV_IMG_DECLARE(jiafei4);
LV_IMG_DECLARE(jiafei5);
LV_FONT_DECLARE(mynumber);

lv_obj_t *three = NULL;
lv_style_t font_style;
lv_style_t style1;
lv_obj_t *label1;
lv_obj_t *label2;
lv_obj_t *label3;
lv_obj_t *label4;
lv_obj_t *label5;
lv_obj_t *bar1;
lv_obj_t *bar2;

/*存储动画每帧图片的数组*/
static const lv_img_dsc_t *jiafei_anim_imgs[5] = {
    &jiafei1,
    &jiafei2,
    &jiafei3,
    &jiafei4,
    &jiafei5,
};

/*page3初始化*/
void page3_init()
{

   three = lv_obj_create(lv_scr_act());
   lv_obj_set_size(three, LV_HOR_RES, LV_VER_RES);

   static lv_point_t line_points[] = {{0, 0}, {230, 0}};
   lv_obj_t *line1;
   line1 = lv_line_create(three);
   lv_line_set_points(line1, line_points, 2);
   lv_obj_align(line1, LV_ALIGN_CENTER, 0, -50);

   lv_obj_t *line2;
   line2 = lv_line_create(three);
   lv_line_set_points(line2, line_points, 2);
   lv_obj_align(line2, LV_ALIGN_CENTER, 0, 30);

   static lv_point_t line_points1[] = {{0, 0}, {0, 70}};
   lv_obj_t *line3;
   line3 = lv_line_create(three);
   lv_line_set_points(line3, line_points1, 2);
   lv_obj_align(line3, LV_ALIGN_CENTER, -50, -86);

   lv_obj_t *line4;
   line4 = lv_line_create(three);
   lv_line_set_points(line4, line_points1, 2);
   lv_obj_align(line4, LV_ALIGN_CENTER, 50, -86);

   static lv_point_t line_points2[] = {{0, 0}, {100, 0}};
   lv_obj_t *line5;
   line5 = lv_line_create(three);
   lv_line_set_points(line5, line_points2, 2);
   lv_obj_align(line5, LV_ALIGN_CENTER, 0, -86);

   lv_obj_t *img1;
   img1 = lv_img_create(three);
   lv_img_set_src(img1, &battery);
   lv_obj_align(img1, LV_ALIGN_CENTER, -83, -94);

   lv_obj_t *img2;
   img2 = lv_img_create(three);
   lv_img_set_src(img2, &sun);
   lv_obj_align(img2, LV_ALIGN_CENTER, 85, -100);

   lv_obj_t *img3;
   img3 = lv_img_create(three);
   lv_img_set_src(img3, &fengsu);
   lv_obj_align(img3, LV_ALIGN_CENTER, -98, 54);

   lv_obj_t *img4;
   img4 = lv_img_create(three);
   lv_img_set_src(img4, &humi);
   lv_obj_align(img4, LV_ALIGN_CENTER, -98, 84);

   lv_obj_t *anim1 = lv_animimg_create(three);
   lv_animimg_set_src(anim1, (lv_img_dsc_t **)jiafei_anim_imgs, 5);
   lv_animimg_set_duration(anim1, 800);
   lv_animimg_set_repeat_count(anim1, LV_ANIM_REPEAT_INFINITE);
   lv_obj_align(anim1, LV_ALIGN_CENTER, 75, 70);
   lv_animimg_start(anim1);

   bar1 = lv_bar_create(three);
   lv_obj_set_size(bar1, 90, 14);
   lv_obj_align(bar1, LV_ALIGN_CENTER, -35, 54);
   lv_bar_set_value(bar1, 70, LV_ANIM_OFF);

   bar2 = lv_bar_create(three);
   lv_obj_set_size(bar2, 90, 14);
   lv_obj_align(bar2, LV_ALIGN_CENTER, -35, 84);
   lv_bar_set_value(bar2, 70, LV_ANIM_OFF);

   label1 = lv_label_create(three);
   lv_label_set_text(label1, "00");
   lv_obj_align(label1, LV_ALIGN_CENTER, -83, -72);

   lv_style_init(&font_style);
   lv_style_set_text_font(&font_style, &mynumber);

   label2 = lv_label_create(three);
   lv_obj_align(label2, LV_ALIGN_CENTER, 0, -12);
   lv_obj_add_style(label2, &font_style, 0);
   lv_label_set_text(label2, "1234:");

   label3 = lv_label_create(three);
   lv_obj_align(label3, LV_ALIGN_CENTER, 0, -100);
   lv_label_set_text(label3, "kkk");

   label4 = lv_label_create(three);
   lv_obj_align(label4, LV_ALIGN_CENTER, 0, -68);
   lv_label_set_text(label4, "jjj");

   label5 = lv_label_create(three);
   lv_obj_align(label5, LV_ALIGN_CENTER, 85, -76);
   lv_label_set_text(label5, "zzz");
}

/*处理asctime返回的字符串*/
char *time_turn(char *x)
{
   int i = 0;
   while (i < 3)
   {
      x += 1;
      if (*x == ' ')
         i++;
   }
   x += 1;
   *(x + 8) = '\0';
   return x;
}

/*处理电量*/
char *electric_quantity_show(int a)
{
   static char electric_quantity_s[2];
   if (a >= 10)
   {
      electric_quantity_s[0] = a / 10 + 48;
      electric_quantity_s[1] = a % 10 + 48;
   }
   else
   {
      electric_quantity_s[0] = a + 48;
      electric_quantity_s[1] = 0;
   }
   return electric_quantity_s;
}

/*page3更新*/
void page3_refresh()
{
   int electric_quantity_int = (int)((((analogRead(32) * 3.3 / 4095) * 2 - 2.8) / 1.1) * 100);
   struct tm timeinfo;
   getLocalTime(&timeinfo);
   lv_label_set_text(label2, time_turn(asctime(&timeinfo)));
   lv_label_set_text(label1, electric_quantity_show(electric_quantity_int));
}