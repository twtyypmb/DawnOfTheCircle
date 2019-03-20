#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "GameCoreProcessInterface.h"
#include "SDL.h"
#include "SDL_image.h"


typedef struct _GameObject GameObject;
typedef GameObject* PGameObject;


typedef void (* SwitchFramesFun)(PGameObject _this_obj,SDL_Texture** new_frames,int new_frames_length);

// ��Ϸ�еĶ��󣬲�Ҫֱ��ʵ��������Ϊ��֪��ͼ����Դ

struct _GameObject
{
    PPosition _position_ptr;

    SDL_Texture** _current_frames;// �ж���״̬���ж���frame
    int _current_frames_length;
    char Name[10];
    int _speed;
    int _current_frame;

    GetPositionFun GetPosition;
    HandleEventFun HandleEvent;
    UpdateDataFun UpdateData;
    RenderFun Render;

    SwitchFramesFun SwitchFrames;
};



PGameObject NewGameObject( void );
void FreeGameObject(PGameObject);

#endif // GAME_OBJECT_H
