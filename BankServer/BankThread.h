#ifndef _BANKTHREAD_H_
#define _BANKTHREAD_H_
#include <memory>
#include "../Public/JThread.h"
#include "../Public/Socket.h"
using namespace PUBLIC;

class BankThread : public JThread
{
public:
	BankThread();
	BankThread(std::auto_ptr<Socket>& socket);
	~BankThread();

	virtual void Run();
private:
	std::auto_ptr<Socket> socket_;
};


#endif

