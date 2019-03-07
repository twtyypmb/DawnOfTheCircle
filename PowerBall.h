#ifndef POWER_BALL_H
#define POWER_BALL_H

typedef struct
{
    int radius;
    unsigned int color1;
    unsigned int color2;
    int positionx;
    int positiony;
    unsigned char blr_alpha;
}PowerBall;

typedef PowerBall* PPowerBall;

PPowerBall NewPowerBall()
{
    PowerBall* temp=(PowerBall*)malloc(sizeof(PowerBall));
    temp.radius = 1;
    temp.color1=0x7777ff;
    temp.color2=0xffffff;
    temp.blr_alpha=0xff;
    return temp;
}

void FreePowerBall(PPowerBall temp)
{
    free(temp);
}



#endif // POWER_BALL_H
