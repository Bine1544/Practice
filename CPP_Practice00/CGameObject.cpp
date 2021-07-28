#include "CGameObject.h"
#include <stdio.h>

CGameObject::CGameObject()
{
	m_PosX = 0;
	m_PosY = 0;
}

CGameObject::~CGameObject()
{
	printf("CGameObject is destroyed");
}