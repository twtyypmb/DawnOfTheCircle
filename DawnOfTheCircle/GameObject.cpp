#include "GameObject.h"
#include "CommonResource.h"
#include "stdlib.h"
#include "RenderMethods.h"

static PRect GetRectCore(void * _this)
{
    return ((PGameObject)_this)->rect;
}

static void HandleEventCore(void* obj)
{
    PGameObject _this = (PGameObject)obj;

}

static void UpdateDataCore(void* _this_obj)
{
    PGameObject _this = (PGameObject)_this_obj;
    //_this->_speed = 100;
    //_this->_position_ptr->Y-=2;
    if(_this->_speed <= 0)
    {
        _this->_current_frame = 0;
    }
    else
    {
        /**
        ��ǰ��֡����Ϊ0ʱ����һֻ֡��ʱ0����1�������֮Ϊ��֡����˼Ϊ�����м��ͼ�����
        _this->_current_frame��������С�ڵ���1�����Ը��ݴ�ԭ���������������
        ��SDL_GetTicks��дΪt��speed��дΪs�����֡������дΪfx
        ��ǰһ����֡������f0=(t0/s)%fx
        ���ε�������Ϊf1=(t1/s)%fx
        f1-f0 = (t1/s)%fx - (t0/s)%fx <=1       ��dt=t1-t0,dt�൱��ÿ��ѭ������Ҫ��ʱ��
        (dt/s)%fx<=1
        dt/s <= 1                               ��dt>=1000/fps
        1000/fps<=dt<=s
        16.6<=100
        ���Գ������ó����۵�֡�ʹ̶�Ϊ60ʱ���ٶȲ��ܵ���16�������֡�����޹�
        **/
        _this->_current_frame = (GetTicks()/ _this->_speed)%_this->_current_frames_length;
    }
}

static void RenderCore(void* this_obj)
{
    PGameObject _this = (PGameObject)this_obj;
    if(_this->_current_frames != NULL)
    {
		PIMAGE temp=_this->_current_frames[_this->_current_frame];
		RenderImage(GetRenderer(), temp, _this->rect->position);
    }

}


static void SwitchFramesCore(PGameObject _this_obj, PIMAGE* new_frames,int new_frames_length)
{
    _this_obj->_current_frames = new_frames;
    _this_obj->_current_frames_length=new_frames_length;
    _this_obj->_current_frame=-1;
}

PGameObject NewGameObject( )
{
    PGameObject temp = (PGameObject)malloc(sizeof(GameObject));
    temp->HandleEvent = HandleEventCore;
    temp->UpdateData = UpdateDataCore;
    temp->GetRect = GetRectCore;
    temp->Render = RenderCore;
	temp->rect = NewRect();
    temp->_current_frames = NULL;
    temp->_current_frame=-1;
    temp->_speed=100;
    temp->SwitchFrames = SwitchFramesCore;
    return temp;
}
void FreeGameObject(PGameObject object)
{
    FreeRect(object->rect);
    free(object);
}
