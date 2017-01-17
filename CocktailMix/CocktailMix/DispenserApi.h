#pragma once
#include <winsock.h>

enum DispenserStatus : char {
	Off = '0',
	On = '1'
};

class DispenserApi
{
public:
	static bool Startup();
	static bool Cleanup();
	static bool GetDispenser(unsigned int, DispenserStatus&);
	static bool SetDispenser(unsigned int, DispenserStatus);
	static bool SetAllDispensers(DispenserStatus);
private:
	virtual void makeClassPureVirtual() = 0;
	static unsigned int csocket;
	static bool init;
	static WSADATA wsadata;
};