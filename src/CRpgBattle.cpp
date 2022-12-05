#include "CRpgBattle.h"

CRpgBattle::CRpgBattle()
{
    //ctor
    m_iWorkMode = c_iClientMode;
    m_iPlayerNum = 1;

    //server member
    m_iGameStep = c_iGameStepStandby;

    //client member
    m_iPlayerId = 0;
    m_iAliveStat = 0;
    m_iHP = 0;
    m_iAtk = 0;
    m_iDef = 0;
    m_iSpd = 0;
}

CRpgBattle::~CRpgBattle()
{
    //dtor
}

void CRpgBattle::SetGamePlayerNum(int num)
{
    m_iPlayerNum = num;
}

int  CRpgBattle::GetGamePlayerNum(void)
{
    return m_iPlayerNum;
}

//server functions
int CRpgBattle::CreateServer(void)
{

    return 0;
}

//client functions
int CRpgBattle::CreateClient(void)
{

    return 0;
}