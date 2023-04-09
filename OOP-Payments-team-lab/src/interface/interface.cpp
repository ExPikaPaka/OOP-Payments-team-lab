#include <iostream>
#include <Windows.h>
#include <fstream>
#include "..\DB\DataBase.h"
#include "Timer/Timer.h"
#include "WindowHelper/Scene.h"
#include "WindowHelper/WindowHelper.h"
#include "WindowHelper/UIHelper/Button.h"
#include "WindowHelper/UIHelper/InputButton.h"


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




	// Color defines
	COLORREF bgCol = RGB(30, 30, 30);
	COLORREF bw50 = RGB(50, 50, 50);
	COLORREF bw60 = RGB(60, 60, 60);
	COLORREF bw255 = RGB(255, 255, 255);
	COLORREF btPressedCol = RGB(60, 70, 90);

	/*	std::string ID;
	std::string bank_CID;
	std::string	first_name;
	std::string second_name;
	int age;
	std::string gender;
	std::string phone_number;
	std::string email;
	std::string address;*/
	// Text defines
	std::wstring lbSave(L"Сохранить");
	std::wstring lbLog(L"Log:");
	std::wstring lbLogInfo;
	std::wstring lbID(L"ID код");
	std::wstring lbFirstName(L"Имя");
	std::wstring lbSecondName(L"Фамилия");
	std::wstring lbAge(L"Возраст");
	std::wstring lbGender(L"Пол");
	std::wstring lbPhoneNumber(L"Тел. номер");
	std::wstring lbEmail(L"Ел. почта");
	std::wstring lbAddress(L"Адресс");



	// Creating scene
	Scene scene(window, msg);
	scene.backgroundColor = bgCol;


	// Scene elements
	UIHelper::Button btSave(scene, 450, 10, 20, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	UIHelper::InputButton btID(scene, 110, 10, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	UIHelper::InputButton btFirstName(scene, 110, 40, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	UIHelper::InputButton btSecondName(scene, 110, 70, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	UIHelper::InputButton btAge(scene, 110, 100, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	UIHelper::InputButton btGender(scene, 110, 130, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	UIHelper::InputButton btPhoneNumber(scene, 110, 160, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	UIHelper::InputButton btEmail(scene, 110, 190, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);
	UIHelper::InputButton btAddress(scene, 110, 220, 200, 20, bw50, bw50, bw60, bw60, btPressedCol, btPressedCol);

	while (GetMessage(&msg, NULL, 0, 0)) {
		if (msg.message == WM_QUIT) {
			break;
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

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
		/*	std::cout << "btID: " << btID.text << '\n';
			std::cout << "btFirstName: " << btFirstName.text << '\n';
			std::cout << "btSecondName: " << btSecondName.text << '\n';
			std::cout << "btAge: " << btAge.text << '\n';
			std::cout << "btGender: " << btGender.text << '\n';
			std::cout << "btPhoneNumber: " << btPhoneNumber.text << '\n';
			std::cout << "btEmail: " << btEmail.text << '\n';
			std::cout << "btAddress: " << btAddress.text << '\n';*/


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

				DataBase db;
				db.loadDB("res/DB");
				db.loadAllUsers();

				db.addUser(u);

				db.saveAllUsers();
			} catch (const std::exception&e) {
				DateTime tmNow;
				std::cout << "[" << tmNow.toString() << "] Log: " << e.what() << '\n';
				
				std::string tmp(e.what());
				lbLogInfo = std::wstring(tmp.begin(), tmp.end());
			}
		}
	}	
}