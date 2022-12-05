#ifndef CRPGBATTLEH
#define CRPGBATTLEH

const int c_iClientMode = 1;
const int c_iServerMode = 2;
const int c_iUniversalMode = 3;

const int c_iGameStepAction = 1;
const int c_iGameStepStandby = 2;

class CRpgBattle
{
    public:
        CRpgBattle();
        virtual ~CRpgBattle();
        //common functions
        void SetGamePlayerNum(int num);
        int  GetGamePlayerNum(void);

        //server functions
        int CreateServer(void);

        //client functions
        int CreateClient(void);

    protected:
    private:
        //common member
        int m_iWorkMode;
        int m_iPlayerNum;

        //server member
        int m_iGameStep;

        //client member
        int m_iPlayerId;
        int m_iAliveStat;
        int m_iHP;
        int m_iAtk;
        int m_iDef;
        int m_iSpd;

        //private function
        void GamePlayTask(void);
};

#endif // RPG_BATTLE_H
