#include "catalog.h"
#include "query.h"
#include "sort.h"
#include "index.h"
#include <cmath>
#include <cstring>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define DOUBLEERROR 1e-07

/*
 * Joins two relations
 *
 * Returns:
 * 	OK on success
 * 	an error code otherwise
 */

Status Operators::Join(const string& result,           // Name of the output relation 
                       const int projCnt,              // Number of attributes in the projection
    	               const attrInfo projNames[],     // List of projection attributes
    	               const attrInfo* attr1,          // Left attr in the join predicate
    	               const Operator op,              // Predicate operator
    	               const attrInfo* attr2)          // Right attr in the join predicate
{
    /* Your solution goes here */



	Status temp;
	AttrDesc Rattr;
	AttrDesc Rattr1;
	AttrDesc Rattr2;

	int tempLength=0;
	AttrDesc TempProjNames[projCnt];


	// get the length
	for (int i = 0; i < projCnt; i++)
	{
		temp=attrCat->getInfo(projNames[i].relName,  projNames[i].attrName, Rattr);
		if (temp != OK)
		{
			return temp;
		}
		TempProjNames[i]=Rattr;
		tempLength+=Rattr.attrLen;
	}

	temp=attrCat->getInfo(attr1->relName,  attr1->attrName, Rattr1);
	if (temp != OK)
	{
		return temp;
	}

	temp=attrCat->getInfo(attr2->relName,  attr2->attrName, Rattr2);
	if (temp != OK)
	{
		return temp;
	}

	// check self join
	if (strcmp(Rattr1.relName, Rattr2.relName) == 0)
	{
		return NOTUSED1;
	}


	
	if(op == EQ)
	{
		// op=EQ, and index exist in at least one predicate attribute
		if (Rattr1.indexed||Rattr2.indexed)
		{
			return INL(result, projCnt, TempProjNames, Rattr1, op, Rattr2, tempLength);
		}
		// op=EQ, but there is no index on either predicate attribute
		else
		{
			return SMJ(result, projCnt, TempProjNames, Rattr1, op, Rattr2, tempLength);
		}
	}
	else
	{
		// op!=EQ
		return SNL(result, projCnt, TempProjNames, Rattr1, op, Rattr2, tempLength);
	}
	




	return OK;
}

// Function to compare two record based on the predicate. Returns 0 if the two attributes 
// are equal, a negative number if the left (attrDesc1) attribute is less that the right 
// attribute, otherwise this function returns a positive number.
double Operators::matchRec(const Record& outerRec,     // Left record
                        const Record& innerRec,     // Right record
                        const AttrDesc& attrDesc1,  // Left attribute in the predicate
                        const AttrDesc& attrDesc2)  // Right attribute in the predicate
{
    int tmpInt1, tmpInt2;
    double tmpFloat1, tmpFloat2, floatDiff;

    // Compare the attribute values using memcpy to avoid byte alignment issues
    switch(attrDesc1.attrType)
    {
        case INTEGER:
            memcpy(&tmpInt1, (char *) outerRec.data + attrDesc1.attrOffset, sizeof(int));
            memcpy(&tmpInt2, (char *) innerRec.data + attrDesc2.attrOffset, sizeof(int));
            return tmpInt1 - tmpInt2;

        case DOUBLE:
            memcpy(&tmpFloat1, (char *) outerRec.data + attrDesc1.attrOffset, sizeof(double));
            memcpy(&tmpFloat2, (char *) innerRec.data + attrDesc2.attrOffset, sizeof(double));
            floatDiff = tmpFloat1 - tmpFloat2;
            return (fabs(floatDiff) < DOUBLEERROR) ? 0 : floatDiff;

        case STRING:
            return strncmp(
                (char *) outerRec.data + attrDesc1.attrOffset, 
                (char *) innerRec.data + attrDesc2.attrOffset, 
                MAX(attrDesc1.attrLen, attrDesc2.attrLen));
    }

    return 0;
}
