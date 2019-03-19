#include <stdio.h>
#include "Role.h"
#include "CommonResource.h"


PRole NewRole(void)
{
    PRole temp=NewGameObject(GetEvnet);
    int i,j,k,index,t,t_back;
    i=j=k=index=t=t_back=0;
    char buffer[200],word[10],frame1[10],frame2[10],frame3[10],frame4[10],frame5[10],frame6[10],frame7[10],frame8[10];
    FILE* fp = fopen("resource/role/img.rol","r");
    do
    {
        while( NULL != fgets(buffer,200,fp) && j<DIRECTION_ENUM_MAX )
        {
            index =0;
            k=0;

            sscanf(buffer,"%s %s %s %s %s %s %s %s",frame1,frame2,frame3,frame4,frame5,frame6,frame7,frame8);
            DebugTools_PrintDebugInfo("%s %s %s %s %s %s %s %s",frame1,frame2,frame3,frame4,frame5,frame6,frame7,frame8);
            temp->Frames[0][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame2),GetTotalSurface(),atoi(frame1));
            temp->Frames[0][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame4),GetTotalSurface(),atoi(frame3));
            temp->Frames[0][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame6),GetTotalSurface(),atoi(frame5));
            temp->Frames[0][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame8),GetTotalSurface(),atoi(frame7));
            //DisPlayTexture(GetRenderer(),temp->Frames[0][j][k-1]);

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
