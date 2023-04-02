#include "DataBase.h"
#include <sstream>
#include <fstream>

DataBase::DataBase() {
}

void DataBase::loadDB(std::string filePath) {
	if (filePath.empty()) {
		throw std::invalid_argument("File path is empty!");
	}
	std::ifstream fs(filePath);

	if (!fs.is_open()) {
		throw std::ios_base::failure("Could not ope file \"" + filePath + "\"");
	}
	
	User current;

	// Checking if file fields are ok
	int fieldsCount = 9;

	// Reading single line (to the '\n')
	std::string line;
	char delimiter = '}';
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
			
			users.push_back(current);
		}

		fields.clear();
		lineIterator++;
	}
	fs.close();
}

void DataBase::saveDB(std::string filePath) {
	if (filePath.empty()) {
		throw std::invalid_argument("File path is empty!");
	}
	std::ofstream os(filePath);

	if (!os.is_open()) {
		throw std::ios_base::failure("Could not ope file \"" + filePath + "\"");
	}

	char delimiter = '}';
	for (int i = 0; i < users.size(); i++) {
		os << users[i].getID() << delimiter;
		os << users[i].getBankCID() << delimiter;
		os << users[i].getFirstName() << delimiter;
		os << users[i].getSecondName() << delimiter;
		os << users[i].getAge() << delimiter;
		os << users[i].getGender() << delimiter;
		os << users[i].getPhoneNumber() << delimiter;
		os << users[i].getEmail() << delimiter;
		os << users[i].getAddress() << "\n";
	}
	os.close();
}

User* DataBase::getUserWithID(std::string ID) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].getID() == ID) return &users[i];
	}

	return 0;
}
