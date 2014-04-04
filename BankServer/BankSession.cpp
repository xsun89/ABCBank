#include "BankSession.h"
#include "TransactionManager.h"
#include "../Public/Exception.h"
#include "../Public/Singleton.h"#include <iostream>
using namespace PUBLIC;

BankSession::BankSession(std::auto_ptr<Socket>& socket) : socket_(socket), isDead_(false)
{
	requestPack_ = (RequestPack*)buffer_;
}


BankSession::~BankSession(void)
{
}

void BankSession::Process()
{
	Recv();
	DoAction();
}

void BankSession::Send(const char* buf, size_t len)
{
	socket_->SendN(buf, len);
}

void BankSession::Recv()
{
	int ret;
	ret = socket_->RecvN(buffer_, sizeof(RequestHead));
	if(ret == 0)
	{
		throw Exception("Client Closed");
	}else if(ret != sizeof(RequestHead))
	{
		throw Exception("Receiving Data package Error");
	}

	uint16 cmd = Endian::NetworkToHost16(requestPack_->head.cmd);
	uint16 len = Endian::HostToNetwork16(requestPack_->head.len);

	requestPack_->head.cmd = cmd;
	requestPack_->head.len = len;

	ret = socket_->RecvN(requestPack_->buf, len);
	if (ret == 0)	
		throw Exception("Client Closed");	else if (ret != len)
	{
		throw Exception("Receiving Data package Error");
	}}

void BankSession::DoAction()
{
	Singleton<TransactionManager>::Instance().DoAction(*this);
}
