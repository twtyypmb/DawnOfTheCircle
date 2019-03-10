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
				_this->GameObjectStatus = MOVING;
				break;
			case SDLK_a:
				_this->Velocity->X = -1;
				_this->GameObjectStatus = MOVING;
				break;
			case SDLK_d:
				_this->Velocity->X = 1;
				_this->GameObjectStatus = MOVING;
				break;
			case SDLK_s:
				_this->Velocity->Y = 1;
				_this->GameObjectStatus = MOVING;
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
                _this->GameObjectStatus = IDLE;
                break;
            case SDLK_a:
                _this->Velocity->X = 0;
                _this->GameObjectStatus = IDLE;
                break;
            case SDLK_d:
                _this->Velocity->X = 0;
                _this->GameObjectStatus = IDLE;
                break;
            case SDLK_s:
                _this->Velocity->Y = 0;
                _this->GameObjectStatus = IDLE;
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

static void UpdateDataCore(void* _this)
{
    PGameObject this = (PGameObject)_this;
}

static void RenderCore(void* _this)
{
    PGameObject this = (PGameObject)_this;

}

PGameObject NewGameObject( SDL_Texture*  texture,GetEventFun GetEvent )
{
    PGameObject temp = (PGameObject)malloc(sizeof(GameObject));
    temp->HandleEnvent = HandleEnventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;
    temp->_position_ptr = NewPosition();
    temp->Velocity = NewPosition();
    temp->texture = texture;
    temp->GetEvent = GetEvent;
    return temp;
}
void FreeGameObject(PGameObject object)
{
    FreePosition(object->_position_ptr);
    free(object);
}
