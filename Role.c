#include <stdio.h>
#include "Role.h"
#include "CommonResource.h"


PRole NewRole(void)
{
    PRole temp=NewGameObject(GetEvnet);
    int i,j,k,index,t,t_back;
    i=j=k=index=t=t_back=0;
    char buffer[200],word[10];
    FILE* fp = fopen("resource/role/img.rol","r");
    do
    {
        while( NULL != fgets(buffer,200,fp) && j<DIRECTION_ENUM_MAX )
        {
            index =0;

            for(k = 0; k<GAME_OBJECT_FRAME_MAX; k++ )
            {
                if( 0 == sscanf(buffer+index,"%s",word) )
                    break;
                index += strlen(word);
                t_back = atoi(word);
                if( 0 == sscanf(buffer+index,"%s",word) )
                    break;
                index += strlen(word);
                t = atoi(word);
                temp->Frames[0][j][k] = GetTransparentTexture(GetTotalSurface(),t,GetTotalBackSurface(),t_back);
            }

            k++;
            j++;
        }


        fclose(fp);
        return temp;
    }while(false);

    fclose(fp);
    FreeRole(temp);
    return temp;
}
void FreeRole(PRole role)
{
    FreeGameObject(role);
}
