#include "RenderMethods.h"

void RenderImage(PIMAGE dest_area, PIMAGE p, PPosition pp)
{
	putimage(dest_area, pp->X, pp->Y, p);
}