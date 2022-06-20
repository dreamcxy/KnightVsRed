#include "gametime.h"


void CGameTime::Update()
{
    gettimeofday(&m_stCurTimeVal, NULL);
}