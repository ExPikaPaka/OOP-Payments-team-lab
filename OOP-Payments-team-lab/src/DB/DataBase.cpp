#include "DataBase.h"
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <filesystem>


std::vector<std::vector<std::string>> DataBase::getUsersListString() {
	std::fstream fs(path + "/" + usersListPath, std::ios::in);

	if (!fs.is_open()) {
		throw std::ios_base::failure("Could not ope file \"" + path + "/" + usersListPath + 
			"\" at std::vector<std::vector<std::string>> DataBase::getUsersListString()");
	}

	// Reading single line (to the '\n')
	std::string line;
	int prevLineEndPos = 0;
	int lineIterator = 0;

	// Loading entire DB
	std::vector <std::vector<std::string>> usersData;
	while (std::getline(fs, line)) {

		// Creating a string stream to parse variables
		std::stringstream ss(line);
		std::string buffer;
		std::vector<std::string> fields;

		while (std::getline(ss, buffer, delimiter)) {
			fields.push_back(buffer);
		}
		if (fields.size() != fieldsCount) {
			throw std::logic_error(".cdb file isn`t formatted correctly! Check line " + std::to_string(lineIterator));
		}

		usersData.push_back(fields);

		fields.clear();
		lineIterator++;
	}
	fs.close();

	return usersData;
}

void DataBase::saveUsersListString(std::vector<std::vector<std::string>> usersData) {
	std::fstream fs(path + "/" + usersListPath, std::ios::out);

	if (!fs.is_open()) {
		throw std::ios_base::failure("Could not ope file \"" + path + "/" + usersListPath + 
			"\" at void DataBase::saveUsersListString(std::vector<std::vector<std::string>> usersData)");
	}

	for (int i = 0; i < usersData.size(); i++) {
		for (int j = 0; j < fieldsCount; j++) {
			fs << usersData[i][j];
			if (j != fieldsCount - 1) {
				fs << delimiter;
			}
		}
		fs << '\n';
	}
	fs.close();
}

void DataBase::loadUserTransactions(User& user) {
	std::string temp = path + "/" + userTransacPath + "/" + user.getID();
	std::wstring dirPath(temp.begin(), temp.end());

	// Get transactions count:
	std::filesystem::directory_iterator dirIter;
	try {
		dirIter = std::filesystem::directory_iterator(dirPath);
	} catch (std::filesystem::filesystem_error& e) {
		return;
	}

	int fileCount = 0;

	for (auto& entry : dirIter) {
		if (entry.is_regular_file()) {
			++fileCount;
		}
	}


	std::ifstream fs;

	Transaction current;

	// If folder exists
	if (!CreateDirectory(dirPath.c_str(), 0)) {
		for (int i = 0; i < fileCount; i++) {
			fs.open(path + "/" + userTransacPath + "/" + user.getID() + "/" + std::to_string(i) + ".cut");

			// Check if file exists
			if (fs.is_open()) {

				// Parsing fields
				std::string line;
				std::getline(fs, line);

				std::stringstream ss(line);
				std::string buffer;
				std::vector<std::string> fields;

				while (std::getline(ss, buffer, delimiter)) {
					fields.push_back(buffer);
				}
				if (fields.size() != 12) {
					throw std::logic_error(".cut file isn`t formatted correctly! Check user transaction " + 
						path + "/" + userTransacPath + "/" + user.getID() + "/" + std::to_string(i) + ".cut");
				}

				current.setTransactionID(std::stoi(fields[0]));
				current.setSenderBankCID(fields[1]);
				current.setRecieverBankCID(fields[2]);
				current.setAmout(std::stof(fields[3]));
				current.setCommission(std::stof(fields[4]));
				current.setPurpose(fields[5]);
				current.transactionTime().setHour(std::stoi(fields[6]));
				current.transactionTime().setMin(std::stoi(fields[7]));
				current.transactionTime().setSec(std::stoi(fields[8]));
				current.transactionTime().setMDay(std::stoi(fields[9]));
				current.transactionTime().setMon(std::stoi(fields[10]));
				current.transactionTime().setYear(std::stoi(fields[11]));
				user.addTransaction(current);
				fs.close();
			}
		}
	}
}

void DataBase::saveUserTransactions(User& user) {
	std::string temp = path + "/" + userTransacPath + "/" + user.getID();
	std::wstring dirPath(temp.begin(), temp.end());
	CreateDirectory(dirPath.c_str(), 0);

	std::ofstream fs;

	std::vector<Transaction> userTransactions = user.getTransactions();
	for (int i = 0; i < userTransactions.size(); i++) {
		fs.open(path + "/" + userTransacPath + "/" + user.getID() + "/" + std::to_string(i) + ".cut");
	
		if (!fs.is_open()) {
			throw std::ios_base::failure("Could not open file \"" + path + "/" + userTransacPath + "/" + user.getID() + "/" + std::to_string(i) + ".cut" + "\"");
		}
		
		fs << userTransactions[i].getTransactionID() << delimiter;
		fs << userTransactions[i].getSenderBankCID() << delimiter;
		fs << userTransactions[i].getRecieverBankCID() << delimiter;
		fs << userTransactions[i].getAmout() << delimiter;
		fs << userTransactions[i].getCommission() << delimiter;
		fs << userTransactions[i].getPurpose() << delimiter;
		fs << userTransactions[i].transactionTime().getTime().tm_hour << delimiter;
		fs << userTransactions[i].transactionTime().getTime().tm_min << delimiter;
		fs << userTransactions[i].transactionTime().getTime().tm_sec << delimiter;
		fs << userTransactions[i].transactionTime().getTime().tm_mday << delimiter;
		fs << userTransactions[i].transactionTime().getTime().tm_mon << delimiter;
		fs << userTransactions[i].transactionTime().getTime().tm_year << '\n';
		
		fs.close();
	}
	
}

DataBase::DataBase() {
	usersListPath = "usersList.cdb";
	userTransacPath = "users_transactions";
	fieldsCount = 11;
	delimiter = '}';
	dbIsOpen = false;
}

DataBase::DataBase(std::string path, std::string usersListPath, std::string userTransacPath) {
	this->path = path;
	this->usersListPath = usersListPath;
	this->userTransacPath = userTransacPath;
	dbIsOpen = false;
	loadDB(path, usersListPath, userTransacPath);
	fieldsCount = 11;
	delimiter = '}';
}

void DataBase::loadDB(std::string path, std::string usersListPath, std::string userTransacPath) {
	if (path.empty()) {
		throw std::invalid_argument("File path is empty!");
	}
	if (usersListPath.empty()) {
		throw std::invalid_argument("UsersListPath path is empty!");
	}
	if (userTransacPath.empty()) {
		throw std::invalid_argument("UserTransacPath path is empty!");
	}
	std::ifstream fs(path + "/" + usersListPath);

	if (!fs.is_open()) {
		throw std::ios_base::failure("Could not open file \"" + path + "/" + usersListPath + "\"");
	}
	this->path = path;
	this->usersListPath = usersListPath;
	this->userTransacPath = userTransacPath;
	dbIsOpen = true;
	fs.close();
}

void DataBase::saveDB(std::string path, std::string usersListPath, std::string userTransacPath) {
	if (path.empty()) {
		throw std::invalid_argument("File path is empty!");
	}
	if (usersListPath.empty()) {
		throw std::invalid_argument("UsersListPath path is empty!");
	}
	if (userTransacPath.empty()) {
		throw std::invalid_argument("UserTransacPath path is empty!");
	}
	std::ofstream fs(path + "/" + usersListPath);

	if (!fs.is_open()) {
		throw std::ios_base::failure("Could not open file \"" + path + "/" + usersListPath + "\"");
	}

	for (int i = 0; i < users.size(); i++) {
		fs << users[i].getID() << delimiter;
		fs << users[i].getBankCID() << delimiter;
		fs << users[i].getFirstName() << delimiter;
		fs << users[i].getSecondName() << delimiter;
		fs << users[i].getAge() << delimiter;
		fs << users[i].getGender() << delimiter;
		fs << users[i].getPhoneNumber() << delimiter;
		fs << users[i].getEmail() << delimiter;
		fs << users[i].getAddress() << "\n";
	}
	fs.close();
}

bool DataBase::isOpen() {
	return dbIsOpen;
}

void DataBase::loadAllUsers() {
	loadUser("-any");
}

void DataBase::saveAllUsers() {
	for (int i = 0; i < users.size(); i++) {
		saveUser(users[i].getID());
		saveUserTransactions(users[i]);
	}
}

void DataBase::clearUserList() {
	users.clear();
}

bool DataBase::loadUser(std::string ID) {
	std::ifstream fs(path + "/" + usersListPath);

	if (!fs.is_open()) {
		throw std::ios_base::failure("Could not open file \"" + path + "/" + usersListPath + "\"");
	}
	User current;
	int preLoadUsersCount = users.size();

	// Reading single line (to the '\n')
	std::string line;
	int lineIterator = 0;

	while (std::getline(fs, line)) {

		// Creating a string stream to parse variables
		std::stringstream ss(line);
		std::string buffer;
		std::vector<std::string> fields;

		while (std::getline(ss, buffer, delimiter)) {
			fields.push_back(buffer);
		}
		if (fields.size() != fieldsCount) {
			throw std::logic_error(".cdb file isn`t formatted correctly! Check line " + std::to_string(lineIterator));
		}

		if (lineIterator) {
			current.setID(fields[0]);
			current.setBankCID(fields[1]);
			current.setFirstName(fields[2]);
			current.setSecondName(fields[3]);
			current.setAge(std::stoi(fields[4]));
			current.setGender(fields[5]);
			current.setPhoneNumber(fields[6]);
			current.setEmail(fields[7]);
			current.setAddress(fields[8]);
			current.setBalance(std::stof(fields[9]));
			current.setHash(fields[10]);

			if (ID == "-any" || ID == current.getID()) {
				try {
					loadUserTransactions(current);
				} catch (const std::exception& e) {
					throw e;
				}

				users.push_back(current);
			}
		}

		fields.clear();
		lineIterator++;
	}
	fs.close();

	if (preLoadUsersCount == users.size()) {
		return 0;
	}
	return 1;
}

void DataBase::saveUser(std::string ID) {
	User target;
	try {
		target = getUserWithID(ID);
	} catch (const std::exception& e) {
		if (typeid(e) == typeid(std::runtime_error)) {
			throw std::runtime_error("User with ID " + ID + " not found! Load user first! At DataBase::saveUser(std::string ID)");
		}
		else {
			throw e;
		}
	}
	
	// Loading entire DB
	std::vector <std::vector<std::string>> usersData;
	try {
		usersData = getUsersListString();
	} catch (const std::exception& e) {
		throw e;
	}

	// Corrceting specified user
	bool addNew = 1;
	for (int i = 0; i < usersData.size(); i++) {
		if (usersData[i][0] == ID) {
			usersData[i][0] = target.getID();
			usersData[i][1] = target.getBankCID();
			usersData[i][2] = target.getFirstName();
			usersData[i][3] = target.getSecondName();
			usersData[i][4] = std::to_string(target.getAge());
			usersData[i][5] = target.getGender();
			usersData[i][6] = target.getPhoneNumber();
			usersData[i][7] = target.getEmail();
			usersData[i][8] = target.getAddress();
			usersData[i][9] = std::to_string(target.getBalance());
			usersData[i][10] = target.getHash();
			addNew = 0;
		}
	}

	// If adding new user, not changing then adding to the array
	if (addNew) {
		std::vector<std::string> current;
		current.push_back(target.getID());
		current.push_back(target.getBankCID());
		current.push_back(target.getFirstName());
		current.push_back(target.getSecondName());
		current.push_back(std::to_string(target.getAge()));
		current.push_back(target.getGender());
		current.push_back(target.getPhoneNumber());
		current.push_back(target.getEmail());
		current.push_back(target.getAddress());
		current.push_back(std::to_string(target.getBalance()));
		current.push_back(target.getHash());
		usersData.push_back(current);
	}


	// Writing to .cdb file
	try {
		saveUsersListString(usersData);
	} catch (const std::exception& e) {
		throw e;
	}
}

void DataBase::addUser(User user) {
	for (int i = 0; i < users.size(); i++) {
		if (user.getID() == users[i].getID()) {
			throw std::runtime_error("Can`t add already existing user! ID: " + user.getID() + ". Match detected at void DataBase::addUser(User user)");
		}
	}
	users.push_back(user);
}

void DataBase::delUser(std::string ID) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].getID() == ID) {
			users[i].null();
			break;
		}
	}

	// Loading entire DB
	std::vector <std::vector<std::string>> usersData;
	try {
		usersData = getUsersListString();
	} catch (const std::exception& e) {
		throw e;
	}

	// Deleting
	for (int i = 0; i < usersData.size(); i++) {
		if (usersData[i][0] == ID) {
			usersData.erase(usersData.begin() + i);
			break;
		}
	}

	// Saving
	try {
		saveUsersListString(usersData);
	} catch (const std::exception& e) {
		throw e;
	}
}

void DataBase::delDB() {
	std::vector<std::vector<std::string>> null;
	saveUsersListString(null);
}

User* DataBase::getUserWithID(std::string ID) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].getID() == ID) return &users[i];
	}

	throw std::runtime_error("User with ID " + ID + " not found");
}

User* DataBase::at(int index) {
	if (index < 0 || index > users.size() - 1) {
		throw std::out_of_range("Index out ouf range! at DataBase::at(int index)");
	}
	return &users[index];
}

int DataBase::usersCount() {
	return users.size();
}
