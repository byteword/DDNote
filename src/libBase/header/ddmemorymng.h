#pragma once

#include <assert.h>
#include <atomic>
#include "ddtypeinfo.h"

#ifndef __DD_LIBBASE__DDMEMORY_MNG__H__INCLUDDED__
#define __DD_LIBBASE__DDMEMORY_MNG__H__INCLUDDED__


#ifndef NULL
#define NULL (0)
#endif // NULL

class DDVarTS;

// class for Memeory management 
class DDMemoryMng
{
public:
	enum E_AllocOption {
		E_AO_LOCAL	= 0x00000001,
		E_AO_THREAD = 0x00000002,
		E_AO_PROCESS = 0x00000003,
		E_AO_SYSTEM = 0x00000007,
		E_AO_KERNEL = 0x0000000F
	};
public:
	static DDVarTS* Alloc(size_t size, unsigned long options = 0);
	void Free(DDVarTS* pvar);
};

#pragma pack(push, 4)
class DDBufferInfo
{
public:
	size_t _allocSizeInByte;
	size_t _alignSize;
	size_t _arrayCount;
	size_t _unitSize;
};

// class for DD Variable Tombstone
class DDVarTS
{
	friend class DDMemoryMng;
private:
	// reference count
	std::atomic<int> _ref;
	
	// type information
	DDTypeInfo* _type;

	// buffer information
	DDBufferInfo* _buff;

	// memory manager for allocation and dealloc
	DDMemoryMng* _mm;

	// for destructor
	typedef void DDDestructor();
	DDDestructor* _destructor;

public:
	DDVarTS();

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

	inline static DDVarTS* Header(void* p)
	{
		return reinterpret_cast<DDVarTS*>(p) - 1;
	}
};

#pragma pack(pop)

// pointer for DDVar
class DDVarPtr
{

private:

	DDVarTS *_header;        // 4 byte

public:

	inline DDVarPtr()
	{
		_header = NULL;
	}

	inline explicit DDVarPtr(DDVarTS* header)
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

	void Set(DDVarTS* header)
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
class DDVPtr_T : public DDVarPtr
{
public:
	inline DDVPtr_T() { }
	inline explicit DDVPtr_T(T* ptr) : DDVarPtr(DDVarTS::Header(ptr)) {}
	inline explicit DDVPtr_T(const DDVPtr_T& ptr) : DDVarPtr(ptr) {}

	template<class V>
	inline explicit DDVPtr_T(const DDVPtr_T<V>& ptr) : DDVarPtr((const DDVarPtr&)ptr)
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
	inline bool operator == (const DDVPtr_T<V>& ptr) const
	{
		return ((const DDVarPtr&)*this) == ((const DDVarPtr&)ptr);
	}

	template<class V>
	inline bool operator != (const DDVPtr_T<V>& ptr) const
	{
		return ((const DDVarPtr&)*this) != ((const DDVarPtr&)ptr);
	}

	template<class V>
	inline bool operator < (const DDVPtr_T<V>& ptr) const
	{
		return ((const DDVarPtr&)*this) < ((const DDVarPtr&)ptr);
	}

	template<class V>
	inline bool operator <= (const DDVPtr_T<V>& ptr) const
	{
		return ((const DDVarPtr&)*this) <= ((const DDVarPtr&)ptr);
	}

	template<class V>
	inline bool operator > (const DDVPtr_T<V>& ptr) const
	{
		return ((const DDVarPtr&)*this) > ((const DDVarPtr&)ptr);
	}


	template<class V>
	inline bool operator >= (const DDVPtr_T<V>& ptr) const
	{
		return ((const DDVarPtr&)*this) >= ((const DDVarPtr&)ptr);
	}

public:

	template<class V>
	inline DDVPtr_T operator = (const DDVPtr_T<T>& ptr)
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
