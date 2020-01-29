#include "window_area_class.h"

bool window_area::clear_area(void)
{
    cleardevice(this->area);
    PIMAGE img1,total_img;//,img3;
    total_img = newimage();
	getimage(total_img,"resource\\image\\total.bmp",0, 0);
    img1 = newimage();
    getimage(img1,total_img,5*32,0*32,32,32);
    int x,y;
    for (y = 0; y < 7; ++y)
	{
		for (x = 0; x < 5; ++x)
		{
             putimage(this->area,x*32, y*32, img1);//画背景
		}
	}

    delimage(img1);
    delimage(total_img);
    return true;
}

bool window_area::init_area(int positionx, int positiony, int window_width, int window_height, int win_number)
{
    this->area=newimage(window_width, window_height);
    position[0]=positionx;
    position[1]=positiony;
    width_height[0]=window_width;
    width_height[1]=window_height;
    window_number=win_number;
    PIMAGE total_img,img1,img2;//,img3;
    total_img = newimage();
	getimage(total_img,"resource\\image\\total.bmp",0, 0);
    img1 = newimage();

    getimage(img1,total_img,5*32,0*32,32,32);
    //getch();
    int x,y;
    for (y = 0; y < 7; ++y)
	{
		for (x = 0; x < 5; ++x)
		{
             putimage(this->area,x*32, y*32, img1);//画背景
		}
	}
    delimage(img1);

    switch(win_number)
    {
        case 0:
            img1=newimage(32,32);
            img2= newimage(50,50);
            getimage(img1,total_img,1*32,17*32,32,32);
            putimage(img2,0,0,50,50,img1,0,0,32,32);
            putimage_transparent(this->area,img2,5,5,0x80ffff);//打印形象
            setcolor(EGERGB(0xff, 0xff, 0xff),this->area);
            setfont(20, 0, "宋体",this->area);
            setbkmode(TRANSPARENT,this->area);//字体底色透明
            outtextxy(3*32+5,1*32-10,"级",this->area);
            outtextxy(10,2*32,"生命",this->area);
            outtextxy(10,3*32,"攻击",this->area);
            outtextxy(10,4*32,"防御",this->area);
            outtextxy(10,5*32,"金币",this->area);
            outtextxy(10,6*32,"经验",this->area);
            delimage(img1);
            delimage(img2);
            break;
        case 1:
            img1=newimage(32,32);

            getimage(img1,total_img,6*32,2*32,32,32);
            putimage(this->area,10,0,img1);
            getimage(img1,total_img,8*32,2*32,32,32);
            putimage(this->area,10,32,img1);
            getimage(img1,total_img,7*32,2*32,32,32);
            putimage(this->area,10,64,img1);

            delimage(img1);

            setcolor(EGERGB(0xff, 0xff, 0xff),this->area);
            setfont(-16, 0, "宋体",this->area);
            setbkmode(TRANSPARENT,this->area);//字体底色透明
            outtextxy(3*32+10,0+10,"把",this->area);
            outtextxy(3*32+10,1*32+10,"把",this->area);
            outtextxy(3*32+10,2*32+10,"把",this->area);
            //delimage(img2);
            break;
        case 2:
            setcolor(EGERGB(0xff, 0xff, 0xff),this->area);
            setfont(-16, 0, "宋体",this->area);
            setbkmode(TRANSPARENT,this->area);//字体底色透明
            //outtextxy(1*32+3,10,"第    层",this->area);
            outtextxy(5,1*32,"U保存 J查看怪物",this->area);
            outtextxy(5,2*32,"P读取 KL跳一层",this->area);
            break;
        default:break;
    }
    delimage(total_img);
    return true;
}
