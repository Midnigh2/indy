#pragma comment(lib, "ws2_32")

#include <iostream>
#include <stdio.h>
#include <iostream>

#include "IndyDCPConnector.h"

using namespace std; // cin, cout 사용
using namespace NRMKIndy::Service::DCP;
IndyDCPConnector connector("192.168.215.123", ROBOT_INDY7); // right Indy7

void WaitFinish(IndyDCPConnector& connector) {
	bool fin = false;
	do {
		Sleep(500);
		connector.isMoveFinished(fin);
	} while (!fin);
}

int main(int argc, char **argv)
{
	initWinSock();

	cout << "Connecting to the right Indy7" << endl;
	connector.connect();

	bool ready;
	connector.isRobotReady(ready); // 로봇이 작동가능한 상태인지 확인

	if (ready)
	{
		cout << "Robot is Ready" << endl;

		double i[6];
		cout << "Current joint values" << endl;
		connector.getJointPosition(i);
		for (int j = 0; j < 6; j++) { cout << i[j] << ","; }
		cout << endl;


		cout << "smartDO_8 LOW" << endl;
		connector.setSmartDigitalOutput(8, 0);

		cout << "smartDO_8 HIGH" << endl;
		connector.setSmartDigitalOutput(8, 1);

		char ret[32];
		cout << "smartDI info" << endl;
		connector.getSmartDigitalInputs(ret); // >>>> 여기서 이미 메모리주소에는 값이 다 들어와있음
		
		for (int a = 0; a < 32; a++) {

			cout << static_cast<int>(ret[a]) << ",";

		}
		cout << endl;
		
		
		cout << "Disconnecting" << endl;
		connector.disconnect();
	}
}