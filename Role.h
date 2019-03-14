#ifndef ROLE_H
#define ROLE_H

#include "GameObject.h"


typedef PGameObject PRole;

PRole NewRole(void);
void FreeRole(PRole);

#endif // ROLE_H
