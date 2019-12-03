/*
 * main.c
 *
 *  Created on: Dec 2, 2019
 *      Author: Ahmed Osama
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "payment.h"

char res[2];

int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	while(1){
			gu8_accountFlag = NOT_FOUND;
			gu8_amountFlag = NOT_VALID;
			gu8_expDateFlag = EXPIRED;
			gu8_balanceFlag = BAL_NOT_APPROVED;

			fillCardData(&data);
			fillTerminalData(&data);
			checkAmount(&data);
			if(gu8_amountFlag == VALID){
				printf("Verifying Data from the server…\n");
				saveTransactionIntoServer(&data);
				if(gu8_accountFlag == FOUND){
					if(gu8_balanceFlag == BAL_APPROVED){
						printf("The transaction is APPROVED\n");
					}
					if(gu8_balanceFlag == BAL_NOT_APPROVED){
						printf("The transaction is DECLINED\n");
					}
					if(gu8_amountFlag == NOT_VALID){
						printf("Transaction is DECLINED\n");
					}
					if(gu8_expDateFlag == EXPIRED){
						printf("The transaction is DECLINED\n");
					}
				}
				else{
					printf("The transaction is DECLINED\n");
				}
			}else{
				printf("The transaction is DECLINED\n");
			}

			printf("Do you want to continue (y/n)?:\n");
			n++;
			gets(res);
			if(strcmp(res, "y") == 0)
				continue;
			else
				break;
	}

	return 0;
}
