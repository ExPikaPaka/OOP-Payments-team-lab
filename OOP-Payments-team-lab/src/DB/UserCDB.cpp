#include "UserCDB.h"
#include <stdexcept>
#include <regex>

bool UserCDB::isEmailValid(std::string email) {
	std::regex pattern("(\\w+)(\\.\\w+)*@(\\w+)(\\.(\\w+))+");
	
	if (std::regex_match(email, pattern)) {
		return true;
	}
	return false;
}

UserCDB::UserCDB() {
	this->bank_CID = "null";
	this->first_name = "null";
	this->second_name = "null";
	this->age = -1;
	this->gender = "null";
	this->phone_number = "null";
	this->email = "null";
}

UserCDB::~UserCDB() {

}

std::string UserCDB::getID() {
	return ID;
}

std::string UserCDB::getBankCID() {
	return bank_CID;
}

std::string UserCDB::getFirstName() {
	return first_name;
}

std::string UserCDB::getSecondName() {
	return second_name;
}

int UserCDB::getAge() {
	return age;
}

std::string UserCDB::getGender() {
	return gender;
}

std::string UserCDB::getPhoneNumber() {
	return phone_number;
}

std::string UserCDB::getEmail() {
	return email;
}

std::string UserCDB::getAddress() {
	return address;
}

Transaction UserCDB::getTransaction(int transaction_id) {
	if (transaction_id > -1 && transaction_id < transactions.size()) {
		return transactions[transaction_id];
	}
	throw std::invalid_argument("Transaction_ID out of range");
}



void UserCDB::addTransaction(Transaction transaction) {
	transactions.push_back(transaction);
}

void UserCDB::setID(std::string ID) {
	if (!ID.empty()) {
		this->ID = ID;
	}
	else {
		throw std::invalid_argument("ID cannot be empty.");
	}
}

void UserCDB::setBankCID(std::string bank_CID) {
	if (!bank_CID.empty()) {
		this->bank_CID = bank_CID;
	} else {
		throw std::invalid_argument("Bank card ID cannot be empty.");
	}
}

void UserCDB::setFirstName(std::string first_name) {
	if (!first_name.empty()) {
		this->first_name = first_name;
	} else {
		throw std::invalid_argument("First name cannot be empty.");
	}
}

void UserCDB::setSecondName(std::string second_name) {
	if (!second_name.empty()) {
		this->second_name = second_name;
	} else {
		throw std::invalid_argument("ID cannot be empty.");
	}
}

void UserCDB::setAge(int age) {
	if (age > -1) {
		this->age = age;
	} else {
		throw std::invalid_argument("Age cannot be negative.");
	}
}

void UserCDB::setGender(std::string gender) {
	if (!gender.empty()) {
		this->gender = gender;
	} else {
		throw std::invalid_argument("Gender cannot be empty.");
	}
}

void UserCDB::setPhoneNumber(std::string phone_number) {
	if (phone_number.size() != 12) {
		this->phone_number = phone_number;
	} else {																
		throw std::invalid_argument("Phone number must contain 12 digits. Ex: 380123456789.");
	}
}

void UserCDB::setEmail(std::string email) {
	if (!email.empty()) {
		if (isEmailValid(email)) {
			this->email = email;
		} else {
			throw std::invalid_argument("Invalid email. Acceptabile is like \"email.example@smail.com.ua\"");
		}
	} else {
		throw std::invalid_argument("Email cannot be empty.");
	}
}

void UserCDB::setAddress(std::string address) {
	if (!address.empty()) {
		this->address = address;
	} else {
		throw std::invalid_argument("Address cannot be empty.");
	}
}
