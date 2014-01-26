#include "cw_tableset.h"
#include "cw_tablebase.h"
SINGLETONG_IMPLEMENTION(CTableSet);

bool CTableSet::Init()
{
	new CLineDataDisposer;
	if (!m_Test.Init("test.tab"))
	{
		return false;
	}	

	if (!TABLE_BASE::smTableGood)
	{
		Assert(false);
		return false;
	}
	return true;
}