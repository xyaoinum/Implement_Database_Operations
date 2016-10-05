#include "catalog.h"
#include "query.h"
#include "index.h"


#include "utility.h"
#include <string.h>
#include <cstdlib>

/*
 * Inserts a record into the specified relation
 *
 * Returns:
 * 	OK on success
 * 	an error code otherwise
 */

Status Updates::Insert(const string& relation,      // Name of the relation
                       const int attrCnt,           // Number of attributes specified in INSERT statement
                       const attrInfo attrList[])   // Value of attributes specified in INSERT statement
{
	Status temp;
	int RattrCnt;
	AttrDesc *attr_ptr;

	temp = attrCat->getRelInfo(relation, RattrCnt, attr_ptr);

	// error checking: if failed to parse RattrCnt, attr_ptr
	if (temp != OK)
	{
		return temp;
	}


	// error checking: if number of attributes doesn't match 
	if (RattrCnt != attrCnt)
	{
		return NOTUSED1;
	}


	Record result;
	result.length = 0;
	AttrDesc Rattr[attrCnt];	// real attribute

	for (int i = 0; i < RattrCnt; i++)
	{
		
		temp=attrCat->getInfo(relation, attrList[i].attrName, Rattr[i]);
		// error checking: if failed to parse Rattr
		if (temp != OK)
		{
			return temp;
		}

		result.length += Rattr[i].attrLen;
	}

	result.data=malloc(result.length);
	for (int i = 0; i < RattrCnt; i++)
	{
		memcpy ((static_cast<char*> (result.data))+Rattr[i].attrOffset, attrList[i].attrValue, Rattr[i].attrLen);
	}

	// insert into heapfile
	RID current_rid;
	HeapFile current_heap(relation, temp);

	//error checking: if failed to create HeapFile
	if (temp != OK)
	{
		return temp;
	}

	temp = current_heap.insertRecord(result, current_rid);
	// error checking: if failed to insert Record
	if (temp != OK)
	{
		return temp;	
	}

	for (int i = 0; i < RattrCnt; i++)
	{
		if (Rattr[i].indexed)
		{
			Index current_index(Rattr[i].relName, Rattr[i].attrOffset, Rattr[i].attrLen, (Datatype)Rattr[i].attrType, 0, temp);
			// error checking: if failed to parse index
			if (temp != OK)
			{
				return temp;
			}
			temp = current_index.insertEntry(attrList[i].attrValue, current_rid);
			// error checking: if failed to insert index entry
			if (temp != OK)
			{
				return temp;
			}
		}
	}

	// free the memory
	free(result.data);



	return OK;
}









