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
	std::string getReceiverBankCID();
	float getAmount();
	float getCommission();
	std::string getPurpose();
	DateTime& transactionTime();

	void setTransactionID(int transaction_ID);
	void setSenderBankCID(std::string sender_bank_CID);
	void setReceiverBankCID(std::string reciever_bank_CID);
	void setAmount(float amount);
	void setCommission(float commission);
	void setPurpose(std::string purpose);

	std::string toString();
};

