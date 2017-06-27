#include "../incl/socket.h"

DDSocket::DDSocket()
{
}

DDSocket::~DDSocket()
{
}

DDSocket DDSocket::Create()
{
	return DDSocket();
}

void DDSocket::Release()
{

}

DDSocket& DDSocket::operator =(const DDSocket &ddsock)
{
	return *this;
}