#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include "..\DB\DataBase.h"
#include "..\Auth\Auth.h"
#include "Timer/Timer.h"
#include "WindowHelper/Scene.h"
#include "WindowHelper/WindowHelper.h"
#include "WindowHelper/UIHelper/Button.h"
#include "WindowHelper/UIHelper/InputButton.h"

namespace colors {
	// Color defines
	static COLORREF bgCol = RGB(30, 30, 30);
	static COLORREF bw40 = RGB(40, 40, 40);
	static COLORREF bw50 = RGB(50, 50, 50);
	static COLORREF bw60 = RGB(60, 60, 60);
	static COLORREF bw70 = RGB(70, 70, 70);
	static COLORREF bw80 = RGB(80, 80, 80);
	static COLORREF bw90 = RGB(90, 90, 90);
	static COLORREF bw100 = RGB(100, 100, 100);
	static COLORREF bw110 = RGB(110, 110, 110);
	static COLORREF bw120 = RGB(120, 120, 120);
	static COLORREF bw130 = RGB(130, 130, 130);
	static COLORREF bw140 = RGB(140, 140, 140);
	static COLORREF bw255 = RGB(255, 255, 255);
	static COLORREF btPressedCol = RGB(60, 70, 90);

	static COLORREF colBg = RGB(30, 46, 61);
	static COLORREF colHover = RGB(60, 49, 67);
	static COLORREF colFace = RGB(39, 52, 68);
	static COLORREF colLGryBle = RGB(143, 147, 150);
	static COLORREF colLRed = RGB(255, 100, 100);
}
using namespace colors;

std::string wstringToString(const std::wstring& wstr) {
	if (wstr.empty()) {
		return std::string();
	}

	const int size_needed = WideCharToMultiByte(65001, 0, &wstr[0], static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
	std::string str(size_needed, 0);
	WideCharToMultiByte(65001, 0, &wstr[0], static_cast<int>(wstr.size()), &str[0], size_needed, nullptr, nullptr);
	return str;
}

std::wstring stringToWString(const std::string& str) {
	if (str.empty()) {
		return std::wstring();
	}

	
	const int size_needed = MultiByteToWideChar(65001, 0, &str[0], static_cast<int>(str.size()), nullptr, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(65001, 0, &str[0], static_cast<int>(str.size()), &wstr[0], size_needed);
	return wstr;
}



bool isEmailTaken(DataBase& db, std::string email) {
	if (!db.isOpen()) {
		throw std::runtime_error("Data base is not opened!");
	}

	try {
		for (int i = 0; i < db.usersCount(); i++) {
			if (db.at(i)->getEmail() == email) return true;
		}
	} catch (const std::exception& e) {
		throw e;
	}
	return false;
}

bool isPhoneNumberTaken(DataBase& db, std::string phoneNumber) {
	if (!db.isOpen()) {
		throw std::runtime_error("Data base is not opened!");
	}

	try {
		for (int i = 0; i < db.usersCount(); i++) {
			if (db.at(i)->getPhoneNumber() == phoneNumber) return true;
		}
	} catch (const std::exception& e) {
		throw e;
	}
	return false;
}



// Auth menu. Returns true if user Authenticated
User drawAuth(Scene& scene, DataBase& db, bool clearTextFields) {
	// Text defines
	static std::wstring lbAuth(L"  Авторизация  ");
	static std::wstring lbEmail(L"Почта");
	static std::wstring LbPassword(L"Пароль");
	static std::wstring lbLogIn(L"Войти");
	static std::wstring lbSingUp(L"Зарегистрироваться");
	static std::wstring lbLogInfo;

	bool fieldsNonZero = true;
	bool clTextFields = clearTextFields;

	// Control defines
	static int menuWidth = 400;
	static int menuHeight = 120;
	int xOffset = (scene.width / 2) - menuWidth / 2;
	int yOffset = (scene.height / 2) - menuHeight / 2;

	static int inBtOffsetX = 60;

	static UIHelper::Button btLogIn(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btSignUp(scene, 0, 0, 0, 0, colFace, colFace, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::InputButton btEmail(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::InputButton btPassword(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);


	

	// Clearing fields if needed
	if (clTextFields) {
		btEmail.text.clear();
		btEmail.wtext.clear();

		btPassword.text.clear();
		btPassword.wtext.clear();
	}


	// Reshaping if menu size changed
	btLogIn.setShape(xOffset, yOffset + 90, menuWidth, 20);
	btSignUp.setShape(xOffset, yOffset + 90 + 25, menuWidth, 20);
	btEmail.setShape(xOffset + inBtOffsetX, yOffset, menuWidth - inBtOffsetX, 20);
	btPassword.setShape(xOffset + inBtOffsetX, yOffset + 30, menuWidth - inBtOffsetX, 20);



	// Recieve input to labels
	btEmail.getInput();
	btPassword.getInput();




	// Begin scene drawing
	scene.beginPaint();

	// Filling custom bgColor
	scene.setBrushColor(colBg);
	scene.setPenColor(colBg);
	scene.rect(0, 0, scene.width, scene.height);

	// Drawing menu bounding box
	scene.setBrushColor(colFace);
	scene.setPenColor(colFace);
	scene.rect(xOffset - 20, yOffset - 35, xOffset + menuWidth + 20, yOffset + menuHeight + 20);

	// Draw buttons
	btLogIn.draw();
	btSignUp.draw();
	btEmail.draw();
	btPassword.draw();

	// Header
	scene.setPenColor(colFace);
	scene.setBrushColor(colFace);
	scene.rect(xOffset + menuWidth / 2 - lbAuth.size() * 10 / 2, yOffset - 50,
		xOffset + menuWidth / 2 + (lbAuth.size() + 2) * 10 / 2, yOffset - 50 + 27);
	scene.text((wchar_t*)lbAuth.c_str(), xOffset + menuWidth / 2 - lbAuth.size() * 10 / 2, yOffset - 50, 200, 50, 10, 27, 0, bw255, colFace);
	scene.setPenColor(bw60);
	scene.boundingBox(xOffset + menuWidth / 2 - lbAuth.size() * 10 / 2, yOffset - 50,
		xOffset + menuWidth / 2 + (lbAuth.size() + 2) * 10 / 2, yOffset - 50 + 27);

	// Fields label
	scene.text((wchar_t*)lbEmail.c_str(), xOffset, yOffset, inBtOffsetX, 20, 7, 16, 0, colLGryBle, colFace);
	scene.text((wchar_t*)LbPassword.c_str(), xOffset, yOffset + 30, inBtOffsetX, 20, 7, 16, 0, colLGryBle, colFace);

	// Log in label
	scene.text((wchar_t*)lbLogIn.c_str(), xOffset + menuWidth / 2 - (lbLogIn.size() / 2) * 7, yOffset + 90,
		100, 20, 7, 16, 0, colLGryBle, btLogIn.getCurrentFillColor());

	// Sign up labbel 
	scene.text((wchar_t*)lbSingUp.c_str(), xOffset + (menuWidth / 2) - (lbSingUp.size() / 2) * 7, yOffset + 115,
		150, 20, 7, 16, 0, bw100, btSignUp.getCurrentFillColor());


	// LogInfo label
	if (lbLogInfo.size()) {
		scene.setBrushColor(colFace);
		scene.setPenColor(bw60);
		scene.rect(xOffset - 20, yOffset + menuHeight + 50, xOffset + menuWidth + 20, yOffset + menuHeight + 120);
		scene.text((wchar_t*)lbLogInfo.c_str(), xOffset, yOffset + menuHeight + 50 + 10, menuWidth, 50, 7, 16, 0, RGB(255, 100, 100), colFace);
	}

	// Check if input > 0
	if (!btEmail.text.size()) {
		scene.setBrushColor(RGB(255, 100, 100));
		scene.setPenColor(RGB(255, 100, 100));
		scene.ellipse(xOffset + menuWidth + 5, yOffset + 5, xOffset + menuWidth + 15, yOffset + 15);
		fieldsNonZero = false;
	}
	if (!btPassword.text.size()) {
		scene.setBrushColor(RGB(255, 100, 100));
		scene.setPenColor(RGB(255, 100, 100));
		scene.ellipse(xOffset + menuWidth + 5, yOffset + 5 + 30, xOffset + menuWidth + 15, yOffset + 15 + 30);
		fieldsNonZero = false;
	}

	// End scene drawing
	scene.endPaint();




	// Log in check
	if (btLogIn.isPressed() && fieldsNonZero) {
		// Checking email
		User u;
		bool goodEmail = false;
		try {
			u.setEmail(btEmail.text);
			goodEmail = true;
		} catch (const std::exception& e) {
			std::string tmp(e.what());
			lbLogInfo = std::wstring(tmp.begin(), tmp.end());
		}


		if (goodEmail) {
			// Calculating hash
			std::string toHasSum = btEmail.text + btPassword.text;

			Auth auth;
			std::string hash = auth.hash256(toHasSum);

			// Findig user
			for (int i = 0; i < db.usersCount(); i++) {
				if (db.at(i)->getEmail() == btEmail.text) {
					u = db.at(i);
					break;
				}
				lbLogInfo = L"Указанный пользователь не найден! Попробуйте снова.";
			}

			// If we found user
			if (u.getID() != "null") {
				std::cout << "Calculated hash: " << hash << '\n';
				std::cout << "User hash:       " << u.getHash() << '\n';

				lbLogInfo = L"Неправильный пароль!";
				if (hash == u.getHash()) {
					lbLogInfo = L"С возвращением!";
					return u;
				}
			}

		}

	}

	// Register check
	if (btSignUp.isPressed() && fieldsNonZero) {
		// Checking email
		User u;
		bool goodEmail = false;
		try {
			u.setEmail(btEmail.text);
			goodEmail = true;
		} catch (const std::exception& e) {
			std::string tmp(e.what());
			lbLogInfo = std::wstring(tmp.begin(), tmp.end());
		}


		if (goodEmail) {
			// Calculating hash
			std::string toHasSum = btEmail.text + btPassword.text;

			Auth auth;
			std::string hash = auth.hash256(toHasSum);

			DataBase db;
			db.loadDB("res/DB");
			db.loadAllUsers();

			// Findig user
			for (int i = 0; i < db.usersCount(); i++) {
				if (db.at(i)->getEmail() == btEmail.text) {
					u = db.at(i);
					lbLogInfo = L"Указанный пользователь уже существует! \nПопробуйте войти.";
					break;
				}
			}
			u.setHash(hash);

			// If user not found - add new
			if (u.getID() == "null") {
				std::cout << "Calculated hash: " << hash << '\n';
				std::cout << "User hash:       " << u.getHash() << '\n';

				u.setID("register");
				return u;
			}
		}
	}
	return User();
}

// Regestration menu.
User drawRegister(Scene& scene, DataBase& db, User& user, bool clearTextFields) {

	// User info defines
	static bool isMale = false;
	static bool isFemale = false;
	bool fieldsNonZero = true;
	bool clTextFields = clearTextFields;


	// Labels defines
	static std::wstring lbSignUpAsk(L"  Регистрация  ");
	static std::wstring lbFirstName(L"Имя");
	static std::wstring lbSecondName(L"Фамилия");
	static std::wstring lbAge(L"Возраст");
	static std::wstring lbGender(L"Пол");
	static std::wstring lbMale(L"мужской");
	static std::wstring lbFemale(L"женский");
	static std::wstring lbPhoneNumber(L"Тел. номер");
	static std::wstring lbAdress(L"Адресс");
	static std::wstring lbCancel(L"Отменить");
	static std::wstring lbSignUp(L"Зарегестрироваться");
	static std::wstring lbLogInfo;


	// Buttons defines
	static UIHelper::InputButton btFirstName(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::InputButton btSecondName(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::InputButton btAge(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btMale(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btFemale(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::InputButton btPhoneNumber(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::InputButton btAdress(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btSignUp(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btCancel(scene, 0, 0, 0, 0, colFace, colFace, colHover, colHover, btPressedCol, btPressedCol);

	// Menu shape defines
	static int menuWidth = 400;
	static int menuHeight = 260;
	int xOffset = (scene.width / 2) - menuWidth / 2;
	int yOffset = (scene.height / 2) - menuHeight / 2;
	int xLbOffset = 100;



	// Clearing fields if needed
	if (clTextFields) {
		btFirstName.text.clear();
		btFirstName.wtext.clear();

		btSecondName.text.clear();
		btSecondName.wtext.clear();

		btAge.text.clear();
		btAge.wtext.clear();

		btPhoneNumber.text.clear();
		btPhoneNumber.wtext.clear();

		btAdress.text.clear();
		btAdress.wtext.clear();

		isFemale = false;
		isMale = false;
	}



	// Begin painting
	scene.beginPaint();

	// Filling custom bgColor
	scene.setBrushColor(colBg);
	scene.setPenColor(colBg);
	scene.rect(0, 0, scene.width, scene.height);

	// Filling menu
	scene.setBrushColor(colFace);
	scene.setPenColor(colFace);
	scene.rect(xOffset - 20, yOffset - 20, xOffset + menuWidth + 20, yOffset + menuHeight + 20);


	//		 Labels draw
	// 
	// SignUp message drawing
	scene.setPenColor(bw60);
	scene.setBrushColor(colFace);
	scene.rect(xOffset + menuWidth / 2 - ((lbSignUpAsk.size() + 1) * 10 / 2), yOffset - 27 / 2 - 20,
		xOffset + menuWidth / 2 + ((lbSignUpAsk.size() + 1) * 10 / 2), yOffset + 27 / 2 - 20);

	scene.text((wchar_t*)lbSignUpAsk.c_str(), xOffset + menuWidth / 2 - ((lbSignUpAsk.size() + 1) * 10 / 2), yOffset - 27 / 2 - 20,
		600, 27, 10, 27, 0, bw255, colFace);

	scene.setPenColor(bw60);
	scene.boundingBox(xOffset + menuWidth / 2 - ((lbSignUpAsk.size() + 1) * 10 / 2), yOffset - 27 / 2 - 20,
		xOffset + menuWidth / 2 + ((lbSignUpAsk.size() + 1) * 10 / 2), yOffset + 27 / 2 - 20);



	// Reshaping buttons
	btFirstName.setShape(xOffset + xLbOffset, yOffset + 20, menuWidth - xLbOffset, 20);
	btSecondName.setShape(xOffset + xLbOffset, yOffset + 20 + 30, menuWidth - xLbOffset, 20);
	btAge.setShape(xOffset + xLbOffset, yOffset + 20 + 60, menuWidth - xLbOffset, 20);
	btMale.setShape(xOffset + xLbOffset, yOffset + 20 + 90, (menuWidth - xLbOffset) / 2 - 5, 20);
	btFemale.setShape(xOffset + xLbOffset + ((menuWidth - xLbOffset) / 2 + 5), yOffset + 20 + 90, (menuWidth - xLbOffset) / 2 - 5, 20);
	btPhoneNumber.setShape(xOffset + xLbOffset, yOffset + 20 + 120, menuWidth - xLbOffset, 20);
	btAdress.setShape(xOffset + xLbOffset, yOffset + 20 + 150, menuWidth - xLbOffset, 20);
	btSignUp.setShape(xOffset, yOffset + 20 + 210, menuWidth, 20);
	btCancel.setShape(xOffset, yOffset + 20 + 235, menuWidth, 20);


	// Male female color and boolean logic
	if (btMale.isPressed()) {
		isMale = true;
		isFemale = false;
	}
	if (btFemale.isPressed()) {
		isFemale = true;
		isMale = false;
	}
	if (isMale) {
		btMale.setFillColor(btPressedCol);
		btMale.setOutlineColor(btPressedCol);
		btMale.setHoverFillColor(btPressedCol);
		btMale.setHoverOutlineColor(btPressedCol);
	} else {
		btMale.setFillColor(colBg);
		btMale.setOutlineColor(colBg);
		btMale.setHoverFillColor(colHover);
		btMale.setHoverOutlineColor(colHover);
	}
	if (isFemale) {
		btFemale.setFillColor(btPressedCol);
		btFemale.setOutlineColor(btPressedCol);
		btFemale.setHoverFillColor(btPressedCol);
		btFemale.setHoverOutlineColor(btPressedCol);
	} else {
		btFemale.setFillColor(colBg);
		btFemale.setOutlineColor(colBg);
		btFemale.setHoverFillColor(colHover);
		btFemale.setHoverOutlineColor(colHover);
	}

	// Drawing buttons
	btFirstName.draw();
	btSecondName.draw();
	btAge.draw();
	btMale.draw();
	btFemale.draw();
	btPhoneNumber.draw();
	btAdress.draw();
	btSignUp.draw();
	btCancel.draw();


	// Other labels draw
	scene.text((wchar_t*)lbFirstName.c_str(), xOffset, yOffset + 20, 200, 20, 7, 16, 0, colLGryBle, colFace);
	scene.text((wchar_t*)lbSecondName.c_str(), xOffset, yOffset + 20 + 30, 200, 20, 7, 16, 0, colLGryBle, colFace);
	scene.text((wchar_t*)lbAge.c_str(), xOffset, yOffset + 20 + 60, 200, 20, 7, 16, 0, colLGryBle, colFace);
	scene.text((wchar_t*)lbGender.c_str(), xOffset, yOffset + 20 + 90, 200, 20, 7, 16, 0, colLGryBle, colFace);
	scene.text((wchar_t*)lbMale.c_str(), xOffset + xLbOffset + ((menuWidth - xLbOffset) / 2 - 5 - (lbMale.size() + 1) * 7) / 2, yOffset + 20 + 90, 200, 20, 7, 16, 0, colLGryBle, btMale.getCurrentFillColor());
	scene.text((wchar_t*)lbFemale.c_str(), xOffset + xLbOffset + ((menuWidth - xLbOffset) / 2 + 5) + ((menuWidth - xLbOffset) / 2 - 5 - (lbMale.size() + 1) * 7) / 2, yOffset + 20 + 90, 200, 20, 7, 16, 0, colLGryBle, btFemale.getCurrentFillColor());
	scene.text((wchar_t*)lbPhoneNumber.c_str(), xOffset, yOffset + 20 + 120, 200, 20, 7, 16, 0, colLGryBle, colFace);
	scene.text((wchar_t*)lbAdress.c_str(), xOffset, yOffset + 20 + 150, 200, 20, 7, 16, 0, colLGryBle, colFace);
	scene.text((wchar_t*)lbSignUp.c_str(), xOffset + (menuWidth - (lbSignUp.size() + 1) * 7) / 2, yOffset + 20 + 210, 200, 20, 7, 16, 0, colLGryBle, btSignUp.getCurrentFillColor());
	scene.text((wchar_t*)lbCancel.c_str(), xOffset + (menuWidth - (lbCancel.size() + 1) * 7) / 2, yOffset + 20 + 235, 200, 20, 7, 16, 0, bw100, btCancel.getCurrentFillColor());


	// LogInfo label
	if (lbLogInfo.size()) {
		scene.setBrushColor(colFace);
		scene.setPenColor(bw60);
		scene.rect(xOffset - 20, yOffset + menuHeight + 50, xOffset + menuWidth + 20, yOffset + menuHeight + 120);
		scene.text((wchar_t*)lbLogInfo.c_str(), xOffset, yOffset + menuHeight + 50 + 10, menuWidth, 50, 7, 16, 0, RGB(255, 100, 100), colFace);
	}


	// Painting red ball in case some fields are empty
	scene.setBrushColor(RGB(255, 100, 100));
	scene.setPenColor(RGB(255, 100, 100));
	if (!btFirstName.text.size()) {

		scene.ellipse(xOffset + menuWidth + 5, yOffset + 25, xOffset + menuWidth + 15, yOffset + 35);
		fieldsNonZero = false;
	}
	if (!btSecondName.text.size()) {
		scene.ellipse(xOffset + menuWidth + 5, yOffset + 25 + 30, xOffset + menuWidth + 15, yOffset + 35 + 30);
		fieldsNonZero = false;
	}
	if (!btAge.text.size()) {
		scene.ellipse(xOffset + menuWidth + 5, yOffset + 25 + 60, xOffset + menuWidth + 15, yOffset + 35 + 60);
		fieldsNonZero = false;
	}
	if (!btPhoneNumber.text.size()) {
		scene.ellipse(xOffset + menuWidth + 5, yOffset + 25 + 120, xOffset + menuWidth + 15, yOffset + 35 + 120);
		fieldsNonZero = false;
	}
	if (!btAdress.text.size()) {
		scene.ellipse(xOffset + menuWidth + 5, yOffset + 25 + 150, xOffset + menuWidth + 15, yOffset + 35 + 150);
		fieldsNonZero = false;
	}
	if (!isFemale && !isMale) {
		scene.ellipse(xOffset + menuWidth + 5, yOffset + 25 + 90, xOffset + menuWidth + 15, yOffset + 35 + 90);
		fieldsNonZero = false;
	}


	scene.endPaint();





	// Button input 
	btFirstName.getInput();
	btSecondName.getInput();
	btAge.getInput();
	btPhoneNumber.getInput();
	btAdress.getInput();


	// Trying to register
	if (btSignUp.isPressed() && fieldsNonZero) {
		try {
			user.setID(std::to_string(db.usersCount()));
			user.setBankCID(std::to_string(db.usersCount()));
			user.setFirstName(btFirstName.text);
			user.setSecondName(btSecondName.text);
			user.setAge(std::stoi(btAge.text));
			if (std::stoi(btAge.text) < 14) {
				lbLogInfo = L"Пользователь должен быть не младше 14 лет!";
				throw std::runtime_error("");
			}

			user.setGender(isMale ? "Male" : "Female");
			user.setPhoneNumber(btPhoneNumber.text);
			if (isPhoneNumberTaken(db, btPhoneNumber.text)) {
				lbLogInfo = L"Тел. номер уже занят!";

				throw std::runtime_error("");
			}

			user.setAddress(btAdress.text);
			user.setBalance(200);

			
			// Adding user and saving it in case all is good
			db.addUser(user);
			db.saveUser(std::to_string(db.usersCount() - 1));

			return user;
		} catch (const std::exception& e) {

			// Check if age field made exception
			if (std::string(e.what()) == "invalid stoi argument") {
				lbLogInfo = L"Возраст должен быть числом!";
			} else {

				// Any other exception
				std::string ex = e.what();
				if (ex.size()) {
					lbLogInfo = std::wstring(ex.begin(), ex.end());
				}
			}

			std::cout << "Caught exception during user registration. Exception:\n" << e.what() << '\n';
		}
	}

	// Breaking register mode
	if (btCancel.isPressed()) {
		User u;
		u.setID("cancel");
		return u;
	}

	return User();
}

// Main menu
void drawOptionsMenu(Scene& scene, DataBase& db, User& user) {

	// Text defines
	static std::wstring lbCurrentBalance(L"Текущий баланс");
	static std::wstring lbTransfer(L"Перевести деньги");
	static std::wstring lbBlockAccount(L"Заблокировать аккаунт");
	static std::wstring lbClearBalance(L"Очистить баланс");
	static std::wstring lbLogOff(L"Очистить баланс");
	static std::wstring lbFirstName(L"Очистить баланс");
	static std::wstring lbSecondName(L"Очистить баланс");



	// Button defines
	static UIHelper::Button btBlockAccount(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::Button btClearBalance(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::Button btTransfer(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::Button btLogOff(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::Button btShowAccountDetails(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);



	// Size defines
	static int logoW = 70;
	static int logoH = 70;

	static int bodyW = 670;
	static int bodyH = 250;

	static int spaceW = 10;
	static int spaceH = 10;

	static int menuW = bodyW;
	static int menuH = logoH + spaceH + bodyH;

	int menuX = (scene.width - menuW) / 2;
	int menuY = (scene.height - menuH) / 2;



	// Logo define
	int colAdj = 0;

	static POINT logoBox[] = { {0, 0}, {70, 0}, {70, 70}, {0, 70} };
	static POINT logoCorners[] = { {35, 35}, {35, 0}, {70, 0}, {70, 35}, {0, 35}, {0, 70}, {35, 70} };
	static POINT logoStar[] = { {35, 2}, {45, 27}, {68, 35}, {45, 43}, {35, 68}, {25, 43}, {2, 35}, {25, 27} };

	static const int logoBoxLen = std::size(logoBox);
	static const int logoCornersLen = std::size(logoCorners);
	static const int logoStarLen = std::size(logoStar);

	static POINT lBox[logoBoxLen];
	static POINT lCorners[logoCornersLen];
	static POINT lStar[logoStarLen];

	for (int i = 0; i < logoBoxLen; i++) {
		lBox[i].x = logoBox[i].x + menuX;
		lBox[i].y = logoBox[i].y + menuY;
	}
	for (int i = 0; i < logoCornersLen; i++) {
		lCorners[i].x = logoCorners[i].x + menuX;
		lCorners[i].y = logoCorners[i].y + menuY;
	}
	for (int i = 0; i < logoStarLen; i++) {
		lStar[i].x = logoStar[i].x + menuX;
		lStar[i].y = logoStar[i].y + menuY;
	}



	// User variables define
	static std::wstring uFirstName;
	static std::wstring uSecondName;
	static std::wstring uInitials;
	static std::wstring uEmail;



	// Reshaping elements
	btShowAccountDetails.setShape(menuX, menuY, logoW, logoH);
	



	// Button logics
	if (btShowAccountDetails.isMouseInArea()) colAdj = 20; // Change logo color in some case
	if (btShowAccountDetails.isPressed()) colAdj = 0;



	// Start paint
	scene.beginPaint();


	// Background fill
	scene.setColor(colBg);
	scene.rect(0, 0, scene.width, scene.height);

	// Menu drawing
	scene.setColor(colFace);
	scene.rect(menuX, menuY, menuX + logoW, menuY + logoH);
	scene.rect(menuX + logoW + spaceW, menuY, menuX + menuW, menuY + logoH);
	scene.rect(menuX, menuY + logoH + spaceH, menuX + menuW, menuY + menuH);

	// Logo drawing
	scene.setColor(60 + colAdj, 70 + colAdj, 90 + colAdj);
	scene.poly(lBox, logoBoxLen);

	scene.setColor(60 + colAdj, 49 + colAdj, 67 + colAdj);
	scene.poly(lCorners, logoCornersLen);

	scene.setColor(255, 100 + colAdj, 100 + colAdj);
	scene.poly(lStar, logoStarLen);


	
	//		Text fields drawind

	// header draw



	scene.endPaint();
}
