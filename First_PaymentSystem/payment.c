/*
 * payment.c
 *
 *  Created on: Dec 2, 2019
 *      Author: Ahmed Osama
 */

/*- INCLUDES ----------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "payment.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

/*- GLOBAL STATIC VARIABLES -------------------------------*/
const unsigned char guc_maxAmount[] = "5000.00";
const uint16_t today_date = 1219;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/
uint8_t gu8_amountFlag = VALID;
uint8_t gu8_expDateFlag = NOT_EXPIRED;
uint8_t gu8_accountFlag = NOT_FOUND;
uint8_t gu8_balanceFlag = BAL_APPROVED;
int n = 0;

ST_transaction data;
uint32_t tranAmnt;

ST_accountBalance accountList[10] = {
		{"0100.00", "123456789"},
		{"6000.00", "234567891"},
		{"3250.25", "567891234"},
		{"1500.12", "456789123"},
		{"0500.00", "258649173"},
		{"2100.00", "654823719"},
		{"0000.00", "971362485"},
		{"0001.00", "793148625"},
		{"0010.12", "123123456"},
		{"0000.55", "456789321"}
};

ST_serverData serverDataList[255];
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*
 * It reads the amount.
 * It checks if the amount > maximum transaction Amount (5000.00)
 * Then it saves the response as DECLINED and prints ”The transaction is DECLINED”
 * Else do nothing.
 */
void checkAmount(ST_transaction *transaction){
	float tranVar = lrint(strToFloat(transaction->transData.transAmount) * 100);
	tranAmnt = (uint32_t)tranVar;

	float maxVar = lrint(strToFloat(transaction->transData.maxTransAmount) * 100);
	uint32_t maxAmnt = (uint32_t)maxVar;
	if( tranAmnt <= maxAmnt)
		gu8_amountFlag = VALID;
	else
		gu8_amountFlag = NOT_VALID;
}

/*
 * Reads the expiry and transaction dates from the transaction structure.
 * It checks if the expiry date > than transaction date
 * Then saves the response as DECLINED and prints ”The transaction is DECLINED”
 * Else do nothing.
 */
void checkExpiryDate(ST_transaction *transaction){
	uint8_t u8_transYear =  transYearToInt(transaction->transData.transactionDate);
	uint8_t u8_transMonth =  transMonthToInt(transaction->transData.transactionDate);

	uint8_t u8_expYear =  expYearToInt(transaction->cardHolderData.cardExpirationDate);
	uint8_t u8_expMonth =  expMonthToInt(transaction->cardHolderData.cardExpirationDate);


	if(u8_transYear <= u8_expYear){
		if(u8_transMonth <= u8_expMonth){
			gu8_expDateFlag = NOT_EXPIRED;
		}
		else{
			gu8_expDateFlag = EXPIRED;
		}
	}
	else{
		gu8_expDateFlag = EXPIRED;
	}

}

/*
 * It checks for the expiry date.
 * It checks for balance.
 * Saves the transaction data into the server array
 */
void saveTransactionIntoServer(ST_transaction *transaction){
	serverDataList->receiptReferenceNumber = n;
	checkExpiryDate(transaction);
	if(gu8_expDateFlag == NOT_EXPIRED){
		checkBalance(transaction);
		if(gu8_accountFlag == FOUND){
			if(gu8_balanceFlag == BAL_APPROVED){
					serverDataList->transactionStatus = APPROVED;
				}
				else{
					serverDataList->transactionStatus = DECLINED;
				}
		}
		else{
			serverDataList->transactionStatus = DECLINED;
		}

	}
	else{
		serverDataList->transactionStatus = DECLINED;
	}
}

/*
 * It reads the primary account number from the transaction structure.
 * It searches for the primary account number into the account/balance array.
 * If it is not exist- Then saves the response as DECLINED and print ”The transaction is DECLINED”
 * Else it checks if the transaction amount > account balance
 * Then saves the response as DECLINED and print ”The transaction is DECLINED”
 * Else saves the response as APPROVED and print ”The transaction is APPROVED”
*/
void checkBalance(ST_transaction *transaction){
	int i;
	for(i=0;i<10;i++){
		if(strcmp((char *)transaction->cardHolderData.primaryAccountNumber, (char *)accountList[i].primaryAccountNumber) == 0){
			gu8_accountFlag = FOUND;
			break;
		}
	}
	if(gu8_accountFlag == NOT_FOUND){
		printf("Account not found\n");
	}
	float balanceVar = lrint(strToFloat(accountList[n].balance) * 100);
	uint32_t u32_balance = (uint32_t)balanceVar;
	if(tranAmnt <= u32_balance){
		gu8_balanceFlag = BAL_APPROVED;
	}
	else{
		gu8_balanceFlag = BAL_NOT_APPROVED;
	}
}

/*- APIs IMPLEMENTATION -----------------------------------*/
/* It fills the card data structure into the ST_transaction structure */
void fillCardData(ST_transaction *transaction){
	printf("Please Enter Card Data:\n");
	gets((char *)transaction->cardHolderData.cardHolderName);
	printf("Please Enter the Primary Account Number:\n");
	gets((char *)transaction->cardHolderData.primaryAccountNumber);
	printf("Please card Expiry Date:\n");
	gets((char *)transaction->cardHolderData.cardExpirationDate);
}

/*
 * It fills transaction amount, maximum transaction amount and expiry date in
 * the ST_transaction structure
 */
void fillTerminalData(ST_transaction *transaction){
	/* Getting Terminal data */
	printf("Please Enter Terminal Data:\n");
	printf("Please Enter the transaction Amount:\n");
	gets((char *)transaction->transData.transAmount);
	strcpy((char *)transaction->transData.maxTransAmount, (char *)guc_maxAmount);
	checkAmount(transaction);
	if(gu8_amountFlag == VALID){
		printf("Please Enter transaction Date:\n");
		gets((char *)transaction->transData.transactionDate);
	}
}

/*
 * Converts array of characters to int
 */

uint8_t expYearToInt(unsigned char arr[]){
	uint8_t u8_expDate = 0;
	u8_expDate += (arr[4]-48);
	u8_expDate += (arr[3]-48) * 10;
	return u8_expDate;
}

uint8_t expMonthToInt(unsigned char arr[]){
	uint8_t u8_expDate = 0;
	u8_expDate += (arr[1]-48);
	u8_expDate += (arr[0]-48) * 10;
	return u8_expDate;
}

/*
 * Converts array of characters to int
 */

uint8_t transYearToInt(unsigned char arr[]){
	uint8_t u8_expDate = 0;
	u8_expDate += (arr[9]-48);
	u8_expDate += (arr[8]-48) * 10;
	return u8_expDate;
}

uint8_t transMonthToInt(unsigned char arr[]){
	uint8_t u8_expDate = 0;
	u8_expDate += (arr[4]-48);
	u8_expDate += (arr[3]-48) * 10;
	return u8_expDate;
}

float strToFloat(unsigned char str[]){
	float var = 0.00;
	var = (str[6]-48) / 100.00;
	var += (str[5]-48) / 10.00;
	var += (str[3]-48);
	var += (str[2]-48) * 10.00;
	var += (str[1]-48) * 100.00;
	var += (str[0]-48) * 1000.00;

	return var;
}

