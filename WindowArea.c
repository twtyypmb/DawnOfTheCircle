#include "WindowArea.h"
#include <stdlib.h>

void  ClearCore(void* _this )
{
    PWindowArea this=(PWindowArea)_this;
//    cleardevice(this->area);
//    PIMAGE img1;//,img3;
//    img1 = newimage();
//    getimage(img1,total_image1,5*32,0*32,32,32);
//    // cout << putimage(NULL,0, 0, img1) <<endl;
//    // DebugTools_PrintDebugInfo( "%d\n", putimage(NULL,0, 0, img1));
//    int x,y;
//    for (y = 0; y < 7; ++y)
//	{
//		for (x = 0; x < 5; ++x)
//		{
//             putimage(this->area,x*32, y*32, img1);//»­±³¾°
//		}
//	}
//
//    delimage(img1);

return 1;
}

PWindowArea NewWindowArea()
{
    PWindowArea area = (PWindowArea)malloc(sizeof(WindowArea));

    area->Clear = ClearCore;

    return area;

}
void FreeWindowArea(PWindowArea window_area)
{
    free(window_area);
}
