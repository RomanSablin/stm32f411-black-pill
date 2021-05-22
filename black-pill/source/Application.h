#pragma once

#include <thread.hpp>
#include <queue.hpp>

class CApplication  : public cpp_freertos::Thread
{
public:
	CApplication();

protected:
	void Run() override;

};

