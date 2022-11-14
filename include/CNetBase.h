#ifndef CNETBASE_H
#define CNETBASE_H

#include <iostream>
#include <string>
#include <netinet/in.h>

using std::string;
const int c_iServerPort = 59999;
const int c_iBacklog = 5;

const int c_iTCPType = 1;
const int c_iUDPType = 2;

const int c_iObjSocket = -1;

class CNetBase
{
    public:
        CNetBase();
        virtual ~CNetBase();
        int DestroySocket(void);
        //UDP interface
        int CreateUDPClient(string sIP, int iPort = c_iServerPort);
        int CreateUDPServer(string sIP, int iPort = c_iServerPort);
        int NonBlockReadUDPSocket(char *sBuffer, int iBufferlen);
        int BlockReadUDPSocket(char *sBuffer, int iBufferlen);
        int WriteUDPSocket(char *sBuffer, int iBufferlen);
        //TCP interface
        int CreateTCPServer(string sIP, int iPort = c_iServerPort);
        int CreateTCPClient(string sIP, int iPort = c_iServerPort);
        int NonBlockReadTCPSocket(char *sBuffer, int iBufferlen, int iConSocket = c_iObjSocket);
        int BlockReadTCPSocket(char *sBuffer, int iBufferlen, int iConSocket = c_iObjSocket);
        int WriteTCPSocket(char *sBuffer, int iBufferlen, int iConSocket = c_iObjSocket);
        //tcp server
        int TCPServerListen(int iBacklog = c_iBacklog);
        int TCPServerAccept(void);
        //tcp client
        int TCPClientConnect(void);

    protected:
    private:
        int m_iProtocolType;
        int m_iSocketFd;
        int m_iServerPort;
        int m_iClientPort;
        struct sockaddr_in m_stAddress;
};

#endif // CNETBASE_H
