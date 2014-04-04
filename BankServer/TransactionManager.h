#ifndef _TRANSACTIONMANAGER_H_
#define _TRANSACTIONMANAGER_H_
#include <map>
#include <string>
#include "../Public/Singleton.h"
#include "BankSession.h"
#include "CMD/Transaction.h"

using namespace CMD;
class TransactionManager
{
	friend class Singleton<TransactionManager>;
public:
	bool DoAction(BankSession& session);
private:
	std::map<uint16, Transaction*> m_actions;
	TransactionManager();
	TransactionManager(const TransactionManager& rhs);
	~TransactionManager();

};
#endif

