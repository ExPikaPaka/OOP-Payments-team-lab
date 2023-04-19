#include <iostream>
#include <Windows.h>
#include <fstream>
#include "..\DB\DataBase.h"
#include "..\Auth\Auth.h"
#include "Timer/Timer.h"
#include "WindowHelper/Scene.h"
#include "WindowHelper/WindowHelper.h"
#include "WindowHelper/UIHelper/Button.h"
#include "WindowHelper/UIHelper/InputButton.h"


// Auth menu. Returns true if user Authenticated
User drawAuth(Scene& scene, DataBase& db, bool clearTextFields = false);
User drawRegister(Scene& scene, DataBase& db, User& hash, bool clearTextFields = false);
void drawOptionsMenu(Scene& scene, DataBase& db, User& user);
void drawTransferMenu(Scene& scene, DataBase& db, User& user, User& target);


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
}
using namespace colors;


int main() {
	system("chcp 1251");
	system("cls");

	// Creating windw
	HWND window = 0;
	WindowHelper wh;
	window = wh.initWindow((wchar_t*)L"Sample window", 100, 100, 800, 600, WS_OVERLAPPEDWINDOW);
	ShowWindow(window, SW_SHOWNORMAL);

	MSG msg = {};


	// Timer
	Timer tm1;
	tm1.setFPS(30);


	// Verification
	Auth authentificator;


	// Creating scene
	Scene scene(window, msg);
	scene.backgroundColor = bgCol;


	// Database loading
	DataBase db;

	try {
		db.loadDB("res/DB");
		db.loadAllUsers();
	} catch (const std::exception& e) {
		std::cout << "Error during DataBase loading:\n" << e.what() << '\n';
	}


	bool authenticated = false;
	bool registerMode = false;

	bool clearAuthFieldsOnce = false;
	bool clearRegFieldsOnce = false;
	User currUser;
	User regUser;
	std::string hash = "";

	while (GetMessage(&msg, NULL, 0, 0)) {
		if (msg.message == WM_QUIT) {
			break;
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Draw auth menu
		if (!authenticated) {
			if (!registerMode) {
				currUser = drawAuth(scene, db, clearAuthFieldsOnce);
				hash = currUser.getHash();

				if (currUser.getID() == "register") {
					registerMode = true;
					clearRegFieldsOnce = true;
					continue;
				} else {
					authenticated = hash.size() ? true : false;
				}
			} else { // Draw register menu
				regUser = drawRegister(scene, db, currUser, clearRegFieldsOnce);

				// Canceling if case
				if (regUser.getID() == "cancel") {
					registerMode = false;
					clearAuthFieldsOnce = true;
					continue;
				} else if (regUser.getID() != "null") {// Registering user
					// LOGIC HERE
					currUser = regUser;
					registerMode = false;
					authenticated = true;
				}
			}
		}

		if (authenticated) {
			drawOptionsMenu(scene, db, currUser);
		}

		// Clearing auth and reg fields if needed once
		if (clearAuthFieldsOnce) {
			clearAuthFieldsOnce = false;
		}
		if (clearRegFieldsOnce) {
			clearRegFieldsOnce = false;
		}
	}	
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

	static UIHelper::Button btLogIn(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::Button btSignUp(scene, 0, 0, 0, 0, bw40, bw40, bw40, bw40, btPressedCol, btPressedCol);
	static UIHelper::InputButton btEmail(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btPassword(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);

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
	scene.setBrushColor(RGB(30, 32, 34));
	scene.setPenColor(RGB(30, 32, 34));
	scene.rect(0, 0, scene.width, scene.height);

	// Drawing menu bounding box
	scene.setBrushColor(bw40);
	scene.setPenColor(bw60);
	scene.rect(xOffset - 20, yOffset - 35, xOffset + menuWidth + 20, yOffset + menuHeight + 20);

	// Draw buttons
	btLogIn.draw();
	btSignUp.draw();
	btEmail.draw();
	btPassword.draw();

	// Header
	scene.setPenColor(bw40);
	scene.setBrushColor(bw40);
	scene.rect(xOffset + menuWidth / 2 - lbAuth.size() * 10 / 2, yOffset - 50,
		xOffset + menuWidth / 2 + (lbAuth.size() + 2) * 10 / 2, yOffset - 50 + 27);
	scene.text((wchar_t*)lbAuth.c_str(), xOffset + menuWidth / 2 - lbAuth.size() * 10 / 2, yOffset - 50, 200, 50, 10, 27, 0, bw255, bw40);
	scene.setPenColor(bw60);
	scene.boundingBox(xOffset + menuWidth / 2 - lbAuth.size() * 10 / 2, yOffset - 50,
		xOffset + menuWidth / 2 + (lbAuth.size() + 2) * 10 / 2, yOffset - 50 + 27);

	// Fields label
	scene.text((wchar_t*)lbEmail.c_str(), xOffset, yOffset, inBtOffsetX, 20, 7, 16, 0, bw255, bw40);
	scene.text((wchar_t*)LbPassword.c_str(), xOffset, yOffset + 30, inBtOffsetX, 20, 7, 16, 0, bw255, bw40);
	
	// Log in label
	scene.text((wchar_t*)lbLogIn.c_str(), xOffset + menuWidth / 2 - (lbLogIn.size() / 2) * 7, yOffset + 90,
		100, 20, 7, 16, 0, bw255, btLogIn.getCurrentFillColor());

	// Sign up labbel 
	scene.text((wchar_t*)lbSingUp.c_str(), xOffset + (menuWidth / 2) - (lbSingUp.size() / 2) * 7, yOffset + 115,
		150, 20, 7, 16, 0, bw100, btSignUp.getCurrentFillColor());


	// LogInfo label
	if (lbLogInfo.size()) {
		scene.setBrushColor(bw40);
		scene.setPenColor(bw60);
		scene.rect(xOffset - 20, yOffset + menuHeight + 50, xOffset + menuWidth + 20, yOffset + menuHeight + 120);
		scene.text((wchar_t*)lbLogInfo.c_str(), xOffset, yOffset + menuHeight + 50 + 10, menuWidth, 50, 7, 16, 0, RGB(255, 100, 100), bw40);
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
		} catch (const std::exception&e) {
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
	static std::wstring lbEmail(L"Ел. почта");
	static std::wstring lbAdress(L"Адресс");
	static std::wstring lbCancel(L"Отменить");
	static std::wstring lbSignUp(L"Зарегестрироваться");
	
	// Buttons defines
	static UIHelper::InputButton btFirstName(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btSecondName(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btAge(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::Button btMale(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::Button btFemale(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btPhoneNumber(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btEmail(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btAdress(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::Button btSignUp(scene, 0, 0, 0, 0, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::Button btCancel(scene, 0, 0, 0, 0, bw40, bw40, bw40, bw40, btPressedCol, btPressedCol);

	// Menu shape defines
	static int menuWidth = 400;
	static int menuHeight = 290;
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
		
		btEmail.text.clear();
		btEmail.wtext.clear();
		
		btAdress.text.clear();
		btAdress.wtext.clear();
		
		isFemale = false;
		isMale = false;
	}



	// Begin painting
	scene.beginPaint();

	// Filling custom bgColor
	scene.setBrushColor(RGB(30, 32, 34));
	scene.setPenColor(RGB(30, 32, 34));
	scene.rect(0, 0, scene.width, scene.height);

	// Filling menu
	scene.setBrushColor(bw40);
	scene.setPenColor(bw60);
	scene.rect(xOffset - 20, yOffset - 20, xOffset + menuWidth + 20, yOffset + menuHeight + 20);


	//		 Labels draw
	// SignUp message drawing
	scene.setPenColor(bw40);
	scene.setBrushColor(bw40);
	scene.rect(xOffset + menuWidth / 2 - ((lbSignUpAsk.size() + 1) * 10 / 2), yOffset - 27 / 2 - 20,
		xOffset + menuWidth / 2 + ((lbSignUpAsk.size() + 1) * 10 / 2), yOffset + 27 / 2 - 20);

	scene.text((wchar_t*)lbSignUpAsk.c_str(), xOffset + menuWidth / 2 - ((lbSignUpAsk.size() + 1) * 10 / 2), yOffset - 27 / 2 - 20,
		600, 27, 10, 27, 0, bw255, bw40);

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
	btEmail.setShape(xOffset + xLbOffset, yOffset + 20 + 150, menuWidth - xLbOffset, 20);
	btAdress.setShape(xOffset + xLbOffset, yOffset + 20 + 180, menuWidth - xLbOffset, 20);
	btSignUp.setShape(xOffset, yOffset + 20 + 240, menuWidth, 20);
	btCancel.setShape(xOffset, yOffset + 20 + 265, menuWidth, 20);


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
		btMale.setFillColor(bw50);
		btMale.setOutlineColor(bw50);
		btMale.setHoverFillColor(bw60);
		btMale.setHoverOutlineColor(bw60);
	}
	if (isFemale) {
		btFemale.setFillColor(btPressedCol);
		btFemale.setOutlineColor(btPressedCol);
		btFemale.setHoverFillColor(btPressedCol);
		btFemale.setHoverOutlineColor(btPressedCol);
	} else {
		btFemale.setFillColor(bw50);
		btFemale.setOutlineColor(bw50);
		btFemale.setHoverFillColor(bw60);
		btFemale.setHoverOutlineColor(bw60);
	}

	// Drawing buttons
	btFirstName.draw();
	btSecondName.draw();
	btAge.draw();
	btMale.draw();
	btFemale.draw();
	btPhoneNumber.draw();
	btEmail.draw();
	btAdress.draw();
	btSignUp.draw();
	btCancel.draw();


	// Other labels draw
	scene.text((wchar_t*)lbFirstName.c_str(), xOffset, yOffset + 20, 200, 20, 7, 16, 0, bw255, bw40);
	scene.text((wchar_t*)lbSecondName.c_str(), xOffset, yOffset + 20 + 30, 200, 20, 7, 16, 0, bw255, bw40);
	scene.text((wchar_t*)lbAge.c_str(), xOffset, yOffset + 20 + 60, 200, 20, 7, 16, 0, bw255, bw40);
	scene.text((wchar_t*)lbGender.c_str(), xOffset, yOffset + 20 + 90, 200, 20, 7, 16, 0, bw255, bw40);
	scene.text((wchar_t*)lbMale.c_str(), xOffset + xLbOffset + ((menuWidth - xLbOffset) / 2 - 5 - (lbMale.size() + 1) * 7) / 2, yOffset + 20 + 90, 200, 20, 7, 16, 0, bw255, btMale.getCurrentFillColor());
	scene.text((wchar_t*)lbFemale.c_str(), xOffset + xLbOffset + ((menuWidth - xLbOffset) / 2 + 5) + ((menuWidth - xLbOffset) / 2 - 5 - (lbMale.size() + 1) * 7) / 2, yOffset + 20 + 90, 200, 20, 7, 16, 0, bw255, btFemale.getCurrentFillColor());
	scene.text((wchar_t*)lbPhoneNumber.c_str(), xOffset, yOffset + 20 + 120, 200, 20, 7, 16, 0, bw255, bw40);
	scene.text((wchar_t*)lbEmail.c_str(), xOffset, yOffset + 20 + 150, 200, 20, 7, 16, 0, bw255, bw40);
	scene.text((wchar_t*)lbAdress.c_str(), xOffset, yOffset + 20 + 180, 200, 20, 7, 16, 0, bw255, bw40);
	scene.text((wchar_t*)lbSignUp.c_str(), xOffset + (menuWidth - (lbSignUp.size() + 1) * 7) / 2, yOffset + 20 + 240, 200, 20, 7, 16, 0, bw255, btSignUp.getCurrentFillColor());
	scene.text((wchar_t*)lbCancel.c_str(), xOffset + (menuWidth - (lbCancel.size() + 1) * 7) / 2, yOffset + 20 + 265, 200, 20, 7, 16, 0, bw100, btCancel.getCurrentFillColor());


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
	if (!btEmail.text.size()) {
		scene.ellipse(xOffset + menuWidth + 5, yOffset + 25 + 150, xOffset + menuWidth + 15, yOffset + 35 + 150);
		fieldsNonZero = false;
	}
	if (!btAdress.text.size()) {
		scene.ellipse(xOffset + menuWidth + 5, yOffset + 25 + 180, xOffset + menuWidth + 15, yOffset + 35 + 180);
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
	btEmail.getInput();
	btAdress.getInput();

	// Trying to register
	if (btSignUp.isPressed() && fieldsNonZero) {
		User u;

		// Logic here
		u.setID("NOT A NULL :)");
		return u;
	}

	// Breaking register mode
	if (btCancel.isPressed()) {
		User u;
		u.setID("cancel");
		return u;
	}

	return User();
}

void drawOptionsMenu(Scene& scene, DataBase& db, User& user) {

	scene.beginPaint();

	scene.setBrushColor(bw100);
	scene.setPenColor(bw100);
	scene.rect(0, 0, 100, 100);
	scene.endPaint();

}

void drawTransferMenu(Scene& scene, DataBase& db, User& user, User& target) {

}
