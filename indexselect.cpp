#include "catalog.h"
#include "query.h"
#include "index.h"

#include <string.h>
#include <cstdlib>

Status Operators::IndexSelect(const string& result,       // Name of the output relation
                              const int projCnt,          // Number of attributes in the projection
                              const AttrDesc projNames[], // Projection list (as AttrDesc)
                              const AttrDesc* attrDesc,   // Attribute in the selection predicate
                              const Operator op,          // Predicate operator
                              const void* attrValue,      // Pointer to the literal value in the predicate
                              const int reclen)           // Length of a tuple in the output relation
{
  cout << "Algorithm: Index Select" << endl;

  /* Your solution goes here */
	Status temp;

	
	if(attrDesc!=NULL)
	{
		// construct heapfilescan to get random record
		HeapFileScan hf_scan(attrDesc->relName, attrDesc->attrOffset, attrDesc->attrLen, (Datatype)attrDesc->attrType, (static_cast<const char*> (attrValue)), op, temp);
		if (temp != OK)
		{
			return temp;
		}

		// construct index
		Index idx(attrDesc->relName, attrDesc->attrOffset, attrDesc->attrLen, (Datatype)attrDesc->attrType, 0, temp);
		if (temp != OK)
		{
			return temp;
		}

		// result heapfile
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
		
		temp=idx.startScan(attrValue);
		if (temp != OK)
		{
			return temp;
		}

		while(!idx.scanNext(tempRID0))
		{
			// get random record
			temp=hf_scan.getRandomRecord(tempRID0, tempRecord0);
			if (temp != OK)
			{
				return temp;
			}
			
			tempOffset=0;
			tempRecord1.length=reclen;
			tempRecord1.data=malloc(reclen);
			
			// project
			for (int i = 0; i < projCnt; i++)
			{
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
		temp=idx.endScan();
		if (temp != OK)
		{
			return temp;
		}
	}
	// if there is no predicate, cannot use index select, cerr
	else
	{
		return NOTUSED1;
	}
	return OK;
}

