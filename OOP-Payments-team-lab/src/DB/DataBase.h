#pragma once
#include "User.h"
#include <vector>

class DataBase {
protected:
public:
	DataBase();
	std::vector<User> users;
	void loadDB(std::string filePath);
	void saveDB(std::string filePath);

	// returns firs finded user with specified ID
	// in case user not found returns empty User
	User* getUserWithID(std::string ID);
};

