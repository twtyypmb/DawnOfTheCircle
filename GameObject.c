#include "GameObject.h"
#include "stdlib.h"

static PPosition GetPositionCore(void * _this)
{
    PGameObject this=(PGameObject)_this;
    return this->_position_ptr;
}

static void HandleEnventCore(void* obj)
{
    PGameObject _this = (PGameObject)obj;
    if( _this->GetEvent != NULL )
    {
        SDL_Event temp_event = _this->GetEvent();
        switch(temp_event.type)
        {
        case SDL_KEYDOWN:
            switch (temp_event.key.keysym.sym)
			{
			case SDLK_w:
				_this->Velocity->Y = -1;
				_this->Status = MOVING;
				break;
			case SDLK_a:
				_this->Velocity->X = -1;
				_this->Status = MOVING;
				break;
			case SDLK_d:
				_this->Velocity->X = 1;
				_this->Status = MOVING;
				break;
			case SDLK_s:
				_this->Velocity->Y = 1;
				_this->Status = MOVING;
				break;
			default:
				break;
			}
        break;
        case SDL_KEYUP:
            switch (temp_event.key.keysym.sym)
            {
            case SDLK_w:
                _this->Velocity->Y = 0;
                _this->Status = IDLE;
                break;
            case SDLK_a:
                _this->Velocity->X = 0;
                _this->Status = IDLE;
                break;
            case SDLK_d:
                _this->Velocity->X = 0;
                _this->Status = IDLE;
                break;
            case SDLK_s:
                _this->Velocity->Y = 0;
                _this->Status = IDLE;
                break;
            case SDLK_ESCAPE:
                //isRunning = false;
            default:
                break;
            }
        break;
        }


    }
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
        _this->_current_frame = (SDL_GetTicks()/ _this->_speed)%GAME_OBJECT_FRAME_MAX;
    }
}

static void RenderCore(void* this_obj)
{
    PGameObject _this = (PGameObject)this_obj;
    SDL_Texture* temp=_this->Frames[0][_this->Direction][_this->_current_frame];
    SDL_Rect temp_rect;
    temp_rect.x = 64;
    temp_rect.y = _this->_position_ptr->Y;
    temp_rect.w = 64;
    temp_rect.h = 64;
    SDL_RenderCopy(GetRenderer(),temp,NULL,&temp_rect);
}

PGameObject NewGameObject( GetEventFun GetEvent )
{
    PGameObject temp = (PGameObject)malloc(sizeof(GameObject));
    temp->HandleEnvent = HandleEnventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;
    temp->_position_ptr = NewPosition();
    temp->Velocity = NewPosition();
    temp->GetEvent = GetEvent;
    temp->_current_frame=-1;
    temp->Direction = UP;
    temp->Status = IDLE;
    temp->_speed=100;
    temp->_position_ptr->Y=600;

    return temp;
}
void FreeGameObject(PGameObject object)
{
    FreePosition(object->_position_ptr);
    free(object);
}
