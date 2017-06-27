#include <assert.h>
#include "../incl/memorymng.h"

DDVarPtr DDVarPtr::NULLPtr;

DDVarHeader::DDVarHeader()
{
}

void DDMemoryMng::Free(DDVarHeader* pvar)
{
	// TODO: Implement
	assert(pvar != NULL);
	assert(pvar->_ref == 0);
}