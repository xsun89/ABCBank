#include "Server.h"
#include "../Public/Singleton.h"

using namespace PUBLIC;
int main()
{
	return Singleton<Server>::Instance().Start();
}