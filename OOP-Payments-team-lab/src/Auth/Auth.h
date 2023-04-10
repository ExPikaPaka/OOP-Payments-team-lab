#pragma once
#include <string>
class Auth {
	std::string hash;
	bool state;
public:
	Auth();
	Auth(std::string stringToHash);

	void setHash(std::string hash);
	
	// Returns current hash stored in object
	std::string hash256();

	// Returns:
	//     true - if string hash equals hash
	//     false - otherwise
	bool checkHash(std::string string);

	// Returns current sate of object
	bool getState();

	// Returns calculated hash
	std::string hash256(std::string stringToHash);

};

