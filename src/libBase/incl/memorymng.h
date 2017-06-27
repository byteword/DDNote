#ifndef __DDNOTE__MEMORY_MANAGER__H__INCLUDDED__
#define __DDNOTE__MEMORY_MANAGER__H__INCLUDDED__
#pragma once

#ifndef NULL
#define NULL (0)
#endif // NULL

#include <../headers/ddmemorymng.h>

class DDVarPtr
{

private:

	DDVarHeader *_header;        // 4 byte

public:

	inline DDVarPtr()
	{
		_header = NULL;
	}

	inline explicit DDVarPtr(DDVarHeader* header)
	{
		_header = NULL;
		Set(header);
	}

	inline explicit DDVarPtr(const DDVarPtr& ptr)
	{
		_header = NULL;
		Set(ptr._header);
	}

	~DDVarPtr()
	{
		Set(NULL);
	}

public:

	inline bool operator == (const DDVarPtr& ptr) const
	{
		return this->_header == ptr._header;
	}

	inline bool operator != (const DDVarPtr& ptr) const
	{
		return this->_header != ptr._header;
	}

	inline bool operator < (const DDVarPtr& ptr) const
	{
		return this->_header < ptr._header;
	}

	inline bool operator <= (const DDVarPtr& ptr) const
	{
		return this->_header <= ptr._header;
	}

	inline bool operator > (const DDVarPtr& ptr) const
	{
		return this->_header > ptr._header;
	}

	inline bool operator >= (const DDVarPtr& ptr) const
	{
		return this->_header >= ptr._header;
	}

private:

	void Set(DDVarHeader* header)
	{
		if (this->_header != NULL)
			this->_header->Release();
		this->_header = header;
		if (this->_header != NULL)
			this->_header->AddRef();
	}

public:

	inline DDVarPtr& operator = (const DDVarPtr& ptr)
	{
		Set(ptr._header);
		return *this;
	}

public:
	static DDVarPtr NULLPtr;
};


template<class T>
class TPtr : public DDVarPtr
{
public:
	inline TPtr() { }
	inline explicit TPtr(T* ptr) : DDVarPtr(DDVarHeader::Header(ptr)) {}
	inline explicit TPtr(const TPtr& ptr) : DDVarPtr(ptr) {}

	template<class V>
	inline explicit TPtr(const TPtr<V>& ptr) : DDVarPtr((const DDVarPtr&)ptr)
	{
	}

public:

	inline DDVarPtr& operator()()
	{
		return *this;
	}

	inline const DDVarPtr& operator()() const
	{
		return *this;
	}

	template<class V>
		inline bool operator == (const TPtr<V>& ptr) const
	{
			return ((const DDVarPtr&)*this) == ((const DDVarPtr&)ptr);
	}

	template<class V> 
		inline bool operator != (const TPtr<V>& ptr) const
	{
			return ((const DDVarPtr&)*this) != ((const DDVarPtr&)ptr);
	}

	template<class V>
	inline bool operator < (const TPtr<V>& ptr) const
	{
		return ((const DDVarPtr&)*this) < ((const DDVarPtr&)ptr);
	}

	template<class V>
	inline bool operator <= (const TPtr<V>& ptr) const
	{
		return ((const DDVarPtr&)*this) <= ((const DDVarPtr&)ptr);
	}

	template<class V>
	inline bool operator > (const TPtr<V>& ptr) const
	{
		return ((const DDVarPtr&)*this) > ((const DDVarPtr&)ptr);
	}


	template<class V>
	inline bool operator >= (const TPtr<V>& ptr) const
	{
		return ((const DDVarPtr&)*this) >= ((const DDVarPtr&)ptr);
	}

public:

	template<class V>
	inline TPtr operator = (const TPtr<T>& ptr)
	{
		((const DDVarPtr&)*this) = ((const DDVarPtr&)ptr);
		return *this;
	}

public:
	inline T* operator ->() const
	{
		return reinterpret_cast<T*>(_header->Body());
	}

	inline T& operator *() const
	{
		return *reinterpret_cast<T*>(_header->Body());
	}

};


#endif //__DDNOTE__MEMORY_MANAGER__H__INCLUDDED__
