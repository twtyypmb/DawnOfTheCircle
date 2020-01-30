#ifndef SIZE_H
#define SIZE_H


typedef struct
{
    int Width;
    int Height;
}Size;

typedef Size* PSize;


PSize NewSize();
PSize NewSizeWH(int width,int height);

void FreeSize(PSize position_ptr);
#endif // SIZE_H