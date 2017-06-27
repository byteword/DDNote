#pragma once

#ifndef __DD_LIBBASE__DD_TYPE_INFO__H__INCLUDDED__
#define __DD_LIBBASE__DD_TYPE_INFO__H__INCLUDDED__

struct DDTypeInfo
{
	// category of type
	enum E_CATEGORY { NONE, SCALAR, OBJECT, FUNCTION, BUFFER };
	unsigned int _cat;

	// size of type
	unsigned int _size;

	// size of type should be allocate
	unsigned int _sizeAlloc;
};

// primitive type info
struct DDScalarTypeInfo : DDTypeInfo
{
	// intializer of data
	void(*_fnInitializer)(void* memory);

	// kind of data
	enum E_KIND { BOOL, INT8, UINT8, INT16, UINT16, INT32, UINT32, INT64, UINT64, FLOAT32, FLOAT64, FLOAT128, POINTER };
	unsigned int _kind;
};

// buffer type info
struct DDBufferInfo : DDTypeInfo
{
	// align of index
	unsigned int _align;
};

// class type info
struct DDClassInfo : DDTypeInfo
{
	// size of information structure
	unsigned int _size;

	// size of object
	unsigned int _sizeObject;

	// name of class
	unsigned int _name_len;

	// heirachy information
	unsigned int _parent_cnt;
};

// function type info
struct DDFunctionTypeInfo : DDTypeInfo
{
	// size of struct
	unsigned int _size;

	// pointer to name of virtual function
	// should statically allocated in memory
	unsigned int _name_len;

	// entry point of function
	void* _entry;

	// calling conversion
	// enum CALL_CONVERSION { CDECL, SYSCALL, OPTLINK, PASCAL, STDCALL, MS_FASTCALL, MS_VECTORCALL, SAFECALL, THISCALL, X64CALL};
	enum CALL_CONVERSION {
		CDECL, THISCALL, PASCAL
	};
	unsigned int _call_conversion;

	// information for arguments
	unsigned int _argc;
};

#endif //__DD_LIBBASE__DD_TYPE_INFO__H__INCLUDDED__
