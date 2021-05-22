#include <stdio.h>
#include "Board.h"

#include "Application.h"

int main(int argc, char **argv)
{
	CBoard::Init();
	CApplication application;
	application.Start();
	cpp_freertos::Thread::StartScheduler();
	return 0;
}
