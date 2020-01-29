#ifndef WINDOW_AREA_CLASS_H_
#define WINDOW_AREA_CLASS_H_

#include <graphics.h>

class window_area
{
    public:
        bool init_area(int positionx, int positiony, int window_width, int window_height,int win_number);
        bool clear_area(void);
        PIMAGE area;
        int window_number;
        int position[2];
        int width_height[2];
        window_area() {}
        ~window_area() {delimage(area);}
};
#endif // WINDOW_AREA_CLASS_H_
