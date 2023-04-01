#pragma once
#include <string>
#include "..\DateTime\DateTime.h"

class Transaction {
protected:
	int transaction_ID;
	std::string sender_bank_CID;
	std::string reciever_bank_CID;
	float amount;
	float commission;
	std::string purpose;
	DateTime transaction_time;

public:
	Transaction();
	~Transaction();
	int getTransactionID();
	std::string getSenderBankCID();
	std::string getRecieverBankCID();
	float getAmout();
	float getCommission();
	std::string getPurpose();
	DateTime getTransactionTime();

	void setTransactionID(int transaction_ID);
	void setSenderBankCID(std::string sender_bank_CID);
	void setRecieverBankCID(std::string reciever_bank_CID);
	void setAmout(float amount);
	void setCommission(float commission);
	void setPurpose(std::string purpose);
	void setTransactionTime(DateTime time);
};

