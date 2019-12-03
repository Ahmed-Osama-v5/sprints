/*
 * payment.h
 *
 *  Created on: Dec 2, 2019
 *      Author: Ahmed Osama
 */

#ifndef PAYMENT_H_
#define PAYMENT_H_

/*- INCLUDES -----------------------------------------------*/
#include <stdint.h>

/**/
extern uint8_t gu8_amountFlag;
extern uint8_t gu8_expDateFlag;
extern uint8_t gu8_accountFlag;
extern uint8_t gu8_balanceFlag;
extern uint32_t tranAmnt;
extern int n;

/*- CONSTANTS ----------------------------------------------*/

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/
typedef enum EN_transStat
{
	DECLINED,APPROVED
}EN_transStat;

typedef enum EN_amountFlagStat
{
	VALID,NOT_VALID
}EN_amountFlagStat;

typedef enum EN_expDateFlagStat
{
	EXPIRED,NOT_EXPIRED
}EN_expDateFlagStat;

typedef enum EN_accountFlagStat
{
	FOUND,NOT_FOUND
}EN_accountFlagStat;

typedef enum EN_balanceFlagStat
{
	BAL_APPROVED,BAL_NOT_APPROVED
}EN_balanceFlagStat;

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct ST_cardData
{
	unsigned char cardHolderName[25];
	unsigned char primaryAccountNumber[19];
	unsigned char cardExpirationDate[6];
}ST_cardData;

typedef struct ST_terminalData
{
	unsigned char transAmount[8];
	unsigned char maxTransAmount[8];
	unsigned char transactionDate[11];
}ST_terminalData;

typedef struct ST_serverData
{
	EN_transStat transactionStatus;
	unsigned int receiptReferenceNumber;
}ST_serverData;

typedef struct ST_accountBalance
{
	unsigned char balance[8];
	unsigned char primaryAccountNumber[19];
}ST_accountBalance;

typedef struct ST_transaction{
	ST_cardData cardHolderData;
	ST_terminalData transData;
	ST_serverData transResponse;
}ST_transaction;

extern ST_transaction data;
extern ST_accountBalance accountList[10];

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* It fills the card data structure into the ST_transaction structure */
void fillCardData(ST_transaction *transaction);
/*
 * It reads the amount.
 * It checks if the amount > maximum transaction Amount (5000.00)
 * Then it saves the response as DECLINED and prints ”The transaction is DECLINED”
 * Else do nothing.
 */

void checkAmount(ST_transaction *transaction);
/*
 * It fills transaction amount, maximum transaction amount and expiry date in
 * the ST_transaction structure
 */

void fillTerminalData(ST_transaction *transaction);
/*
 * Reads the expiry and transaction dates from the transaction structure.
 * It checks if the expiry date > than transaction date
 * Then saves the response as DECLINED and prints ”The transaction is DECLINED”
 * Else do nothing.
 */

void checkExpiryDate(ST_transaction *transaction);
/*
 * It checks for the expiry date.
 * It checks for balance.
 * Saves the transaction data into the server array
 */

void saveTransactionIntoServer(ST_transaction *transaction);
/*
 * It reads the primary account number from the transaction structure.
 * It searches for the primary account number into the account/balance array.
 * If it is not exist- Then saves the response as DECLINED and print ”The transaction is DECLINED”
 * Else it checks if the transaction amount > account balance
 * Then saves the response as DECLINED and print ”The transaction is DECLINED”
 * Else saves the response as APPROVED and print ”The transaction is APPROVED”
*/
void checkBalance(ST_transaction *transaction);

/*
 * Converts array of characters to int
 */
uint8_t expYearToInt(unsigned char arr[]);
uint8_t expMonthToInt(unsigned char arr[]);
uint8_t transYearToInt(unsigned char arr[]);
uint8_t transMonthToInt(unsigned char arr[]);
/*
 * Converts array of characters to float
 */
float strToFloat(unsigned char str[]);

#endif /* PAYMENT_H_ */
