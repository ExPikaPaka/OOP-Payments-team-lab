#include "User.h"
#include <stdexcept>
#include <regex>
#include <sstream>
#include <string>

bool User::isEmailValid(std::string email) {
	std::regex pattern("(\\w+)(\\.\\w+)*@(\\w+)(\\.(\\w+))+");
	
	if (std::regex_match(email, pattern)) {
		return true;
	}
	return false;
}

User::User() {
	this->ID = "null";
	this->bank_CID = "null";
	this->first_name = "null";
	this->second_name = "null";
	this->age = -1;
	this->gender = "null";
	this->phone_number = "null";
	this->email = "null";
	this->address = "null";
	transactions = {};
}

User::User(const User& other) : User() {
	ID = other.getID();
	bank_CID = other.bank_CID;
	first_name = other.first_name;
	second_name = other.second_name;
	age = other.age;
	gender = other.gender;
	phone_number = other.phone_number;
	email = other.email;
	address = other.address;
	transactions = other.transactions;
}

User::User(const User* other) : User() {
	if (other != 0) {
		ID = other->getID();
		bank_CID = other->bank_CID;
		first_name = other->first_name;
		second_name = other->second_name;
		age = other->age;
		gender = other->gender;
		phone_number = other->phone_number;
		email = other->email;
		address = other->address;
		transactions = other->transactions;
	}
}

User::~User() {

}

std::string User::getID() const {
	return ID;
}

std::string User::getBankCID() const {
	return bank_CID;
}

std::string User::getFirstName() const {
	return first_name;
}

std::string User::getSecondName() const {
	return second_name;
}

int User::getAge() const {
	return age;
}

std::string User::getGender() const {
	return gender;
}

std::string User::getPhoneNumber() const {
	return phone_number;
}

std::string User::getEmail() const {
	return email;
}

std::string User::getAddress() const {
	return address;
}

Transaction User::getTransaction(int transaction_id) const {
	if (transaction_id > -1 && transaction_id < transactions.size()) {
		return transactions[transaction_id];
	}
	throw std::out_of_range("Transaction_ID out of range");
}

Transaction User::getLastTransaction() const {
	if (transactions.size() != 0) {
		return transactions[transactions.size()];
	}
	throw std::out_of_range("User has 0 transactions!");
}

int User::getTransactionsCount() const {
	return transactions.size();
}

std::vector<Transaction> User::getTransactions() const {
	return transactions;
}


void User::addTransaction(Transaction transaction) {
	transactions.push_back(transaction);
}

void User::setID(std::string ID) {
	if (!ID.empty()) {
		this->ID = ID;
	}
	else {
		throw std::invalid_argument("ID cannot be empty.");
	}
}

void User::setBankCID(std::string bank_CID) {
	if (!bank_CID.empty()) {
		this->bank_CID = bank_CID;
	} else {
		throw std::invalid_argument("Bank card ID cannot be empty.");
	}
}

void User::setFirstName(std::string first_name) {
	if (!first_name.empty()) {
		this->first_name = first_name;
	} else {
		throw std::invalid_argument("First name cannot be empty.");
	}
}

void User::setSecondName(std::string second_name) {
	if (!second_name.empty()) {
		this->second_name = second_name;
	} else {
		throw std::invalid_argument("ID cannot be empty.");
	}
}

void User::setAge(int age) {
	if (age > -1) {
		this->age = age;
	} else {
		throw std::invalid_argument("Age cannot be negative.");
	}
}

void User::setGender(std::string gender) {
	if (!gender.empty()) {
		this->gender = gender;
	} else {
		throw std::invalid_argument("Gender cannot be empty.");
	}
}

void User::setPhoneNumber(std::string phone_number) {
	if (phone_number.size() == 12) {
		this->phone_number = phone_number;
	} else {																
		throw std::invalid_argument("Phone number must contain 12 digits. Ex: 380123456789, but given " + phone_number);
	}
}

void User::setEmail(std::string email) {
	if (!email.empty()) {
		if (isEmailValid(email)) {
			this->email = email;
		} else {
			throw std::invalid_argument("Invalid email. Acceptabile is like \"email.example@smail.com.ua\", but given " + email);
		}
	} else {
		throw std::invalid_argument("Email cannot be empty.");
	}
}

void User::setAddress(std::string address) {
	if (!address.empty()) {
		this->address = address;
	} else {
		throw std::invalid_argument("Address cannot be empty.");
	}
}

User& User::operator=(User& other) {
	if (this == &other) {
		return *this;
	}

	ID = other.getID();
	bank_CID = other.getBankCID();
	first_name = other.getFirstName();
	second_name = other.getSecondName();
	age = other.getAge();
	gender = other.getGender();
	phone_number = other.getPhoneNumber();
	email = other.getEmail();
	address = other.getAddress();
	transactions = other.getTransactions();

	return *this;
}

User& User::operator=(User* other) {
	if (other == nullptr) {
		throw std::invalid_argument("Null pointer passed to User::operator=()");
	}

	if (this == other) {
		return *this;
	}

	ID = other->getID();
	bank_CID = other->getBankCID();
	first_name = other->getFirstName();
	second_name = other->getSecondName();
	age = other->getAge();
	gender = other->getGender();
	phone_number = other->getPhoneNumber();
	email = other->getEmail();
	address = other->getAddress();
	transactions = other->getTransactions();

	return *this;
}

void User::null() {
	this->ID = "null";
	this->bank_CID = "null";
	this->first_name = "null";
	this->second_name = "null";
	this->age = -1;
	this->gender = "null";
	this->phone_number = "null";
	this->email = "null";
	this->address = "null";
	transactions = {};
}

std::string User::toString() {
	std::stringstream ss;
	ss << "User ID      : " + ID << "\n";
	ss << "Bank CID     : " + bank_CID << "\n";
	ss << "First name   : " + first_name << "\n";
	ss << "Second name  : " + second_name << "\n";
	ss << "Age          : " + std::to_string(age) << "\n";
	ss << "Gender       : " + gender << "\n";
	ss << "Phone number : " + phone_number << "\n";
	ss << "Email        : " + email << "\n";
	ss << "Address      : " + address << "\n";
	ss << "Transactions : " + std::to_string(transactions.size()) << "\n";

	std::string userInfo = ss.str();

	return userInfo;
}
