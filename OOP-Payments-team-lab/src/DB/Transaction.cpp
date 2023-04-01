#include "Transaction.h"

Transaction::Transaction() {
    transaction_ID = -1;
    sender_bank_CID = "null";
    reciever_bank_CID = "null";
    amount = -1;
    commission = -1;
    purpose = "null";
    transaction_time = DateTime();
}

Transaction::~Transaction() {
}

int Transaction::getTransactionID() {
    return transaction_ID;
}

std::string Transaction::getSenderBankCID() {
    return sender_bank_CID;
}

std::string Transaction::getRecieverBankCID() {
    return reciever_bank_CID;
}

float Transaction::getAmout() {
    return amount;
}

float Transaction::getCommission() {
    return commission;
}

std::string Transaction::getPurpose() {
    return purpose;
}

DateTime Transaction::getTransactionTime() {
    return transaction_time;
}

void Transaction::setTransactionID(int transaction_ID) {
    this->transaction_ID = transaction_ID;
}

void Transaction::setSenderBankCID(std::string sender_bank_CID) {
    this->sender_bank_CID = sender_bank_CID;
}

void Transaction::setRecieverBankCID(std::string reciever_bank_CID) {
    this->reciever_bank_CID = reciever_bank_CID;
}

void Transaction::setAmout(float amount) {
    this->amount = amount;
}

void Transaction::setCommission(float commission) {
    this->commission = commission;
}

void Transaction::setPurpose(std::string purpose) {
    this->purpose = purpose;
}

void Transaction::setTransactionTime(DateTime time) {
    transaction_time = time;
}
