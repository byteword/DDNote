#pragma once

#include <assert.h>
#include <atomic>
#include "ddtypeinfo.h"

#ifndef __DD_LIBBASE__DDMEMORY_MNG__H__INCLUDDED__
#define __DD_LIBBASE__DDMEMORY_MNG__H__INCLUDDED__


#ifndef NULL
#define NULL (0)
#endif // NULL

class DDVarHeader;

// class for Memeory management 
class DDMemoryMng
{
public:
	void Free(DDVarHeader* pvar);
};

#pragma pack(push, 4)
// class for DDVar header
class DDVarHeader
{
	friend class DDMemoryMng;
private:
	// reference count
	std::atomic<int> _ref;
	
	// type information
	DDTypeInfo* _type;

	// memory manager for allocation and dealloc
	DDMemoryMng* _mm;

	// for destructor
	typedef void DDDestructor();
	DDDestructor* _destructor;

public:
	DDVarHeader();

	inline void AddRef() { 
		_ref++;
	}
	inline void Release() {
		assert(_ref > 0);

		if ( --_ref == 0 )
		{
			this->_destructor();
			_mm->Free(this);
		}
	}

public:
	inline void* Body()
	{
		return reinterpret_cast<void*>(this + 1 );
	}

	inline static DDVarHeader* Header(void* p)
	{
		return reinterpret_cast<DDVarHeader*>(p) - 1;
	}
};

#pragma pack(pop)

// pointer for DDVar
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


// generic pointer template for DDVar
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


#endif //__DD_LIBBASE__DDMEMORY_MNG__H__INCLUDDED__
