#include "linkedList.h"

struct AllData
{
	char* fileName;
	char* nodeName;
	int nodeNum;
	listDummy* dataQ;
}; 
typedef struct AllData allData;

typedef char* packet;

typedef int boolean;
enum {false, true};
