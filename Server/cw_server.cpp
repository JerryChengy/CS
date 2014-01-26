#include "cw_socketserver.h"
#include "cw_connection.h"
#include "cw_packetdefine.h"
#include "cw_serverhandler.h"
#include "cw_connectionmanager.h"
#include "cw_packetfactorymanager.h"
#include "cw_packet.h"
#include "cw_handlerset.h"
#include "cw_time.h"
#include "cw_log.h"
#include "cw_serveriniset.h"
#include "cw_tableset.h"


bool Init()
{
	new CTimeManager;
	new CLogManager;
	new CServerIniSet;
	new CTableSet;

	new CPacketFactoryManager;
	new CPacketHandlerSet;
	new CConnectionManager;
	new CSocketServer;	

	CTimeManager::GetSingleton().Init();
	CLogManager::GetSingleton().Init();	

	bool bRet = CServerIniSet::GetSingleton().Init();
	if (!bRet)
	{
		return false;
	}
	bRet = CTableSet::GetSingleton().Init();
	if (!bRet)
	{
		return false;
	}

	CSocketServer::GetSingleton().Init(g_ServerIni.m_ServerNet.m_Port);
	bRet = CSocketServer::GetSingleton().Listen();
	if (!bRet)
	{
		return false;
	}
	/*LOG_DEBUG("port: %d, recvbuflen: %d, sendbuflen: %d", g_ServerIni.m_ServerNet.m_Port,
		g_ServerIni.m_ServerNet.m_ReceiveSocketBuffLen,
		g_ServerIni.m_ServerNet.m_SendSocketBuffLen);*/
	/*TABLE_TEST* pTestTable = Tables.m_Test.Row(1);
	if (pTestTable)
	{
		LOG_DEBUG("table test, nam: %s, level: %d, hp: %d, mp: %f, title: %d", pTestTable->m_Name,
			pTestTable->m_Level, pTestTable->m_Hp, 
			pTestTable->m_Mp, pTestTable->m_Title[0]);

	}*/
	
	return true;
}

void Work()
{
	while (1)
	{
		CSocketServer::GetSingleton().Work();
		::Sleep(10);
	}
}
int main()
{
	if (!Init())
	{
		return 0;
	}
	Work();	
	return 0;
};
