#pragma once

#ifndef __DD_LIBBASE__DD_TYPE_INFO__H__INCLUDDED__
#define __DD_LIBBASE__DD_TYPE_INFO__H__INCLUDDED__

struct DDTypeInfoBsae
{
	// category of type
	enum E_CATEGORY { NONE, SCALAR, OBJECT, FUNCTION, VARIED };
	unsigned int _cat;

	// size of type
	unsigned int _size;

};

struct DDVariedTypeInfo : DDTypeInfoBsae
{
};

// primitive type info
struct DDScalarTypeInfo : DDTypeInfoBsae
{
	// intializer of data
	void(*_fnInitializer)(void* memory);

	// kind of data
	enum E_KIND { BOOL, INT8, UINT8, INT16, UINT16, INT32, UINT32, INT64, UINT64, FLOAT32, FLOAT64, FLOAT128, POINTER };
	unsigned int _kind;
};

// class type info
struct DDClassInfo : DDTypeInfoBsae
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
struct DDFunctionTypeInfo : DDTypeInfoBsae
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

union DDTypeInfo {
	DDTypeInfoBsae base;
	DDScalarTypeInfo scalar;
	DDClassInfo obj;
	DDFunctionTypeInfo fn;
	DDVariedTypeInfo var;
};

#endif //__DD_LIBBASE__DD_TYPE_INFO__H__INCLUDDED__
