/*Stephania Kostaki A.M.:1115201600082*/

#include <stdlib.h>
#include <stdio.h>
#include "Session.h"
#include <string.h>

typedef struct TabNode *TabNodePtr;
typedef struct SiteNode *SiteNodePtr;


struct InfoSession {
	TabNodePtr FirstTab;
	TabNodePtr LastTab;
	TabNodePtr CurrTab;
	TabNodePtr AuxTab;
	char* 	  OpeningAddress;
};

struct TabNode {	
	TabNodePtr PrevTab, NextTab;
	SiteNodePtr FirstSite;
	SiteNodePtr CurrSite;
};

struct SiteNode{
	SiteNodePtr PrevSite, NextSite;
	TabNodePtr UpTab;
	char *Address;
};


InfoSessionPtr SessionNew(char * OpeningAddress){
	InfoSessionPtr InfoSession=(InfoSessionPtr)malloc(sizeof(struct InfoSession));		//makes InfoSession node
	InfoSession->OpeningAddress=malloc(strlen(OpeningAddress)+1);						//allocates memory for string of opening address
	strcpy(InfoSession->OpeningAddress,OpeningAddress);									//copies string to the opening address of InfoSession
	TabNodePtr Tab=(TabNodePtr)malloc(sizeof(struct TabNode));							//makes Tab node
	SiteNodePtr Site=(SiteNodePtr)malloc(sizeof(struct SiteNode));						//makes Site node
	InfoSession->FirstTab=Tab;															//FirstTab LastTab and CurrTab pointers point to the Tab
	InfoSession->LastTab=Tab;
	InfoSession->CurrTab=Tab;
	InfoSession->AuxTab=NULL;
	Tab->NextTab=Tab;																	//NextTab and PrevTab pointers of Tab point to Tab
	Tab->PrevTab=Tab;																	//because it is a circular doubly linked list
	Tab->FirstSite=Site;
	Tab->CurrSite=Site; 
	Site->PrevSite=NULL;
	Site->NextSite=NULL;
	Site->UpTab=Tab;
	Site->Address=malloc(strlen(OpeningAddress)+1);
	strcpy(Site->Address,OpeningAddress);
	return InfoSession;
}

void SessionNewTab(InfoSessionPtr InfoSession, int *error){
	if(InfoSession->CurrTab==NULL){										//checks that CurrTab isn't NULL
		return;
	}
	TabNodePtr NewTab=(TabNodePtr)malloc(sizeof(struct TabNode));		//makes new tab and new site
	SiteNodePtr NewSite=(SiteNodePtr)malloc(sizeof(struct SiteNode));
	if(NewTab==NULL){
		*error=1;
		return;
	}
	else if(NewSite==NULL){
		*error=1;
		return;
	}
	else{
		NewTab->NextTab=InfoSession->LastTab->NextTab;			//the NextTab pointer of NewTab points to the NextTab of the LastTab
		NewTab->PrevTab=InfoSession->LastTab;					//the PrevTab pointer of NewTab points to the LastTab
		InfoSession->LastTab->NextTab=NewTab;					//the NextTab pointer of LastTab points to the NewTab
		InfoSession->FirstTab->PrevTab=NewTab;					//the PrevTab pointer of FirstTab points to the NewTab
		InfoSession->LastTab=NewTab;							//the LastTab pointer points to the NewTab
		NewTab->FirstSite=NewSite;								//FirstSite and CurrSite pointers point to the NewSite
		NewTab->CurrSite=NewSite;
		InfoSession->CurrTab=NewTab;							//CurrTab pointer points to the NewTab
		NewSite->UpTab=NewTab;									//UpTab points to the NewTab
		NewSite->PrevSite=NULL;									//PrevSite and NextSite of the NewSite are NULL
		NewSite->NextSite=NULL;
		NewSite->Address=malloc(strlen(InfoSession->OpeningAddress)+1);		
		strcpy(NewSite->Address,InfoSession->OpeningAddress);	//assigns the OpeningAddress to the NewSites address
		
	}
}

void SessionTabShow(InfoSessionPtr InfoSession){
	if(InfoSession->CurrTab==NULL){
		return;
	}
	char* currentaddress;
	currentaddress=InfoSession->CurrTab->CurrSite->Address;		
	printf("%s \n",currentaddress);								//prints the address of the CurrTabs CurrSite
}

void SessionTabNext(InfoSessionPtr InfoSession){
	if(InfoSession->CurrTab==NULL){								
		return;
	}
	InfoSession->CurrTab=InfoSession->CurrTab->NextTab;			//moves the CurrTab pointer one node to the right
}

void SessionTabPrev(InfoSessionPtr InfoSession){
	if(InfoSession->CurrTab==NULL){
		return;
	}
	InfoSession->CurrTab=InfoSession->CurrTab->PrevTab;			//moves the CurrTab pointer one node to the left
}

void SessionTabMoveRight(InfoSessionPtr InfoSession){
	if(InfoSession->CurrTab==NULL){
		return;
	}
	if(InfoSession->CurrTab!=InfoSession->LastTab){
		InfoSession->CurrTab->NextTab->PrevTab=InfoSession->CurrTab->PrevTab;		//the PrevTab pointer of the next tab of the CurrTab points to the PrevTab of the CurrTab
		InfoSession->CurrTab->PrevTab->NextTab=InfoSession->CurrTab->NextTab;		//the NextTab pointer of the previous tab of the CurrTab points to the next tab of the CurrTab
		InfoSession->CurrTab->PrevTab=InfoSession->CurrTab->NextTab;				//the PrevTab pointer of CurrTab points to the next tab of CurrTab
		InfoSession->CurrTab->NextTab=InfoSession->CurrTab->NextTab->NextTab;		//the NextTab pointer of CurrTab points to the next tab of NextTab
		InfoSession->CurrTab->NextTab->PrevTab=InfoSession->CurrTab;				//the PrevTab pointer of the new NextTab points to the CurrTab
		InfoSession->CurrTab->PrevTab->NextTab=InfoSession->CurrTab;				//the NextTab pointer of the new PrevTab points to the CurrTab
	}
}

void SessionTabMoveLeft(InfoSessionPtr InfoSession){
	if(InfoSession->CurrTab==NULL){
		return;
	}
	if(InfoSession->CurrTab!=InfoSession->FirstTab){
		InfoSession->CurrTab->PrevTab->NextTab=InfoSession->CurrTab->NextTab;
		InfoSession->CurrTab->NextTab->PrevTab=InfoSession->CurrTab->PrevTab;
		InfoSession->CurrTab->NextTab=InfoSession->CurrTab->PrevTab;
		InfoSession->CurrTab->PrevTab=InfoSession->CurrTab->PrevTab->PrevTab;
		InfoSession->CurrTab->PrevTab->NextTab=InfoSession->CurrTab;
		InfoSession->CurrTab->NextTab->PrevTab=InfoSession->CurrTab;
	}
}

void SessionNewOpeningAddress(InfoSessionPtr InfoSession, char* NewAddress){
	if(InfoSession->CurrTab==NULL){
		return;
	}
	free(InfoSession->OpeningAddress);							//frees the previous OpeningAddress  
	InfoSession->OpeningAddress=malloc(strlen(NewAddress)+1);	//allocates memory for the new address
	strcpy(InfoSession->OpeningAddress,NewAddress);				//copies the NewAddress to the OpeningAddress of InfoSession
}

void SessionShowOpeningAddress(InfoSessionPtr InfoSession){
	if(InfoSession->CurrTab==NULL){
		return;
	}
	printf("%s",InfoSession->OpeningAddress);					//prints the OpeningAddress of InfoSession
}

void SessionSiteNext(InfoSessionPtr InfoSession){
	if(InfoSession->CurrTab==NULL){
		return;
	}
	if(InfoSession->CurrTab->CurrSite->NextSite!=NULL){
		InfoSession->CurrTab->CurrSite=InfoSession->CurrTab->CurrSite->NextSite;	//the CurrSite pointer points to the next node
	}
}

void SessionSitePrev(InfoSessionPtr InfoSession){
	if(InfoSession->CurrTab==NULL){
		return;
	}
	if(InfoSession->CurrTab->CurrSite->PrevSite!=NULL){
		InfoSession->CurrTab->CurrSite=InfoSession->CurrTab->CurrSite->PrevSite;	//the CurrSite pointer points to the previous node
	}
}

void SessionSiteShow(InfoSessionPtr InfoSession){ 
	if(InfoSession->CurrTab==NULL){
		return;
	}
	printf("%s",InfoSession->CurrTab->CurrSite->Address);			//prints the address of the CurrSite of the CurrTab
}

void SessionTabClose(InfoSessionPtr *InfoSession){
	if((*InfoSession)->CurrTab==NULL){
		return;
	}
	SiteNodePtr temp;												
	SiteNodePtr next;
	TabNodePtr nexttab;
	temp=(*InfoSession)->CurrTab->FirstSite;						//temp pointer points to the FirstSite of the CurrTab
	while(temp!=NULL){												//frees all the sites of CurrTab
		next=temp->NextSite;
		free(temp->Address);
		free(temp);
		temp=next;
	}
	if((*InfoSession)->FirstTab==(*InfoSession)->LastTab && (*InfoSession)->FirstTab!=NULL){	//if there is only one Tab node left
		free((*InfoSession)->FirstTab);															//it frees it and it frees the InfoSession
		(*InfoSession)->FirstTab=NULL;
		(*InfoSession)->LastTab=NULL;
		(*InfoSession)->CurrTab=NULL;
		free((*InfoSession)->OpeningAddress);
		free((*InfoSession));
	}
	else if((*InfoSession)->FirstTab==(*InfoSession)->CurrTab){							//if the first tab needs to be freed
		nexttab=(*InfoSession)->CurrTab->NextTab;										//it frees it and moves the FirstTab pointer to the next tab
		(*InfoSession)->CurrTab->PrevTab->NextTab=(*InfoSession)->CurrTab->NextTab;
		(*InfoSession)->CurrTab->NextTab->PrevTab=(*InfoSession)->CurrTab->PrevTab;
		free((*InfoSession)->CurrTab);
		(*InfoSession)->CurrTab=nexttab;
		(*InfoSession)->FirstTab=nexttab;
	}
	else if((*InfoSession)->LastTab==(*InfoSession)->CurrTab){							//if the last tab needs to be freed
		nexttab=(*InfoSession)->CurrTab->NextTab;										//it frees it and moves the LastTab pointer to the previous tab of the CurrTab
		(*InfoSession)->CurrTab->PrevTab->NextTab=(*InfoSession)->CurrTab->NextTab;
		(*InfoSession)->CurrTab->NextTab->PrevTab=(*InfoSession)->CurrTab->PrevTab;
		free((*InfoSession)->CurrTab);
		(*InfoSession)->CurrTab=nexttab;
		(*InfoSession)->LastTab=nexttab->PrevTab;
	}
	else{																				
		nexttab=(*InfoSession)->CurrTab->NextTab;
		(*InfoSession)->CurrTab->PrevTab->NextTab=(*InfoSession)->CurrTab->NextTab;		
		(*InfoSession)->CurrTab->NextTab->PrevTab=(*InfoSession)->CurrTab->PrevTab;
		free((*InfoSession)->CurrTab);
		(*InfoSession)->CurrTab=nexttab;												//the CurrTab points to the next tab
	}
}

void SessionClose(InfoSessionPtr *InfoSession){
	while((*InfoSession)->CurrTab!=NULL){					//loop until the CurrTab is NULL which frees each CurrTab and then
		SessionTabClose(InfoSession);						//goes to the next one
	}
	
}

void SessionNewAddress(InfoSessionPtr InfoSession, char *Address){
	if(InfoSession->CurrTab==NULL){
		return;
	}
	SiteNodePtr NewSite=(SiteNodePtr)malloc(sizeof(struct SiteNode));
	if(InfoSession->CurrTab->CurrSite->NextSite==NULL){				//if the CurrSite of the CurrTab doesn't have a next site
	 	NewSite->Address=malloc(strlen(Address)+1);					//it makes a new site as the next site
	 	strcpy(NewSite->Address,Address);
	 	InfoSession->CurrTab->CurrSite->NextSite=NewSite;
	 	NewSite->NextSite=NULL;
	 	NewSite->PrevSite=InfoSession->CurrTab->CurrSite;
	 	NewSite->UpTab=InfoSession->CurrTab;						//the UpTab pointer of the NewSite points to the CurrTab
	 	InfoSession->CurrTab->CurrSite=NewSite;						//the CurrSite pointer points to the NewSite
	}
	else{															//if the CurrSite of the CurrTab has a next site
		while(InfoSession->CurrTab->CurrSite->NextSite!=NULL){		//it frees all of the sites after the CurrSite
			SiteNodePtr nextsite, temp;
			nextsite=InfoSession->CurrTab->CurrSite->NextSite;
			temp=nextsite->NextSite;
			free(nextsite->Address);								//frees the address string
			free(nextsite);											//frees the node
			nextsite=temp;
			InfoSession->CurrTab->CurrSite->NextSite=nextsite;
			if(nextsite!=NULL){
				nextsite->PrevSite=InfoSession->CurrTab->CurrSite;
			}
		}
		NewSite->Address=malloc(strlen(Address)+1);					//and then it makes the new site as the next site
	 	strcpy(NewSite->Address,Address);
	 	InfoSession->CurrTab->CurrSite->NextSite=NewSite;
	 	NewSite->NextSite=NULL;
	 	NewSite->PrevSite=InfoSession->CurrTab->CurrSite;
	 	NewSite->UpTab=InfoSession->CurrTab;
	 	InfoSession->CurrTab->CurrSite=NewSite;
	}
}




