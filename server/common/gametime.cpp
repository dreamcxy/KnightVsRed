#include "gametime.h"
#include <string.h>


CGameTime::CGameTime()
{
    memset(&m_stCurTimeVal, 0, sizeof(m_stCurTimeVal));

    Update();
}

void CGameTime::Update()
{
    gettimeofday(&m_stCurTimeVal, nullptr);
}