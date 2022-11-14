#include <iostream>
#include <unistd.h>
#include "CNetBase.h"
#include "CRpgBattle.h"
#include <cstring>
#include <errno.h>

using namespace std;

const int c_iBufLen = 1024;

int main()
{
    int iRet = -1;
    int iConSocket = -1;
    char buffer[c_iBufLen] = {0};
    cout << "Welcom to my game!" << endl;
    cout << "Game server initing..." << endl;
    cout << "OK! ready for 2 players to join." << endl;

    CNetBase oNet;

    #if 0
    iRet = oNet.CreateTCPServer("127.0.0.1");
    if(-1 == iRet) { return iRet; }

    iRet = oNet.TCPServerListen();
    if(iRet != 0)
    {
        cout << "TCPServerListen failed." << endl;
        oNet.DestroySocket();
        return -1;
    }
    else
    {
        cout << "TCPServerListen OK." << endl;
        iConSocket = oNet.TCPServerAccept();
        if(-1 == iConSocket)
        {
            cout << iConSocket << ", TCPServerAccept failed." << endl;
            oNet.DestroySocket();
            return -1;
        }

        cout << "TCPServerAccept OK." << endl;
        iRet = oNet.BlockReadTCPSocket(buffer, c_iBufLen, iConSocket);
        cout << iRet << endl;
        if(iRet <= 0)
        {
            cout << "BlockReadTCPSocket error" << endl;
            oNet.DestroySocket();
            return -1;
        }
        else
        {
            cout << "received msg" << endl;
            cout << buffer << endl;
        }
    }
    #else
    iRet = oNet.CreateTCPClient("127.0.0.1");
    if(-1 == iRet) { return iRet; }

    iRet = oNet.TCPClientConnect();
    if(-1 == iRet) 
    {
        cout << "TCPClientConnect failed." << endl;
        oNet.DestroySocket();
        return iRet; 
    }

    cout << "TCPClientConnect OK." << endl;
    strncpy(buffer, "Hello", strlen("Hello"));
    iRet = oNet.WriteTCPSocket(buffer, strlen(buffer));
    if(iRet != -1)
    {
        cout << "WriteUDPSocket OK" << endl;
        oNet.DestroySocket();
        return 0;
    }

    #endif



    while(1)
    {
        sleep(1);
    }
    oNet.DestroySocket();
    return 0;
}
