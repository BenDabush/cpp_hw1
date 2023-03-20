#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copy_Func, DEL_FUNC del_Func, PRINT_FUNC print_Func)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
    pArr->copyFunc = copy_Func;
	pArr->delFunc = del_Func;
    pArr->printFunc = print_Func;
	return pArr;
}


Result SetAdptArrayAt(PAdptArray pArr, int index, PElement pNewElement)
{
	if (pArr == NULL)
    {
		return FAIL;
    }

    PElement* newpElementArr;

	if (pArr->ArrSize <= index)
	{
        newpElementArr = (PElement*)calloc((index + 1), sizeof(PElement));
		if (newpElementArr == NULL)
        {
			return FAIL;
        }
		memcpy(newpElementArr, pArr->pElemArr, pArr->ArrSize * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElementArr;
        pArr->ArrSize = index + 1;
        if ((pArr->pElemArr)[index] != NULL)
        {
            pArr->delFunc((pArr->pElemArr)[index]);
        }
	    (pArr->pElemArr)[index] = pArr->copyFunc(pNewElement);
	}
    else
    {
        if ((pArr->pElemArr)[index] != NULL)
        {
            pArr->delFunc((pArr->pElemArr)[index]);
        }
        (pArr->pElemArr)[index] = pArr->copyFunc(pNewElement);
    }

	return SUCCESS;
}


void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
    {
		return;
    }
	for(i = 0; i < pArr->ArrSize; ++i)
	{
        if ((pArr->pElemArr)[i] != NULL)
        {
            pArr->delFunc((pArr->pElemArr)[i]);
        }
	}
	free(pArr->pElemArr);
	free(pArr);
}

PElement GetAdptArrayAt(PAdptArray pArr, int i)
{
    if (pArr == NULL)
    {
        return NULL;
    }
    if ((pArr->pElemArr)[i] == NULL)
    {
        return NULL;
    }
    return pArr->copyFunc((pArr->pElemArr)[i]);
}


int GetAdptArraySize(PAdptArray pArr)
{
    if (pArr == NULL)
    {
        return -1;
    }
    return pArr->ArrSize;
}


void PrintDB(PAdptArray pArr)
{
    if (pArr == NULL)
    {
        return;
    }
    int i;
    for(i = 0; i < pArr->ArrSize; ++i)
	{
        if ((pArr->pElemArr)[i] != NULL)
        {
		    pArr->printFunc((pArr->pElemArr)[i]);
        }
	}
}