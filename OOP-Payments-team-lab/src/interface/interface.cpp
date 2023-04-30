#include "interface.h"

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
int main() {
	system("chcp 1251");
	std::wcout.imbue(std::locale(""));
	system("cls");

	// Creating window
	HWND window = 0;
	WindowHelper wh;
	window = wh.initWindow((wchar_t*)L"Name me please and give a logo", 100, 100, 900, 600, WS_OVERLAPPEDWINDOW);
	ShowWindow(window, SW_SHOWNORMAL);

	MSG msg = {};


	// Timer
	Timer tm1;
	tm1.setFPS(30);


	// Verification
	Auth authenticator;


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
	std::string hash;


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
					std::cout << regUser.toString() << '\n';
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

