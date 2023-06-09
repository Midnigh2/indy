﻿#pragma comment(lib, "ws2_32")

#include <iostream>
#include <stdio.h>
#include <iostream>

#include "IndyDCPConnector.h"

using namespace std; // cin, cout 사용
using namespace NRMKIndy::Service::DCP;
IndyDCPConnector connector_R("192.168.215.123", ROBOT_INDY7); // right Indy7
IndyDCPConnector connector_L("192.168.215.124", ROBOT_INDY7); // left Indy7

void WaitFinish_R(IndyDCPConnector& connector_R) {
	bool fin = false;
	do {
		Sleep(500);
		connector_R.isMoveFinished(fin);
	} while (!fin);
}

void WaitFinish_L(IndyDCPConnector& connector_L) {
	bool fin = false;
	do {
		Sleep(500);
		connector_L.isMoveFinished(fin);
	} while (!fin);
}
void DigitalIO_L(IndyDCPConnector& connector_L) {
	cout << "smartDO_L_8 LOW" << endl;
	connector_L.setSmartDigitalOutput(8, 0);

	cout << "smartDO_L_8 HIGH" << endl;
	connector_L.setSmartDigitalOutput(8, 1);
}

void DigitalIO_R(IndyDCPConnector& connector_R) {
	cout << "smartDO_R_8 LOW" << endl;
	connector_R.setSmartDigitalOutput(8, 0);

	cout << "smartDO_R_8 HIGH" << endl;
	connector_R.setSmartDigitalOutput(8, 1);
}

int main(int argc, char **argv)
{
	initWinSock();

	cout << "Connecting to the Indy7" << endl;
	connector_R.connect();
	connector_L.connect();

	bool ready_R;
	bool ready_L;
	connector_R.isRobotReady(ready_R); // 로봇이 작동가능한 상태인지 확인
	connector_L.isRobotReady(ready_L);

	if (ready_R && ready_L)
	{
		cout << "Robot is Ready" << endl;

		DigitalIO_L(connector_L);
		
		cout << "Disconnecting" << endl;
		connector_L.disconnect();
		connector_R.disconnect();
	}
}

