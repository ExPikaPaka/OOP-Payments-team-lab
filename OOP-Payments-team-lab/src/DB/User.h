#pragma once
#include <string>
#include <vector>
#include "Transaction.h"

class User {
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
	int transactionsCount;
	User();
	User(const User& other);
	~User();

	std::string getID() const;
	std::string getBankCID() const;
	std::string getFirstName() const;
	std::string getSecondName() const;
	int getAge() const;
	std::string getGender() const;
	std::string getPhoneNumber() const;
	std::string getEmail() const;
	std::string getAddress() const;
	Transaction getTransaction(int transaction_id) const;
	Transaction getLastTransaction() const;
	std::vector<Transaction> getTransactions() const;

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

	User& operator=(User& other);
	User& operator=(User* other);

	std::string toString();
};

