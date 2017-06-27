#ifndef __DDNOTE__DDMEMORY_MNG__H__INCLUDDED__
#define __DDNOTE__DDMEMORY_MNG__H__INCLUDDED__
#pragma once

#ifndef NULL
#define NULL (0)
#endif // NULL

#pragma pack(push, 4)

struct DDTypeInfo;
class DDVarHeader;

class DDMemoryMng
{
public:
	void Free(DDVarHeader* var);
};

class DDVarHeader
{
private:
	// reference count
	unsigned int _ref;
	
	// type information
	DDTypeInfo* _type;

	// memory manager for allocation and dealloc
	DDMemoryMng* _mm;

	// for destructor
	typedef void DDDestructor();
	DDDestructor* _destructor;
	
public:
	inline void AddRef() { _ref++; }
	inline void Release() {
		_ref--;
		if (_ref == NULL)
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

class DDScalarHeader : public DDVarHeader
{
private:
};


#endif //__DDNOTE__DDMEMORY_MNG__H__INCLUDDED__
