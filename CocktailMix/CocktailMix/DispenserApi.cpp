#include "stdafx.h"

#include "DispenserApi.h"
#include <sys/types.h>
#include <sstream>


#define PORT 55655
#define DEST "192.168.1.1" // Raspberry IP

bool DispenserApi::Startup() {
	if (init) return true;

	if (WSAStartup(0x0202, &wsadata) < 0) return false;
	if (wsadata.wVersion != 0x0202) return false;

	char* target = DEST;
	struct sockaddr_in caddr;
	memset(&caddr, 0, sizeof(caddr));
	caddr.sin_family = AF_INET;
	caddr.sin_port = htons(PORT);
	caddr.sin_addr.s_addr = inet_addr(target);
	csocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (csocket < 0) {
		WSACleanup();
		return false;
	}
	if (connect(csocket, (struct sockaddr *) &caddr, sizeof(caddr)) < 0) {
		WSACleanup();
		return false;
	}
	init = true;
	return true;
}
bool DispenserApi::Cleanup() {
	if (!init) return true;
	closesocket(csocket);
	WSACleanup();
	return true;
}
bool DispenserApi::SetDispenser(unsigned int number, DispenserStatus status) {
	if (!init || number > 5) return false;
	std::stringstream ss;
	ss << "set " << (char)('0' + number) << " " << (char)status;
	char buffer[8];
	memset(buffer, 0, sizeof(buffer));
	strcpy_s(buffer, ss.str().c_str());
	int sent = send(csocket, buffer, sizeof(buffer), 0);
	if (sent != sizeof(buffer)) return false;
	memset(buffer, 0, sizeof(buffer));
	recv(csocket, buffer, 1, 0);
	return buffer[0] == (char)status;
}
bool DispenserApi::SetAllDispensers(DispenserStatus status) {
	if (!init) return false;
	std::stringstream ss;
	ss << "set * " << (char)status;
	char buffer[8];
	memset(buffer, 0, sizeof(buffer));
	strcpy_s(buffer, ss.str().c_str());
	int sent = send(csocket, buffer, sizeof(buffer), 0);
	if (sent != sizeof(buffer)) return false;
	memset(buffer, 0, sizeof(buffer));
	recv(csocket, buffer, 1, 0);
	return buffer[0] == (char)status;
}

bool DispenserApi::GetDispenser(unsigned int number, DispenserStatus& status) {
	if (!init || number > 5) return false;
	std::stringstream ss;
	ss << "get " << (char)('0' + number) << " x";
	char buffer[8];
	memset(buffer, 0, sizeof(buffer));
	strcpy_s(buffer, ss.str().c_str());
	int sent = send(csocket, buffer, sizeof(buffer), 0);
	if (sent != sizeof(buffer)) return false;
	memset(buffer, 0, sizeof(buffer));
	recv(csocket, buffer, 1, 0);
	
	if (buffer[0] == DispenserStatus::Off || buffer[0] == DispenserStatus::On) {
		status = (DispenserStatus)buffer[0];
		return true;
	}
	return false;
}

unsigned int DispenserApi::csocket = 0;
bool DispenserApi::init = false;
WSADATA DispenserApi::wsadata;