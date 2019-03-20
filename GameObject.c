#include "GameObject.h"
#include "stdlib.h"

static PPosition GetPositionCore(void * _this)
{
    PGameObject this=(PGameObject)_this;
    return this->_position_ptr;
}

static void HandleEventCore(void* obj)
{
    PGameObject _this = (PGameObject)obj;

}

static void UpdateDataCore(void* _this_obj)
{
    PGameObject _this = (PGameObject)_this_obj;
    //_this->_speed = 100;
    _this->_position_ptr->Y-=2;
    if(_this->_speed <= 0)
    {
        _this->_current_frame = 0;
    }
    else
    {
        /**
        当前的帧索引为0时，下一帧只能时0或者1，否则称之为跳帧，意思为跳过中间的图像表现
        _this->_current_frame增量必须小于等于1，所以根据此原则则有下面的推论
        设SDL_GetTicks简写为t，speed简写为s，最大帧数量简写为fx
        设前一次是帧索引是f0=(t0/s)%fx
        本次的桢索引为f1=(t1/s)%fx
        f1-f0 = (t1/s)%fx - (t0/s)%fx <=1       设dt=t1-t0,dt相当于每次循环所需要的时间
        (dt/s)%fx<=1
        dt/s <= 1                               又dt>=1000/fps
        1000/fps<=dt<=s
        16.6<=100
        所以成立，得出推论当帧率固定为60时，速度不能低于16，与最大帧数量无关
        **/
        _this->_current_frame = (SDL_GetTicks()/ _this->_speed)%_this->_current_frames_length;
    }
}

static void RenderCore(void* this_obj)
{
    PGameObject _this = (PGameObject)this_obj;
    if(_this->_current_frames != NULL)
    {
        SDL_Texture* temp=_this->_current_frames[_this->_current_frame];
        SDL_Rect temp_rect;
        temp_rect.x = 64;
        temp_rect.y = _this->_position_ptr->Y;
        temp_rect.w = 64;
        temp_rect.h = 64;
        SDL_RenderCopy(GetRenderer(),temp,NULL,&temp_rect);
    }

}


static void SwitchFramesCore(PGameObject _this_obj,SDL_Texture** new_frames,int new_frames_length)
{
    _this_obj->_current_frames = new_frames;
    _this_obj->_current_frames_length=new_frames_length;
    _this_obj->_current_frame=0;
}

PGameObject NewGameObject( )
{
    PGameObject temp = (PGameObject)malloc(sizeof(GameObject));
    temp->HandleEvent = HandleEventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;
    temp->_position_ptr = NewPosition();
    temp->_current_frames = NULL;
    temp->_current_frame=-1;
    temp->_speed=100;
    temp->_position_ptr->Y=600;

    return temp;
}
void FreeGameObject(PGameObject object)
{
    FreePosition(object->_position_ptr);
    free(object);
}
