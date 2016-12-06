
#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>

#include "ipc_viewer.h"

using namespace boost::interprocess;

std::map<std::uint32_t, std::uint32_t> readHighScore(bool block)
{
	std::cout << "read " << block << std::endl;

	return {};
}
