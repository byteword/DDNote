#include <assert.h>
#include "../incl/memorymng.h"

DDVarPtr DDVarPtr::NULLPtr;

DDVarTS::DDVarTS()
{
}


void* DDMemoryMng::Alloc(size_t size, unsigned long options)
{
	if (options == 0)
	{
		// automatic or default
	}
}

void DDMemoryMng::Free(DDVarTS* pvar)
{
	// TODO: Implement
	assert(pvar != NULL);
	assert(pvar->_ref == 0);
}