#include "Test.h"
#include <memory>
#include <cstdint>


void CTestor::Test()
{
	uint32_t value_01 = 100;
	std::shared_ptr<uint32_t> sp( &value_01 );
}
