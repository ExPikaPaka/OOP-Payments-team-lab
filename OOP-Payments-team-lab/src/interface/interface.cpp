#include <iostream>
#include "..\DB\DataBase.h"
#include <Windows.h>
#include <fstream>

int main() {
	
	// An example
	User us1;
	User us2;

	us1.setFirstName("Us1");
	us2.setFirstName("Us2");


	DataBase b;
	try {
		b.loadDB("res/DB/usersList.cdb");
	} catch (const std::exception&e) {
		std::cout << e.what();
	}

	std::cout << "Users count: " << b.users.size() << '\n';
	User us;
	b.getUserWithID("2")->setBankCID("2323");
	try {
		us = b.getUserWithID("2");

	} catch (const std::exception&e) {
		std::cout << e.what() << '\n';
	}

	std::cout << us.toString();
}