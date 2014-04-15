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


// 开户
int BankService::OpenAccount(Account& account)
{
	MysqlDB db;
	Server& server = Singleton<Server>::Instance();

	try
	{
		db.Open(server.GetDbServerIp().c_str(),
			server.GetDbUser().c_str(),
			server.GetDbPass().c_str(),
			server.GetDbName().c_str(),
			server.GetDbServerPort());

		db.StartTransaction();
		stringstream ss;
		ss << "insert into bank_account values(null, '" <<
			account.name <<"', '"<<
			account.pass<<"', '"<<
			account.id<<"', "<<
			setprecision(2) << setiosflags(ios::fixed) << account.balance<<", now(), "<<
			0<<");";
		unsigned long long ret = db.ExecSQL(ss.str().c_str());
		ss.clear();
		ss.str("");
		account.account_id = static_cast<int>(db.GetInsertId());
		ss<<"insert into trans values(null, "<<
			account.account_id<<", null, "<<
			1<<", "<<
			setprecision(2)<<setiosflags(ios::fixed)<<account.balance<<", "<<
			setprecision(2)<<setiosflags(ios::fixed)<<account.balance<<
			",  now());";

		ret = db.ExecSQL(ss.str().c_str());
		db.Commit();

		ss.clear();
		ss.str("");
		ss<<"select open_date from bank_account where account_id='"<<
			account.account_id<<"';";
		MysqlRecordset rs = db.QuerySQL(ss.str().c_str());
		account.op_date = rs.GetItem(0, "open_date");

	}
	catch (Exception& e)
	{
		LOG_INFO<<e.what();
		db.Rollback();
		return -1;
	}

	return 0;
}


// 存款
int BankService::Deposit(Account& account)
{
		/*
	select balance from bank_account where account_id=5 for update;
	update bank_account set balance=balance+100 where account_id=5;
	insert into trans values(...);
	*/


	MysqlDB db;
	Server& server = Singleton<Server>::Instance();

	try
	{
		db.Open(server.GetDbServerIp().c_str(),
			server.GetDbUser().c_str(),
			server.GetDbPass().c_str(),
			server.GetDbName().c_str(),
			server.GetDbServerPort());

		db.StartTransaction();

		stringstream ss;
		ss<<"select balance from bank_account where account_id="<<
			account.account_id<<
			" and flag=0 for update;";

		MysqlRecordset rs = db.QuerySQL(ss.str().c_str());
		if (rs.GetRows() < 1)	// 帐户不存在
			return 2;

		// 帐户余额
		double balance = Convert::StringToDouble(rs.GetItem(0, "balance"));

		ss.clear();
		ss.str("");
		ss<<"update bank_account set balance=balance+"<<
			setprecision(2)<<setiosflags(ios::fixed)<<account.balance<<" where account_id="<<
			account.account_id<<";";
		unsigned long long ret = db.ExecSQL(ss.str().c_str());


		ss.clear();
		ss.str("");
		ss<<"insert into trans values(null, "<<
			account.account_id<<", null, "<<
			2<<", "<<
			setprecision(2)<<setiosflags(ios::fixed)<<account.balance<<", "<<
			setprecision(2)<<setiosflags(ios::fixed)<<balance+account.balance<<
			",  now());";

		ret = db.ExecSQL(ss.str().c_str());

		/*
		select a.name, b.balance, b.trans_date
		from bank_account a, 
		(select account_id, balance, trans_date from trans where trans_id=1) b
		where a.account_id=b.account_id;
		*/

		int trans_id = static_cast<int>(db.GetInsertId());
		db.Commit();

		ss.clear();
		ss.str("");
		ss<<"select a.name, b.trans_date "<<
			"from bank_account a, "<<
			"(select account_id, trans_date from trans where trans_id="<<
			trans_id<<") b "<<
			"where a.account_id=b.account_id;";
		rs.Clear();
		rs = db.QuerySQL(ss.str().c_str());
		account.name = rs.GetItem(0, "name");
		account.op_date = rs.GetItem(0, "trans_date");
		account.balance += balance;


	}
	catch (Exception& e)
	{
		db.Rollback();
		LOG_INFO<<e.what();
		return -1;
	}

	return 0;
}

// 取款
int BankService::WithDraw(Account& account)
{
	return 0;
}
// 转帐
int BankService::Transfer(Account& account, const string& otherAccountId)
{
	
	return 0;
}
// 查询余额
int BankService::BalanceInquiry(Account& account)
{
	
	return 0;
}

// 修改密码
int BankService::ChangePassword(Account& account, const string& newPass)
{
	
	return 0;
}

// 查询某日报表
int BankService::QueryDayBill(list<TransDetail>& result, int page, const string& date)
{
	
	return 0;
}
// 根据日期查询明细
int BankService::QueryHistoryBill(list<TransDetail>& result, int page, const string& begin, const string& end)
{
	
	return 0;
}
// 根据帐号查询明细
int BankService::QueryAccountHistoryBill(list<TransDetail>& result, int page, const string& accountId, const string& begin, const string& end)
{
	
	return 0;
}

// 销户
int BankService::CloseAccount(Account& account, double& interest)
{
	
	return 0;

}
