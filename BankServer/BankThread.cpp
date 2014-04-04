#include <string>
#include <vector>
#include "BankThread.h"
#include "BankSession.h"
#include "../Public/Logging.h"
#include "../Public/StringUtil.h"
#include "../Public/Exception.h"
using namespace PUBLIC;
BankThread::BankThread()
	: JThread(), socket_(0)
{

}

BankThread::BankThread(std::auto_ptr<Socket>& sock) : JThread(), socket_(sock)
{

}

BankThread::~BankThread(void)
{

}

void BankThread::Run()
{	
	BankSession* bs = new BankSession(socket_);
	while (!bs->IsDead())
	{
		try
		{
			bs->Process();
		}
		catch (Exception& e)
		{
			LOG_INFO<<e.what();
			bs->Kill();
		}
	}

	delete bs;
}
