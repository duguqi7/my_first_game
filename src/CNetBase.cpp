#include "CNetBase.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>

using std::cout;
using std::endl;

CNetBase::CNetBase()
{
    //ctor
    m_iProtocolType = c_iTCPType;
    m_iSocketFd = -1;
    m_iServerPort = c_iServerPort;
    m_iClientPort = 0;
    memset(&m_stAddress, 0, sizeof(m_stAddress));
}

CNetBase::~CNetBase()
{
    //dtor
}

//UDP interface
int CNetBase::CreateUDPServer(string sIP, int iPort)
{
    int iRet = -1;
    int iLen = sizeof(m_stAddress);

	m_iSocketFd = socket(AF_INET, SOCK_DGRAM, 0);
	if(m_iSocketFd < 0)
	{
		cout << "socket error" << endl;
		return -1;
	}
    m_stAddress.sin_family = AF_INET;
    m_stAddress.sin_port = htons(iPort);

    if(0 == sIP.size())
    {
       m_stAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        m_stAddress.sin_addr.s_addr = inet_addr(sIP.c_str());
    }

    iRet = bind(m_iSocketFd,(struct sockaddr*)&m_stAddress, iLen);
    if( iRet < 0 )
    {
        cout << "bind error" << endl;
        return -1;
    }

    m_iProtocolType = c_iUDPType;

	return 0;
}
int CNetBase::CreateUDPClient(string sIP, int iPort)
{
    if(0 == sIP.size())
    {
       cout << "UDP client IP address shouldn't be NULL" << endl;
       return -1;
    }

	m_iSocketFd = socket(AF_INET, SOCK_DGRAM, 0);
	if(m_iSocketFd < 0)
	{
		cout << "socket error" << endl;
		return -1;
	}
    m_stAddress.sin_family = AF_INET;
    m_stAddress.sin_port = htons(iPort);
    m_stAddress.sin_addr.s_addr = inet_addr(sIP.c_str());

    m_iProtocolType = c_iUDPType;

	return 0;
}
int CNetBase::NonBlockReadUDPSocket(char *sBuffer, int iBufferlen)
{
    int iFlag;
    iFlag = fcntl(m_iSocketFd, F_GETFL, 0);
    iFlag |= O_NONBLOCK;
    if(fcntl(m_iSocketFd, F_SETFL, iFlag) < 0)
    {
        cout << "Set socket to nonblock failed!" <<endl;
        return -1;
    }

    int iRet;
	size_t len=sizeof(m_stAddress);
	iRet = recvfrom(m_iSocketFd, sBuffer, iBufferlen, 0, (struct sockaddr *)&m_stAddress, (socklen_t*)&len );
	return iRet;
}
int CNetBase::BlockReadUDPSocket(char *sBuffer, int iBufferlen)
{
    fcntl(m_iSocketFd, F_SETFL, 0);

    int iRet;
	size_t len=sizeof(m_stAddress);
	iRet = recvfrom(m_iSocketFd, sBuffer, iBufferlen, 0, (struct sockaddr *)&m_stAddress,(socklen_t*)&len );
	return iRet;
}
int CNetBase::WriteUDPSocket(char *sBuffer, int iBufferlen)
{
    size_t iLen = sizeof(m_stAddress);
	return sendto(m_iSocketFd, sBuffer, iBufferlen, 0, (struct sockaddr *)&m_stAddress, iLen);
}
//TCP interface
int CNetBase::CreateTCPServer(string sIP, int iPort)
{
    int iLen = sizeof(m_stAddress);

    m_iSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if(m_iSocketFd < 0)
    {
        cout << "socket error" << endl;
        return -1;
    }
    m_stAddress.sin_family = AF_INET;
    m_stAddress.sin_port = htons(iPort);

    if(0 == sIP.size())
    {
        m_stAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        m_stAddress.sin_addr.s_addr = inet_addr(sIP.c_str());
    }

    int iRet = bind(m_iSocketFd,(const struct sockaddr*)&m_stAddress, iLen);
    if( iRet < 0 )
    {
        cout << errno << " bind error" << endl;
        return -1;
    }
    m_iProtocolType = c_iTCPType;
    return 0;
}
int CNetBase::CreateTCPClient(string sIP, int iPort)
{
    if(0 == sIP.size())
    {
        cout << "TCP client IP address shouldn't be NULL" << endl;
        return -1;
    }

    m_iSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if(m_iSocketFd < 0)
    {
        cout << "socket error" << endl;
        return -1;
    }
    m_stAddress.sin_family = AF_INET;
    m_stAddress.sin_port = htons(iPort);
    m_stAddress.sin_addr.s_addr = inet_addr(sIP.c_str());
    m_iProtocolType = c_iTCPType;
    return 0;
}
int CNetBase::NonBlockReadTCPSocket(char *sBuffer, int iBufferlen, int iConSocket)
{
    int iFlag;
    if(iConSocket < 0)
    {
        iConSocket = m_iSocketFd;
    }
    iFlag = fcntl(iConSocket, F_GETFL, 0);
    iFlag |= O_NONBLOCK;
    if(fcntl(iConSocket, F_SETFL, iFlag) < 0)
    {
        cout << errno << " - Set socket to nonblock failed!" << endl;
        return -1;
    }

    int iRet;
    iRet = read(iConSocket, sBuffer, iBufferlen);
    return iRet;
}
int CNetBase::BlockReadTCPSocket(char *sBuffer, int iBufferlen, int iConSocket)
{
    int iRet;
    if(iConSocket < 0)
    {
        iConSocket = m_iSocketFd;
    }
    fcntl(iConSocket, F_SETFL, 0);

    iRet = read(iConSocket, sBuffer, iBufferlen);
    return iRet;
}
int CNetBase::WriteTCPSocket(char *sBuffer, int iBufferlen, int iConSocket)
{
    if(iConSocket < 0)
    {
        iConSocket = m_iSocketFd;
    }
    return write(iConSocket, sBuffer, iBufferlen);
}

//tcp server
int CNetBase::TCPServerListen(int iBacklog)
{
    return listen(m_iSocketFd, iBacklog);
}
int CNetBase::TCPServerAccept(void)
{
    socklen_t len = sizeof(m_stAddress);
    return accept(m_iSocketFd, (struct sockaddr*)&m_stAddress, &len);
}
//tcp client
int CNetBase::TCPClientConnect(void)
{
    return connect(m_iSocketFd, (struct sockaddr*)&m_stAddress, sizeof(m_stAddress));
}
int CNetBase::DestroySocket(void)
{
    return close(m_iSocketFd);
}