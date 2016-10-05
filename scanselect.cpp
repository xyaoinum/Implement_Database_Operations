#include "catalog.h"
#include "query.h"
#include "index.h"

#include <string.h>
#include <cstdlib>

/* 
 * A simple scan select using a heap file scan
 */

Status Operators::ScanSelect(const string& result,       // Name of the output relation
                             const int projCnt,          // Number of attributes in the projection
                             const AttrDesc projNames[], // Projection list (as AttrDesc)
                             const AttrDesc* attrDesc,   // Attribute in the selection predicate
                             const Operator op,          // Predicate operator
                             const void* attrValue,      // Pointer to the literal value in the predicate
                             const int reclen)           // Length of a tuple in the result relation
{
  cout << "Algorithm: File Scan" << endl;
  
  /* Your solution goes here */

	Status temp;

	// if there is a predicate, use constructor with predicate arguments
	if(attrDesc!=NULL)
	{
		// construct scan
		HeapFileScan hf_scan(attrDesc->relName, attrDesc->attrOffset, attrDesc->attrLen, (Datatype)attrDesc->attrType, (static_cast<const char*> (attrValue)), op, temp);
		if (temp != OK)
		{
			return temp;
		}
		// construct heapfile to store result
		HeapFile result_heap(result, temp);
		if (temp != OK)
		{
			return temp;
		}

		RID tempRID0;
		Record tempRecord0;
		RID tempRID1;
		Record tempRecord1;
		int tempOffset;
		// traverse scanfile
		while(!hf_scan.scanNext(tempRID0, tempRecord0))
		{
			tempOffset=0;
			tempRecord1.length=reclen;
			tempRecord1.data=malloc(reclen);
			// project answer
			for (int i = 0; i < projCnt; i++)
			{
				if (temp != OK)
				{
					return temp;
				}
				memcpy ((char*)tempRecord1.data+tempOffset, (char*)tempRecord0.data+projNames[i].attrOffset, projNames[i].attrLen);
				tempOffset+=projNames[i].attrLen;
			}
			temp=result_heap.insertRecord(tempRecord1, tempRID1);
			if (temp != OK)
			{
				return temp;
			}
			// free mmemory
			free(tempRecord1.data);
		}
	}
	// if there is no predicate, use the other construct
	else
	{
		// coustruct scanfile	
		HeapFileScan hf_scan(projNames[0].relName, temp);
		if (temp != OK)
		{
			return temp;
		}
		// construct result heapfile
		HeapFile result_heap(result, temp);
		if (temp != OK)
		{
			return temp;
		}

		RID tempRID0;
		Record tempRecord0;
		RID tempRID1;
		Record tempRecord1;
		int tempOffset;
		while(!hf_scan.scanNext(tempRID0, tempRecord0))
		{
			tempOffset=0;
			tempRecord1.length=reclen;
			tempRecord1.data=malloc(reclen);
			// project
			for (int i = 0; i < projCnt; i++)
			{
				if (temp != OK)
				{
					return temp;
				}
				memcpy ((char*)tempRecord1.data+tempOffset, (char*)tempRecord0.data+projNames[i].attrOffset, projNames[i].attrLen);
				tempOffset+=projNames[i].attrLen;
			}
			temp=result_heap.insertRecord(tempRecord1, tempRID1);
			if (temp != OK)
			{
				return temp;
			}
			free(tempRecord1.data);
		}
	}
	return OK;
}










