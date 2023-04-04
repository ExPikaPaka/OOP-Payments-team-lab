#pragma once
#include "User.h"
#include <vector>

class DataBase {
protected:
	std::string path;
	std::string usersListPath;
	std::string userTransacPath;
	std::vector<User> users;

	int fieldsCount;
	char delimiter;

	std::vector<std::vector<std::string>> getUsersListString();
	void saveUsersListString(std::vector<std::vector<std::string>> usersData);

public:
	void loadUserTransactions(User& user);
	void saveUserTransactions(User& user);
	DataBase();
	DataBase(std::string path, std::string usersListPath = "usersList.cdb", std::string userTransacPath = "users_transactions");

	// Loads DB, but not users
	void loadDB(std::string path, std::string usersListPath = "usersList.cdb", std::string userTransacPath = "users_transactions");

	// Overrides current DB state into file
	void saveDB(std::string path, std::string usersListPath = "usersList.cdb", std::string userTransacPath = "users_transactions");

	// Loads user with specified ID. 
	// Returns 1 if succeed.
	// Returns 0 if failed.
	bool loadUser(std::string ID);
	void saveUser(std::string ID);
	void loadAllUsers();
	void saveAllUsers();

	void clearUserList();

	void addUser(User user);
	void delUser(std::string ID);
	void delDB();
	// returns firs finded user with specified ID
	// in case user not found returns empty User
	User* getUserWithID(std::string ID);
	User* at(int index);
	int usersCount();
};

