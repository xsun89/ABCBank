#include "BankService.h"

#include "../Server.h"
#include "../../Public/Logging.h"
#include "../../Public/Exception.h"
#include "../../Public/JUtil.h"
#include "../DAL/MysqlDB.h"

#include <sstream>
using namespace std;

using namespace DAL;
using namespace PUBLIC;

int BankService::UserLogin(const string& user, const string& pass)
{
	try{
		MysqlDB db;
		Server& server = Singleton<Server>::Instance();
		db.Open(server.GetDbServerIp().c_str(), server.GetDbUser().c_str(), 
			server.GetDbPass().c_str(), server.GetDbName().c_str(), server.GetDbServerPort());

		stringstream query;
		query << "select * from teller where TELLER_NAME = '"
			<< user << "' and TELLER_PASS = '" <<pass << "';";

		MysqlRecordset recoredSet  = db.QuerySQL(query.str().c_str());

		if (recoredSet.GetRows() < 0)
			return 1;


	}catch(Exception& e)
	{
		LOG_INFO<<e.what();
	}
	return 0;
}


// ����
int BankService::OpenAccount(Account& account)
{
	
	return 0;
}


// ���
int BankService::Deposit(Account& account)
{
	
	return 0;
}

// ȡ��
int BankService::WithDraw(Account& account)
{
	return 0;
}
// ת��
int BankService::Transfer(Account& account, const string& otherAccountId)
{
	
	return 0;
}
// ��ѯ���
int BankService::BalanceInquiry(Account& account)
{
	
	return 0;
}

// �޸�����
int BankService::ChangePassword(Account& account, const string& newPass)
{
	
	return 0;
}

// ��ѯĳ�ձ���
int BankService::QueryDayBill(list<TransDetail>& result, int page, const string& date)
{
	
	return 0;
}
// �������ڲ�ѯ��ϸ
int BankService::QueryHistoryBill(list<TransDetail>& result, int page, const string& begin, const string& end)
{
	
	return 0;
}
// �����ʺŲ�ѯ��ϸ
int BankService::QueryAccountHistoryBill(list<TransDetail>& result, int page, const string& accountId, const string& begin, const string& end)
{
	
	return 0;
}

// ����
int BankService::CloseAccount(Account& account, double& interest)
{
	
	return 0;

}
