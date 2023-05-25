# OOP-Payments-team-lab
C++ OPP lab - pet project. Theme is bank payments system  
Program allows easily interact with custom test bank system. To use program user must register, or login. 
User has possibility to transfer money to other person via phone number or email, explore transfer menu, 
clear balance, block account.  Every interaction between the user, the program, and the database goes 
through checks for data validity or other errors. In case of occurrence of such, the user is notified by a pop-up window.
Program has 2 localizations - Ukrainian, and Russian.


## Demo:
<img src="https://github.com/ExPikaPaka/OOP-Payments-team-lab/assets/112851715/f413bb6e-c93e-4742-82b9-397d02d51b70" width="400" height="300">
<img src="https://github.com/ExPikaPaka/OOP-Payments-team-lab/assets/112851715/bd34c2ee-01f7-4913-8d34-7578b24cc731" width="400" height="300">
<img src="https://github.com/ExPikaPaka/OOP-Payments-team-lab/assets/112851715/e8003d4b-a0e5-44d6-a67e-b536c23e1c0f" width="400" height="300">
<img src="https://github.com/ExPikaPaka/OOP-Payments-team-lab/assets/112851715/a8c64e28-b185-4132-a353-84b1df16da37" width="400" height="300">
<img src="https://github.com/ExPikaPaka/OOP-Payments-team-lab/assets/112851715/f810fe48-2c47-48ec-b16b-dafb27981d6a" width="400" height="300">
<img src="https://github.com/ExPikaPaka/OOP-Payments-team-lab/assets/112851715/512cc580-c7fc-4456-9b46-26b1d6fca901" width="400" height="300">



## Versions:
* v1.0 Final. 
  * Auth menu
  * Register menu
  * Main menu
  * RU/UA localization

## Changelog:
* 14:35 01.04.2023 \ ExPikaPaka:  
  * Repository pre-configuration

* 21:42 01.04.2023 \ ExPikaPaka:  
  * Added some DB logic  
  * Added DateTime class


* 21:26 02.04.2023 \ ExPikaPaka:
  * Implemented DB class (now it's possible to create and load DB). DB class loads only users, but transactions load and save is not implemented yet.

* 18:31 04.04.2023 \ ExPikaPaka:
  * Full DB implementation.

* 00:54 10.04.2023 \ ExPikaPaka:
  * Added UI classes, and demo which allows to interact with DB via adding new user.
  
* 17:02 10.04.2023 \ ExPikaPaka:
  * Added UI login page and Auth module (Fileds verification not implemented yet)

* 12:09 11.04.2023 \ ExPikaPaka:
  * Implemented log in. Log in page update. 
  * Now is possible to log in with email and password and create a new account. No password stored, only hash. 

* 17:25 19.04.2023 \ ExPikaPaka:
  * Added sign up page.
  * Menu is clickable, but doesn't affect data base (Will be implemented soon).

* 19:51 21.04.2023 \ ExPikaPaka:
  * Full LogIn & SignUp implementation.

* 18:40 27.04.2023 \ ExPikaPaka:
  * Added main menu UI.
  
* 20:20 30.04.2023 \ ExPikaPaka:
  * Final version. v1.0
  * Russian/Ukrainian localization trough #def UA
  * UI improvement
