#include <iostream>
#include "..\DB\DataBase.h"
#include <Windows.h>
#include <fstream>

int main() {
	User u;
	u.setID("15");
	u.setFirstName("Rex");
	u.setAddress("Unde rroof");
	u.setEmail("Zaka.Zaka@Gmail.com");
	u.setPhoneNumber("123456789012");
	u.setAge(52);

	DateTime d1; // Now
	DateTime d2;
	Transaction t1;
	Transaction t2;

	d2.setHour(14);

	t1.setTransactionID(0);
	t1.setAmout(205);
	t1.setCommission(4.23);
	t1.setPurpose("Internet payment");
	t1.setRecieverBankCID("0");
	t1.setSenderBankCID("15");

	t2.setTransactionID(1);
	t2.setAmout(5);
	t2.setCommission(0);
	t2.setPurpose("Refund");
	t2.setRecieverBankCID("15");
	t2.setSenderBankCID("0");

	u.addTransaction(t1);
	u.addTransaction(t2);

	DataBase db;
	db.loadDB("res/DB");
	db.saveUserTransactions(u);
	try {
		db.loadAllUsers();
		//db.addUser(u); // Already exists
		//db.saveAllUsers();
		for (int i = 0; i < db.usersCount(); i++) {
			std::cout << "User #" << i + 1<< "\n----------------------------------------\n";
			std::cout << db.at(i)->toString();
			if (db.at(i)->getTransactionsCount() != 0) {
				for (int j = 0; j < db.at(i)->getTransactionsCount(); j++) {
					std::cout << "\n\n" << "Transaction N " << j << '\n';
					std::cout << db.at(i)->getTransactions()[j].toString() << "\n\n";
				}
			}
			std::cout << "-----------------------------------------\n\n";
		}
		db.saveAllUsers();
	} catch (const std::exception&e) {
		std::cout << e.what();
	}
	
}