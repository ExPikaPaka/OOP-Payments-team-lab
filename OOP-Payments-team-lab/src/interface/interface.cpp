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
std::string drawAuth(Scene& scene);
void drawAddUser(Scene& scene, std::string hash);

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


	bool authenticated = false;
	std::string hash = "";

	while (GetMessage(&msg, NULL, 0, 0)) {
		if (msg.message == WM_QUIT) {
			break;
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (!authenticated) {
			hash = drawAuth(scene);
			authenticated = hash.size() ? true : false;
		}

		if (authenticated) {
			drawAddUser(scene, hash);
		}
		
	}	
}


void drawAddUser(Scene& scene, std::string hash) {
	// Text defines
	static std::wstring lbSave(L"Сохранить");
	static std::wstring lbLog(L"Log:");
	static std::wstring lbLogInfo;
	static std::wstring lbID(L"ID код");
	static std::wstring lbFirstName(L"Имя");
	static std::wstring lbSecondName(L"Фамилия");
	static std::wstring lbAge(L"Возраст");
	static std::wstring lbGender(L"Пол");
	static std::wstring lbPhoneNumber(L"Тел. номер");
	static std::wstring lbEmail(L"Ел. почта");
	static std::wstring lbAddress(L"Адресс");


	// Scene elements
	static UIHelper::Button btSave(scene, 450, 10, 20, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btID(scene, 110, 10, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btFirstName(scene, 110, 40, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btSecondName(scene, 110, 70, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btAge(scene, 110, 100, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btGender(scene, 110, 130, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btPhoneNumber(scene, 110, 160, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btEmail(scene, 110, 190, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	static UIHelper::InputButton btAddress(scene, 110, 220, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);


	// Begin scene drawing
	scene.beginPaint();

	scene.text((wchar_t*)lbID.c_str(), 10, 10, 100, 20, 7, 16, 0, bw255, bgCol);
	scene.text((wchar_t*)lbFirstName.c_str(), 10, 40, 100, 20, 7, 16, 0, bw255, bgCol);
	scene.text((wchar_t*)lbSecondName.c_str(), 10, 70, 100, 20, 7, 16, 0, bw255, bgCol);
	scene.text((wchar_t*)lbAge.c_str(), 10, 100, 100, 20, 7, 16, 0, bw255, bgCol);
	scene.text((wchar_t*)lbGender.c_str(), 10, 130, 100, 20, 7, 16, 0, bw255, bgCol);
	scene.text((wchar_t*)lbPhoneNumber.c_str(), 10, 160, 100, 20, 7, 16, 0, bw255, bgCol);
	scene.text((wchar_t*)lbEmail.c_str(), 10, 190, 100, 20, 7, 16, 0, bw255, bgCol);
	scene.text((wchar_t*)lbAddress.c_str(), 10, 220, 100, 20, 7, 16, 0, bw255, bgCol);
	scene.text((wchar_t*)lbSave.c_str(), 350, 10, 100, 20, 7, 16, 0, bw255, bgCol);

	scene.setPenColor(bw50);
	scene.setBrushColor(bw50);
	scene.rect(10, 250, 10 + 300, 250 + 100);
	scene.text((wchar_t*)lbLog.c_str(), 15, 250, 100, 20, 7, 16, 0, bw255, bw50);
	scene.text((wchar_t*)lbLogInfo.c_str(), 15, 270, 300, 80, 7, 16, 0, bw255, bw50);

	btID.draw();
	btFirstName.draw();
	btSecondName.draw();
	btAge.draw();
	btGender.draw();
	btPhoneNumber.draw();
	btEmail.draw();
	btAddress.draw();

	btSave.draw();

	// End scene drawing
	scene.endPaint();



	btID.getInput();
	btFirstName.getInput();
	btSecondName.getInput();
	btAge.getInput();
	btGender.getInput();
	btPhoneNumber.getInput();
	btEmail.getInput();
	btAddress.getInput();

	if (btSave.isPressed()) {
		try {
			User u;
			u.setID(btID.text);
			u.setFirstName(btFirstName.text);
			u.setSecondName(btSecondName.text);
			u.setAge(std::stoi(btAge.text));
			u.setGender(btGender.text);
			u.setPhoneNumber(btPhoneNumber.text);
			u.setEmail(btEmail.text);
			u.setAddress(btAddress.text);
			u.setBalance(0);
			u.setHash(hash);

			std::cout << u.getHash() << '\n';
			DataBase db;
			db.loadDB("res/DB");
			db.loadAllUsers();

			db.addUser(u);

			db.saveAllUsers();
			
			lbLogInfo = L"Success";
		} catch (const std::exception& e) {
			DateTime tmNow;
			std::cout << "[" << tmNow.toString() << "] Log: " << e.what() << '\n';

			std::string tmp(e.what());
			lbLogInfo = std::wstring(tmp.begin(), tmp.end());
		}
	}
}

// Auth menu. Returns true if user Authenticated
std::string drawAuth(Scene& scene) {
	// Text defines
	static std::wstring lbAuth(L"  Авторизация  ");
	static std::wstring lbEmail(L"Почта");
	static std::wstring LbPassword(L"Пароль");
	static std::wstring lbLogIn(L"Войти");
	static std::wstring lbSingUp(L"Зарегистрироваться");
	static std::wstring lbLogInfo;

	bool fieldsNonZero = true;
	

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

	btLogIn.setX(xOffset);
	btLogIn.setY(yOffset + 90);
	btLogIn.setW(menuWidth);
	btLogIn.setH(20);

	btSignUp.setX(xOffset);
	btSignUp.setY(yOffset + 90 + 25);
	btSignUp.setW(menuWidth);
	btSignUp.setH(20);
	
	btEmail.setX(xOffset + inBtOffsetX);
	btEmail.setY(yOffset);
	btEmail.setW(menuWidth - inBtOffsetX);
	btEmail.setH(20);
	
	btPassword.setX(xOffset + inBtOffsetX);
	btPassword.setY(yOffset + 30);
	btPassword.setW(menuWidth - inBtOffsetX);
	btPassword.setH(20);



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
		150, 20, 7, 16, 0, bw140, btSignUp.getCurrentFillColor());


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

			DataBase db;
			db.loadDB("res/DB");
			db.loadAllUsers();

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
				std::cout << "User hash: " << u.getHash() << '\n';

				lbLogInfo = L"Неправильный пароль!";
				if (hash == u.getHash()) {
					lbLogInfo = L"С возвращением!";
					return hash;
				}
			}

		}

	}

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
				std::cout << "User hash: " << u.getHash() << '\n';


				// Implement logic here
				return hash;
			}
		}
	}
	return std::string();
}
