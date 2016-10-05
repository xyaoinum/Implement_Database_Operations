#include "catalog.h"
#include "query.h"
#include "index.h"

#include <string.h>
#include <cstdlib>

/*
 * Selects records from the specified relation.
 *
 * Returns:
 * 	OK on success
 * 	an error code otherwise
 */
Status Operators::Select(const string & result,      // name of the output relation
	                 const int projCnt,          // number of attributes in the projection
		         const attrInfo projNames[], // the list of projection attributes
		         const attrInfo *attr,       // attribute used inthe selection predicate 
		         const Operator op,         // predicate operation
		         const void *attrValue)     // literal value in the predicate
{
	
	Status temp;

	int tempLength=0;
	AttrDesc Rattr;
	AttrDesc TempProjNames[projCnt];

	// get the length
	for (int i = 0; i < projCnt; i++)
	{
		// get the correctness of attrInfo[]
		temp=attrCat->getInfo(projNames[i].relName, projNames[i].attrName, Rattr);
		if (temp != OK)
		{
			return temp;
		}
		TempProjNames[i]=Rattr;
		tempLength+=Rattr.attrLen;
	}


	AttrDesc *tempD=NULL;
	// determine which selection method to use
	if(attr!=NULL)
	{
		temp=attrCat->getInfo(attr->relName, attr->attrName, Rattr);
		if (temp != OK)
		{
			return temp;
		}
		// indexSelect, because there is predicate and op=EQ and there is index on the predicate
		if(Rattr.indexed&&op == EQ)
		{
			return IndexSelect(result, projCnt, TempProjNames, &Rattr, op, attrValue, tempLength);
			
		}
		// scanSelect, because there is predicate but op is not EQ or there is no index
		else
		{
			return ScanSelect(result, projCnt, TempProjNames, &Rattr, op, attrValue, tempLength);
		}
	}
	else
	{
		// scanSelect, because there is no predicate
		return ScanSelect(result, projCnt, TempProjNames, tempD, op, attrValue, tempLength);
	}
}

