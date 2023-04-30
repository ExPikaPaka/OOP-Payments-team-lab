#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <regex>
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
	static COLORREF bw200 = RGB(200, 200, 200);
	static COLORREF bw210 = RGB(210, 210, 210);
	static COLORREF bw220 = RGB(220, 220, 220);
	static COLORREF bw230 = RGB(230, 230, 230);
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

	const int size_needed = WideCharToMultiByte(1251, 0, &wstr[0], static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
	std::string str(size_needed, 0);
	WideCharToMultiByte(1251, 0, &wstr[0], static_cast<int>(wstr.size()), &str[0], size_needed, nullptr, nullptr);
	return str;
}

std::wstring stringToWString(const std::string& str) {
	if (str.empty()) {
		return std::wstring();
	}

	const int size_needed = MultiByteToWideChar(1251, 0, &str[0], static_cast<int>(str.size()), nullptr, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(1251, 0, &str[0], static_cast<int>(str.size()), &wstr[0], size_needed);
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
	
#ifdef UA 
	// Text defines
	static std::wstring lbAuth(L"  Авторизація  ");
	static std::wstring lbEmail(L"Пошта");
	static std::wstring LbPassword(L"Пароль");
	static std::wstring lbLogIn(L"Увійти");
	static std::wstring lbSingUp(L"Зареєструватися");
	static std::wstring lbLogInfo;
#else     
	// Text defines
	static std::wstring lbAuth(L"  Авторизация  ");
	static std::wstring lbEmail(L"Почта");
	static std::wstring LbPassword(L"Пароль");
	static std::wstring lbLogIn(L"Войти");
	static std::wstring lbSingUp(L"Зарегистрироваться");
	static std::wstring lbLogInfo;
#endif     


	

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


	// LbLogInfo clearing time logic define
	static auto logInfoStart = std::chrono::steady_clock::now();





	// Clearing log info, if the las update was > 2 sec ago
	if (std::chrono::steady_clock::now() > logInfoStart + std::chrono::seconds(2)) {
		if (lbLogInfo.size()) {
			lbLogInfo.clear();
		}
	}

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
			logInfoStart = std::chrono::steady_clock::now();
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
			}

			// If we found user
			if (u.getID() != "null") {
				std::cout << "Calculated hash: " << hash << '\n';
				std::cout << "User hash:       " << u.getHash() << '\n';

#ifdef UA  
				lbLogInfo = L"Невірний пароль!";
				if (hash == u.getHash()) {
					lbLogInfo = L"З поверненням!";
					return u;
				}
#else  
				lbLogInfo = L"Неправильный пароль!";
				if (hash == u.getHash()) {
					lbLogInfo = L"С возвращением!";
					return u;
				}
#endif
				logInfoStart = std::chrono::steady_clock::now();
			} else {
#ifdef UA   
				lbLogInfo = L"Зазначеного користувача не знайдено! Спробуйте знову.";
#else     
				lbLogInfo = L"Указанный пользователь не найден! Попробуйте снова.";
#endif
				logInfoStart = std::chrono::steady_clock::now();
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
			logInfoStart = std::chrono::steady_clock::now();
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
#ifdef UA 
					lbLogInfo = L"Зазначений користувач вже існує! \nСпробуйте увійти.";
#else
					lbLogInfo = L"Указанный пользователь уже существует! \nПопробуйте войти.";
#endif
					logInfoStart = std::chrono::steady_clock::now();
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

#ifdef UA 
	// Labels defines
	static std::wstring lbSignUpAsk(L"  Реєстрація  ");
	static std::wstring lbFirstName(L"Імя");
	static std::wstring lbSecondName(L"Прізвище");
	static std::wstring lbAge(L"Вік");
	static std::wstring lbGender(L"Стать");
	static std::wstring lbMale(L"чоловічий");
	static std::wstring lbFemale(L"жіночий");
	static std::wstring lbPhoneNumber(L"Тел. номер");
	static std::wstring lbAddress(L"Адреса");
	static std::wstring lbCancel(L"Скасувати");
	static std::wstring lbSignUp(L"Зареєструватись");
	static std::wstring lbLogInfo;
#else
	// Labels defines
	static std::wstring lbSignUpAsk(L"  Регистрация  ");
	static std::wstring lbFirstName(L"Имя");
	static std::wstring lbSecondName(L"Фамилия");
	static std::wstring lbAge(L"Возраст");
	static std::wstring lbGender(L"Пол");
	static std::wstring lbMale(L"мужской");
	static std::wstring lbFemale(L"женский");
	static std::wstring lbPhoneNumber(L"Тел. номер");
	static std::wstring lbAddress(L"Адрес");
	static std::wstring lbCancel(L"Отменить");
	static std::wstring lbSignUp(L"Зарегистрироваться");
	static std::wstring lbLogInfo;
#endif

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

	// LbLogInfo clearing time logic define
	static auto logInfoStart = std::chrono::steady_clock::now();




	// Clearing log info, if the las update was > 2 sec ago
	if (std::chrono::steady_clock::now() > logInfoStart + std::chrono::seconds(2)) {
		if (lbLogInfo.size()) {
			lbLogInfo.clear();
		}
	}

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
	scene.text((wchar_t*)lbAddress.c_str(), xOffset, yOffset + 20 + 150, 200, 20, 7, 16, 0, colLGryBle, colFace);
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
#ifdef UA 
				lbLogInfo = L"Користувач повинен бути не молодшим 14 років!";
#else
				lbLogInfo = L"Пользователь должен быть не младше 14 лет!";
#endif
				throw std::runtime_error("");
			}

			user.setGender(isMale ? "Male" : "Female");
			user.setPhoneNumber(btPhoneNumber.text);
			if (isPhoneNumberTaken(db, btPhoneNumber.text)) {
#ifdef UA 
				lbLogInfo = L"Тел. номер уже зайнятий!";
#else
				lbLogInfo = L"Тел. номер уже занят!";
#endif

				throw std::runtime_error("");
			}

			user.setAddress(btAdress.text);
			user.setBalance(200);

			
			// Adding user and saving it in case all is good
			db.addUser(user);
			db.saveUser(std::to_string(db.usersCount() - 1));
			logInfoStart = std::chrono::steady_clock::now();

			return user;
		} catch (const std::exception& e) {

			// Check if age field made exception
			if (std::string(e.what()) == "invalid stoi argument") {
#ifdef UA 
				lbLogInfo = L"Вік має бути числом!";
#else
				lbLogInfo = L"Возраст должен быть числом!";
#endif	
			} else {

				// Any other exception
				std::string ex = e.what();
				if (ex.size()) {
					lbLogInfo = std::wstring(ex.begin(), ex.end());
				}
			}

			logInfoStart = std::chrono::steady_clock::now();
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
#ifdef UA 
	// Text defines
	static std::wstring lbCurrentBalance(L"Поточний баланс");
	static std::wstring lbTransfer(L"Переказати гроші");
	static std::wstring lbBlockAccount(L"Заблокувати обл. запис");
	static std::wstring lbClearBalance(L"Очистити баланс");
	static std::wstring lbLogOff(L"Вийти");
	static std::wstring lbByPhone(L"За тел. номером");
	static std::wstring lbByEmail(L"За поштою");
	static std::wstring lbAskPhone(L"Введіть тел. номер одержувача");
	static std::wstring lbAskEmail(L"Введіть ел. адресу одержувача");
	static std::wstring lbAskValue(L"Сума");
	static std::wstring lbReason(L"Призначення");
	static std::wstring lbSend(L"Надіслати");
	static std::wstring lbCancel(L"Скасувати");
	static std::wstring lbTsfrHistory(L"Історія транзакцій");
	static std::wstring lbLogInfo;
#else
	// Text defines
	static std::wstring lbCurrentBalance(L"Текущий баланс");
	static std::wstring lbTransfer(L"Перевести деньги");
	static std::wstring lbBlockAccount(L"Заблокировать аккаунт");
	static std::wstring lbClearBalance(L"Очистить баланс");
	static std::wstring lbLogOff(L"Выйти");
	static std::wstring lbByPhone(L"За тел. номером");
	static std::wstring lbByEmail(L"За почтой");
	static std::wstring lbAskPhone(L"Введите тел. номер получателя");
	static std::wstring lbAskEmail(L"Введите ел. адрес получателя");
	static std::wstring lbAskValue(L"Сумма");
	static std::wstring lbReason(L"Предназначение");
	static std::wstring lbSend(L"Отправить");
	static std::wstring lbCancel(L"Отменить");
	static std::wstring lbTsfrHistory(L"История транзакций");
	static std::wstring lbLogInfo;
#endif


	// Button defines
	static UIHelper::Button btBlockAccount(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btClearBalance(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btTransfer(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btTsfrByPhone(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btTsfrByEmail(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btLogOff(scene, 0, 0, 0, 0);
	static UIHelper::Button btShowAccountDetails(scene, 0, 0, 0, 0);
	static UIHelper::InputButton btTsfrDest(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::InputButton btTsfrVal(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::InputButton btTsfReason(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btSend(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btCancel(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btTsfrHistory(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btTsfrHUp(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);
	static UIHelper::Button btTsfrHDown(scene, 0, 0, 0, 0, colBg, colBg, colHover, colHover, btPressedCol, btPressedCol);


	// Size defines
	static int logoW = 70;
	static int logoH = 70;

	static int bodyW = 770;
	static int bodyH = 250;

	static int spaceW = 10;
	static int spaceH = 10;

	static int menuW = bodyW;
	static int menuH = logoH + spaceH + bodyH;

	int menuX = (scene.width - menuW) / 2;
	int menuY = (scene.height - menuH) / 2;

	static int subMenuW = menuW - 200 - 20 - 50;
	static int subMenuH = menuH - 20 - logoH - spaceH;
	int subMenuX = menuX + menuW - 10 - subMenuW;
	int subMenuY = menuY + logoH + spaceH + 10;
	
	// Logic boolean defines
	static bool blTransfer = false;
	static bool blTsfrByPhone = false;
	static bool blTsfrByEmail = false;
	static bool blTsfrHistory = false;


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



	// Transactions history define
	static int tsfrStart = 0;


	// LbLogInfo clearing time logic define
	static auto logInfoStart = std::chrono::steady_clock::now();





	// User update
	try {
		db.clearUserList();
		db.loadAllUsers();
		user = db.getUserWithID(user.getID());
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}

	// User variables define
	static std::wstring uFirstName = stringToWString(user.getFirstName());
	static std::wstring uSecondName = stringToWString(user.getSecondName());
	static std::wstring uInitials = uFirstName + std::wstring(L" ") + uSecondName;
	static std::wstring uEmail = stringToWString(user.getEmail());
	std::wstringstream wss;
	wss << L"Бал.: " << std::fixed << std::setprecision(2) << user.getBalance() << L" у.е.";
	std::wstring uBalance = wss.str();


	// Reshaping elements
	btShowAccountDetails.setShape(menuX, menuY, logoW, logoH);
	btTransfer.setShape(menuX + 10, menuY + logoH + spaceH + 10, 200, 20);
	btTsfrHistory.setShape(menuX + 10, menuY + menuH - 10 - 80, 200, 20);
	btClearBalance.setShape(menuX + 10, menuY + menuH - 10 - 40 - 10, 200, 20);
	btBlockAccount.setShape(menuX + 10, menuY + menuH - 10 - 20, 200, 20);
	btTsfrByPhone.setShape(menuX + 10, menuY + logoH + spaceH + 10 + 20 + 10, 200, 20);
	btTsfrByEmail.setShape(menuX + 10, menuY + logoH + spaceH + 10 + 40 + 20, 200, 20);
	btTsfrDest.setShape(subMenuX, subMenuY + 20 + 10, subMenuW, 20);
	btTsfrVal.setShape(subMenuX + 100, subMenuY + 60, subMenuW - 100, 20);
	btTsfReason.setShape(subMenuX, subMenuY + 120, subMenuW, subMenuH - 150);
	btSend.setShape(subMenuX, subMenuY + 210, subMenuW / 2 - 5, 20);
	btCancel.setShape(subMenuX + subMenuW / 2 + 5, subMenuY + 210, subMenuW / 2 - 5, 20);
	btTsfrHDown.setShape(subMenuX + subMenuW - 20, subMenuY, 20, 20);
	btTsfrHUp.setShape(subMenuX + subMenuW - 50, subMenuY, 20, 20);


	// Button logics
	if (btShowAccountDetails.isMouseInArea()) colAdj = 20; // Change logo color in some case
	if (btShowAccountDetails.isPressed()) colAdj = 0;

	if (btTransfer.isPressed()) { // Show/Hide transfer menu
		if (blTransfer) {
			blTransfer = false;
			blTsfrByEmail = false;
			blTsfrByPhone = false;
		} else {
			blTransfer = true;
		}
		blTsfrHistory = false;
	}

	if (btTsfrHistory.isPressed()) {
		if (blTsfrHistory) {
			blTsfrHistory = false;
		} else {
			blTsfrHistory = true;
			blTsfrByEmail = false;
			blTsfrByPhone = false;
			blTransfer = false;
		}
	}

	if (blTsfrByEmail || blTsfrByPhone) {
		btTsfrDest.getInput();
		btTsfrVal.getInput();
		btTsfReason.getInput();
	}

	if (btTsfrHUp.isPressed()) {
		if (tsfrStart < user.getTransactionsCount()) {
			tsfrStart++;
		}
	}
	if (btTsfrHDown.isPressed()) {
		if (tsfrStart > 0) {
			tsfrStart--;
		}
	}


	// Clearing log info, if the las update was > 2 sec ago
	if (std::chrono::steady_clock::now() > logInfoStart + std::chrono::seconds(1)) {
		if (lbLogInfo.size()) {
			lbLogInfo.clear();
		}
	}
	





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


	
	//		Text fields drawing

	// header draw
	scene.text((wchar_t*)uInitials.c_str(), menuX + logoW + spaceW + 10, menuY + 10, 600, 20, 8, 20, 0, bw200, colFace);
	scene.text((wchar_t*)uEmail.c_str(), menuX + logoW + spaceW + 10, menuY + 10 + 20 + 5, 600, 20, 8, 20, 0, bw200, colFace);
	scene.text((wchar_t*)uBalance.c_str(), menuX + menuW - 10 - (uBalance.size() - 1) * 8, menuY + 10 + 20 + 5, 600, 20, 8, 20, 0, bw200, colFace);

	// Buttons draw
	scene.setColor(colBg);
	btTransfer.draw();
	btClearBalance.draw();
	btBlockAccount.draw();
	btTsfrHistory.draw();
	

	scene.text((wchar_t*)lbTransfer.c_str(), menuX + 10 + 8, menuY + logoH + spaceH + 10, 200, 20, 8, 20, 0, bw200, btTransfer.getCurrentFillColor());
	scene.text((wchar_t*)lbClearBalance.c_str(), menuX + 10 + 8, menuY + menuH - 10 - 40 - 10, 200, 20, 8, 20, 0, bw200, btClearBalance.getCurrentFillColor());
	scene.text((wchar_t*)lbBlockAccount.c_str(), menuX + 10 + 8, menuY + menuH - 10 - 20, 200, 20, 8, 20, 0, bw200, btBlockAccount.getCurrentFillColor());
	scene.text((wchar_t*)lbTsfrHistory.c_str(), menuX + 10 + 8, menuY + menuH - 10 - 80, 200, 20, 8, 20, 0, bw200, btTsfrHistory.getCurrentFillColor());


	// Transfer history draw
	if (blTsfrHistory) {
		btTsfrHUp.draw();
		btTsfrHDown.draw();

		scene.text((wchar_t*)lbTsfrHistory.c_str(), subMenuX, subMenuY, 200, 20, 8, 20, 0, bw200, colFace);

		
		for (int i = tsfrStart; i < min(user.getTransactionsCount(), tsfrStart + 7); i++) {
			Transaction tsc = user.getTransaction(user.getTransactionsCount() - i - 1);
			User dest;

				
			try {
				dest = db.getUserWithID(tsc.getSenderBankCID());
			
				scene.setColor(140, 200, 210);
				if (tsc.getSenderBankCID() == user.getBankCID()) {
					scene.setColor(255, 100, 100);
						dest = db.getUserWithID(tsc.getReceiverBankCID());
				}
			} catch (const std::exception& e) {
				std::cout << e.what() << '\n';
			}
			std::string rtms = tsc.transactionTime().toString();
			std::wstring tm = std::wstring(rtms.begin(), rtms.begin() + 5) + std::wstring(rtms.begin() + 8, rtms.end());

			std::wstringstream wss;
			wss << std::fixed << std::setprecision(2) << tsc.getAmount();
			std::wstring tscAmount = wss.str();

			scene.ellipse(subMenuX + 2, subMenuY + 30 + i * 30 + 2 - 30 * tsfrStart, subMenuX + 20 - 2, subMenuY + 30 + i * 30 + 20 - 2 - 30 * tsfrStart);
			scene.setColor(colBg);
			scene.rect(subMenuX + 20, subMenuY + 30 + i * 30 - 30 * tsfrStart, subMenuX + subMenuW, subMenuY + 30 + i * 30 + 20 - 30 * tsfrStart);
			
			scene.text((wchar_t*)stringToWString(tsc.getPurpose()).c_str(), subMenuX + 20 + 7, subMenuY + 30 + i * 30 - 30 * tsfrStart, 150, 20, 7, 16, 0, bw200, colBg);
			scene.text((wchar_t*)stringToWString(dest.getFirstName() + " " + dest.getSecondName()).c_str(), subMenuX + subMenuW - 60 - 8 - 120 - 8 - 100, subMenuY + 30 + i * 30 - 30 * tsfrStart, 100, 20, 7, 16, 0, bw200, colBg);
		
			scene.text((wchar_t*)tm.c_str(), subMenuX + subMenuW - 60 - 7 - 120 - 7, subMenuY + 30 + i * 30 - 30 * tsfrStart, 120, 20, 7, 16, 0, bw200, colBg);
			scene.text((wchar_t*)tscAmount.c_str(), subMenuX + subMenuW - tscAmount.size() * 7 - 7, subMenuY + 30 + i * 30 - 30 * tsfrStart, 200, 20, 7, 16, 0, bw200, colBg);

		}
	}

	// Transfer buttons
	if (blTransfer) {
		btTsfrByPhone.draw();
		btTsfrByEmail.draw();

		scene.text((wchar_t*)lbByPhone.c_str(), btTsfrByPhone.getX() + 8, btTsfrByPhone.getY(), 200, 20, 8, 20, 0, bw200, btTsfrByPhone.getCurrentFillColor());
		scene.text((wchar_t*)lbByEmail.c_str(), btTsfrByEmail.getX() + 8, btTsfrByEmail.getY(), 200, 20, 8, 20, 0, bw200, btTsfrByEmail.getCurrentFillColor());
	}

	if (blTransfer) {
		if (btTsfrByPhone.isPressed()) {
			blTsfrByPhone = true;
			blTsfrByEmail = false;
		}
		
		if (btTsfrByEmail.isPressed()) {
			blTsfrByPhone = false;
			blTsfrByEmail = true;
		}

		if (blTsfrByPhone) { // if transfer by phone draw
			scene.text((wchar_t*)lbAskPhone.c_str(), subMenuX + (subMenuW - lbAskPhone.size() * 8) / 2, subMenuY, 400, 20, 8, 20, 0, bw200, colFace);

		}
		if (blTsfrByEmail) { // if transfer by email draw
			scene.text((wchar_t*)lbAskEmail.c_str(), subMenuX + (subMenuW - lbAskEmail.size() * 8) / 2, subMenuY, 400, 20, 8, 20, 0, bw200, colFace);
		}

		if (blTsfrByEmail || blTsfrByPhone) {  // Drawing other buttons, inputs, and texts
			btTsfrDest.draw();
			scene.text((wchar_t*)lbAskValue.c_str(), subMenuX + 8, subMenuY + 60, 100, 20, 8, 20, 0, bw200, colFace);
			btTsfrVal.draw();
		
			scene.text((wchar_t*)lbReason.c_str(), subMenuX + 8, subMenuY + 90, 200, 20, 8, 20, 0, bw200, colFace);
			btTsfReason.draw();

			btSend.draw();
			btCancel.draw();

			scene.text((wchar_t*)lbSend.c_str(), subMenuX + (subMenuW / 2 - lbSend.size() * 8) / 2, subMenuY + 210, 100, 20, 8, 20, 0, bw200, btSend.getCurrentFillColor());
			scene.text((wchar_t*)lbCancel.c_str(), subMenuX + subMenuW / 2 + 5 + (subMenuW / 2 - lbSend.size() * 8) / 2, subMenuY + 210, 100, 20, 8, 20, 0, bw200, btCancel.getCurrentFillColor());
		}
	}


	// LogInfo label
	if (lbLogInfo.size()) {
		scene.setBrushColor(colFace);
		scene.setPenColor(bw60);
		scene.rect(menuX, menuY + menuH + 10, menuX + menuW, menuY + menuH + 10 + 70);

		int xCentered = menuX + (menuW - lbLogInfo.size() * 7) / 2;
		xCentered = xCentered < menuX ? menuX : xCentered;
		scene.text((wchar_t*)lbLogInfo.c_str(), xCentered + 10, menuY + menuH + 20, menuW - xCentered - 10, 50, 7, 16, 0, (std::regex_match(std::string(lbLogInfo.begin(), lbLogInfo.end()), std::regex("(Success\\s*)*")) ? RGB(100, 255, 100) : RGB(255, 100, 100)), colFace);
	}

	scene.endPaint();






	//			Options logic

	// Transfer logic
	if (blTsfrByEmail || blTsfrByPhone || btClearBalance.isPressed()) {
		if (btSend.isPressed() || btClearBalance.isPressed()) {
			User receiver;

			try {
				// Getting receiver user
				for (int i = 0; i < db.usersCount(); i++) {
					if (blTsfrByEmail) {
						if (db.at(i)->getEmail() == btTsfrDest.text) {
							receiver = db.at(i);
						}
					}
					if (blTsfrByPhone) {
						if (db.at(i)->getPhoneNumber() == btTsfrDest.text) {
							receiver = db.at(i);
						}
					}
				}


				

				if (receiver.getID() != "null" || btClearBalance.isPressed()) {
					Transaction tr;

					tr.setSenderBankCID(user.getBankCID());
					tr.setCommission(0);

					// Clearing balance if bt pressed
					if (btClearBalance.isPressed()) {
						tr.setAmount(user.getBalance());
						tr.setPurpose("Clear balance");
						tr.setReceiverBankCID("-1");

					} else { // Usual transaction
						tr.setAmount(std::stoi(btTsfrVal.text));
						tr.setPurpose(btTsfReason.text);
						tr.setReceiverBankCID(receiver.getBankCID());

						// Check if specified money amount is logical
						if (tr.getAmount() > user.getBalance()) {
							throw std::runtime_error("Not enough money");
						}
						if (tr.getAmount() <= 0) {
							throw std::runtime_error("Invalid amount");
						}
					}

					
					// Saving users
					for (int i = 0; i < db.usersCount(); i++) {
						if (db.at(i)->getID() == user.getID()) {
							tr.setTransactionID(user.getTransactionsCount() + 1);
							db.at(i)->setBalance(db.at(i)->getBalance() - tr.getAmount());
							db.at(i)->addTransaction(tr);
							db.saveUser(user.getID());
							user = db.at(i);
							db.saveUserTransactions(user);
						}
						if (db.at(i)->getID() == receiver.getID()) {
							tr.setTransactionID(receiver.getTransactionsCount() + 1);
							db.at(i)->setBalance(db.at(i)->getBalance() + tr.getAmount());
							db.at(i)->addTransaction(tr);
							db.saveUser(receiver.getID());
							receiver = db.at(i);
							db.saveUserTransactions(receiver);
						}
					}
				} else {
					throw std::runtime_error("Receiver not found");
				}
				lbLogInfo += L"Success  ";
				logInfoStart = std::chrono::steady_clock::now();
			} catch (const std::exception& e) {
				std::string ex = e.what();
				if (ex.size()) {
					lbLogInfo += std::wstring(ex.begin(), ex.end()) + L"  ";
					logInfoStart = std::chrono::steady_clock::now();
				}

				std::cout << e.what() << '\n';
			}
		}
	}


	if (btBlockAccount.isPressed()) {
		try {
			db.getUserWithID(user.getID())->setHash(std::string("BLOCKED_") + user.getHash());
			db.saveUser(user.getID());
			std::cout << db.getUserWithID(user.getID())->getHash();
			lbLogInfo += L"Success  ";
			logInfoStart = std::chrono::steady_clock::now();
		} catch (const std::exception& e) {
			std::string ex = e.what();
			if (ex.size()) {
				lbLogInfo += std::wstring(ex.begin(), ex.end()) + L"  ";
				logInfoStart = std::chrono::steady_clock::now();
			}

			std::cout << e.what();
		}
		exit(0);
	}
	if (btTransfer.isPressed() || btSend.isPressed() || btTsfrHistory.isPressed() || btTsfrHUp.isPressed() || btTsfrHDown.isPressed()) {
		Sleep(100);
	}
}
