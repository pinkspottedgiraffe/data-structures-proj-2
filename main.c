/*Stephania Kostaki A.M.:1115201600082*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Session.h"


void print_options(){
	printf("\n1.SessionNewTab \n2.SessionTabShow \n3.SessionTabNext \n4.SessionTabPrev \n5.SessionTabMoveLeft \n");
	printf("6.SessionTabMoveRight \n7.SessionNewOpeningAddress \n8.SessionShowOpeningAddress \n9.SessionSiteNext \n10.SessionSitePrev \n");
	printf("11.SessionSiteShow \n12.SessionTabClose \n13.SessionClose \n14.SessionNewAddress \nInput 1-14 for your choice or -1 for Exit\n");
}

int main(int argc, char *argv[]) {
	InfoSessionPtr 	MySession=NULL;
	char OpeningAddress[100];
	int option, error;
	printf("Enter opening address: \n");
	scanf("%s",OpeningAddress);
	MySession=SessionNew(OpeningAddress);
	print_options();
	scanf("%d",&option);
	while(option!=-1){
		switch(option){
			case 1:
				SessionNewTab(MySession, &error);
				break;
			case 2:
				SessionTabShow(MySession);
				break;
			case 3:
				SessionTabNext(MySession);
				break;
			case 4:
				SessionTabPrev(MySession);
				break;
			case 5:
				SessionTabMoveLeft(MySession);
				break;
			case 6:
				SessionTabMoveRight(MySession);
				break;
			case 7:
				printf("Enter new opening address:");
				scanf("%s",OpeningAddress);
				SessionNewOpeningAddress(MySession, OpeningAddress);
				break;
			case 8:
				SessionShowOpeningAddress(MySession);
				break;
			case 9:
				SessionSiteNext(MySession);
				break;
			case 10:
				SessionSitePrev(MySession);
				break;
			case 11:
				SessionSiteShow(MySession);
				break;
			case 12:
				SessionTabClose(&MySession);
				break;
			case 13:
				SessionClose(&MySession);
				break;
			case 14:
				printf("Enter a site address:");
				scanf("%s",OpeningAddress);
				SessionNewAddress(MySession, OpeningAddress);
				break;
			default: 
				printf("Wrong option!\n");
				break;	
				
		}
		print_options();
		scanf("%d",&option);
	}
	return 0;
}
