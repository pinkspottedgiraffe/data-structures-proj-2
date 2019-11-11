/*Stephania Kostaki A.M.:1115201600082*/

#ifndef __SESSION__
#define __SESSION__

typedef struct InfoSession *InfoSessionPtr;

InfoSessionPtr SessionNew(char *);
void SessionNewTab(InfoSessionPtr, int *);
void SessionTabShow(InfoSessionPtr);
void SessionTabNext(InfoSessionPtr);
void SessionTabPrev(InfoSessionPtr);
void SessionTabMoveRight(InfoSessionPtr);
void SessionNewOpeningAddress(InfoSessionPtr, char*);
void SessionShowOpeningAddress(InfoSessionPtr);
void SessionSiteNext(InfoSessionPtr);
void SessionSitePrev(InfoSessionPtr);
void SessionSiteShow(InfoSessionPtr);
void SessionTabClose(InfoSessionPtr *);
void SessionClose(InfoSessionPtr *);
void SessionNewAddresss(InfoSessionPtr, char *);


#endif
