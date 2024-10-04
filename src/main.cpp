#include <iostream>

#include "netagent/netagent.h"
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib

int main(int argc, char *argv[]) {
	NetServer server;
	std::cout << "Waiting for clients\n";

	FastCont<int> clientIDs;

	while (true) {
		for (int i = 0; i < clientIDs.size; ++i) {
			int id = *clientIDs.at_index(i);

			int res = server.recieveData(id);
			if (res != recieveData_NO_NEW_DATA) {
				if (res == recieveData_CONN_CLOSED_BY_CLIENT_ERR) {
					std::cout << "Connection closed by client!\n";
					clientIDs.remove_index(i);
					i--;
					continue;
				}
				if (res == recieveData_NO_CLIENT_ERR) {
					std::cout << "No client with this id!\n";
					clientIDs.remove_index(i);
					i--;
					continue;
				}
				if (res == recieveData_ERR) {
					std::cout << "server.recieveData() general error!\n";
					continue;
				}

				std::cout << id << " (" << server.getLastData(id)->len
					<< "B): " << server.getLastData(id)->data << std::endl;

				for (int j = 0; j < clientIDs.size; ++j) {
					if (i != j)
						server.sendData(*clientIDs.at_index(j),
							server.getLastData(id)->data,
							server.getLastData(id)->len);
				}
			}
		}

		int tmpId = server.acceptNewClient();
		if (tmpId >= 0) {
			std::cout << "New client with ID" << tmpId << std::endl;
			clientIDs.push_back(tmpId);
		}
		Sleep(100);
	}

	return 0;
}