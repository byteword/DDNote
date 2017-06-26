#pragma once

#ifndef __DDNOTE_LIB_SOCKET__H__INCLUDDED__
#define __DDNOTE_LIB_SOCKET__H__INCLUDDED__

struct _DDSocketCtx;
class DDSocket {
private:
	_DDSocketCtx *m_ctx;
protected:
	DDSocket();
	virtual ~DDSocket();
public:
	static DDSocket Create();
	void Release();
public:
	DDSocket& operator =(const DDSocket &ddsock);
};


#endif //__DDNOTE_LIB_SOCKET__H__INCLUDDED__