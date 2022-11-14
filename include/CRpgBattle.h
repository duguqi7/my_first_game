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
        void SetGamePlayerNum(int players);
        int  GetGamePlayerNum(void);

        //server functions
        int CreateServer(void);

        //client functions
        int CreateClient(void);

    protected:
    private:
        int iWorkMode;
};

#endif // RPG_BATTLE_H
