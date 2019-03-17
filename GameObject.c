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
    _this->_current_frame++;
    if(_this->_current_frame>= GAME_OBJECT_FRAME_MAX)
    {
        _this->_current_frame = 0;
    }
}

static void RenderCore(void* this_obj)
{
    PGameObject _this = (PGameObject)this_obj;
    SDL_Texture* temp=_this->Frames[0][_this->Direction][_this->_current_frame];
    SDL_RenderCopy(GetRenderer(),temp,NULL,NULL);
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

    return temp;
}
void FreeGameObject(PGameObject object)
{
    FreePosition(object->_position_ptr);
    free(object);
}
