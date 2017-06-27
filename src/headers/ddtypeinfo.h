#ifndef __DD_LIBBASE__DD_TYPE_INFO__H__INCLUDDED__
#define __DD_LIBBASE__DD_TYPE_INFO__H__INCLUDDED__
#pragma once


struct DDTypeInfo
{
	// category of type
	enum E_CATEGORY { NONE, SCALAR, OBJECT, ARRAY, FUNCTION };
	unsigned int _cat;

	// size of type
	unsigned int _size;

	// size of type should be allocate
	unsigned int _sizeAlloc;
};

struct DDScalarTypeInfo : DDTypeInfo
{
	// intializer of data
	void(*_fnInitializer)(void* memory);

	// kind of data
	enum E_KIND { BOOL, SBYTE, UBYTE, SSHORT, USHORT, SWORD, UWORD, SDWORD, UDWORD, SQWORD, UQWORD, FLOAT32, FLOAT64, FLOAT80, POINTER };
	unsigned int _kind;
};

struct DDArrayTypeInfo : DDTypeInfo
{
	// intializer of data
	DDTypeInfo *_elementType;

	// length of array
	unsigned int _length;
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
