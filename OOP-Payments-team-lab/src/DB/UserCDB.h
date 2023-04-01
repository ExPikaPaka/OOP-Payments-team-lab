#pragma once
#include <string>
#include <vector>
#include "Transaction.h"

class UserCDB {
protected:
	std::string ID;
	std::string bank_CID;
	std::string	first_name;
	std::string second_name;
	int age;
	std::string gender;
	std::string phone_number;
	std::string email;
	std::string address;
	std::vector<Transaction> transactions;


	bool isEmailValid(std::string email);
public:
	UserCDB();
	~UserCDB();

	std::string getID();
	std::string getBankCID();
	std::string getFirstName();
	std::string getSecondName();
	int getAge();
	std::string getGender();
	std::string getPhoneNumber();
	std::string getEmail();
	std::string getAddress();
	Transaction getTransaction(int transaction_id);

	void addTransaction(Transaction transaction);
	void setID(std::string ID);
	void setBankCID(std::string bank_CID);
	void setFirstName(std::string first_name);
	void setSecondName(std::string second_name);
	void setAge(int age);
	void setGender(std::string gender);
	void setPhoneNumber(std::string phone_number);
	void setEmail(std::string email);
	void setAddress(std::string address);
};

