#include <memory>
#include "Server.h"

#include "../Public/Socket.h"
#include "../Public/Logging.h"
#include "BankThread.h"


Server::Server()
{
	Socket::Startup();
}

Server::Server(const Server& rhs)
{
}
Server::~Server()
{
	Socket::Cleanup();
}

int Server::Start()
{
	LOG_INFO<<"Start Server.....";
	Socket sock;
	sock.Create();
	if(!sock.Bind(NULL, 8888))
	{
		return 1;
	}
	if (!sock.Listen())
		return 1;


	while (1)
	{
		std::auto_ptr<Socket> conn(new Socket);
		conn->socket_ = sock.Accept();
		if(!conn->IsValid())
			continue;
		BankThread* bt = new BankThread(conn);
		bt->SetAutoDel(true);
		bt->Start();
		
	}

	return 0;

}
