#include <lvgl.h>
#include <stdlib.h>

LV_IMG_DECLARE(luminance);

lv_obj_t *five = NULL;
lv_obj_t *slider1;

void page5_init()
{
   five = lv_obj_create(lv_scr_act());
   lv_obj_set_size(five, LV_HOR_RES, LV_VER_RES);

   lv_obj_t *img1;
   img1 = lv_img_create(five);
   lv_img_set_src(img1, &luminance);
   lv_obj_align(img1, LV_ALIGN_CENTER, 0, -50);

   slider1 = lv_slider_create(five);
   lv_obj_set_size(slider1, 160, 20);
   lv_slider_set_range(slider1, 0, 100);
   lv_obj_align(slider1, LV_ALIGN_CENTER, 0, 0);
   lv_bar_set_value(slider1, 70, LV_ANIM_OFF);
}
