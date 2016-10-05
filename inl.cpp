#include "catalog.h"
#include "query.h"
#include "sort.h"
#include "index.h"
#include <cstdlib>
#include <string.h>
/* 
 * Indexed nested loop evaluates joins with an index on the 
 * inner/right relation (attrDesc2)
 */

Status Operators::INL(const string& result,           // Name of the output relation
                      const int projCnt,              // Number of attributes in the projection
                      const AttrDesc attrDescArray[], // The projection list (as AttrDesc)
                      const AttrDesc& attrDesc1,      // The left attribute in the join predicate
                      const Operator op,              // Predicate operator
                      const AttrDesc& attrDesc2,      // The left attribute in the join predicate
                      const int reclen)               // Length of a tuple in the output relation
{

  cout << "Algorithm: Indexed NL Join" << endl;

  /* Your solution goes here */
	
	Status temp;

	// result heapfile
	HeapFile resultfile (result, temp);
	if (temp != OK)
		return temp;

	
	if (attrDesc1.indexed)
	{
		// for random scan
		HeapFileScan Rel_1_Scan(attrDesc1.relName, temp);
		if (temp != OK)
			return temp;

		// for sequential scan
		HeapFileScan Rel_2_Scan(attrDesc2.relName, temp);
		if (temp != OK)
			return temp;
		
		RID Rel_2_RID;
		Record Rel_2_Record;
	

		// get the index of relation 1
		Index idx(attrDesc1.relName, attrDesc1.attrOffset, attrDesc1.attrLen, (Datatype)attrDesc1.attrType, 0, temp);
	
		// outer loop, sequential scan relation 2
		while (!Rel_2_Scan.scanNext(Rel_2_RID, Rel_2_Record))
		{
			if (temp != OK)
				return temp;

			// get the current value of relation 2
			void* Record_value = (char*)Rel_2_Record.data + attrDesc2.attrOffset;

			temp = idx.startScan(Record_value);
			if (temp != OK)
				return temp;

			RID Rel_1_RID;
			Record Rel_1_Record;		
			// inner loop, random scan relation 1 with the help of index
			while (!idx.scanNext(Rel_1_RID))
			{
				temp=Rel_1_Scan.getRandomRecord(Rel_1_RID, Rel_1_Record);
				if (temp != OK)
					return temp;			

				// put into new heapfile
				RID ResultRID;
				Record ResultRecord;
				ResultRecord.length=reclen;
				
				// allocate memory
				ResultRecord.data = malloc(ResultRecord.length);
				
				int tempOffset = 0;
				Record tempRecord;

				// put the value in the result
				for (int i = 0; i < projCnt; i++)
				{
					if (!strcmp(attrDescArray[i].relName, attrDesc1.relName))
					{
						tempRecord = Rel_1_Record;
					}					
					else
					{
						tempRecord = Rel_2_Record;
					}
					
					memcpy ((char*)ResultRecord.data+tempOffset, (char*)tempRecord.data+attrDescArray[i].attrOffset, attrDescArray[i].attrLen);
					tempOffset+=attrDescArray[i].attrLen;
				}
				temp=resultfile.insertRecord(ResultRecord, ResultRID);
				if (temp != OK)
					return temp;
				free(ResultRecord.data);
			}
			temp=idx.endScan();
			if (temp != OK)
				return temp;

		}
	}
	else
	{
		// for random scan
		HeapFileScan Rel_2_Scan(attrDesc2.relName, temp);
		if (temp != OK)
			return temp;

		// for sequential scan
		HeapFileScan Rel_1_Scan(attrDesc1.relName, temp);
		if (temp != OK)
			return temp;
		
		RID Rel_1_RID;
		Record Rel_1_Record;
		
		// outer loop, sequential scan relation 1
		while (!Rel_1_Scan.scanNext(Rel_1_RID, Rel_1_Record))
		{
			
			// get the index of relation 2
			Index idx(attrDesc2.relName, attrDesc2.attrOffset, attrDesc2.attrLen, (Datatype)attrDesc2.attrType, 0, temp);
			if (temp != OK)
				return temp;

			// get the current value of relation 1
			void* Record_value = (char*)Rel_1_Record.data + attrDesc1.attrOffset;

			temp = idx.startScan(Record_value);
			if (temp != OK)
				return temp;

			RID Rel_2_RID;
			Record Rel_2_Record;		
			// inner loop, random scan relation 1 with the help of index
			while (!idx.scanNext(Rel_2_RID))
			{
				Rel_2_Scan.getRandomRecord(Rel_2_RID, Rel_2_Record);

				// put into new heapfile
				RID ResultRID;
				Record ResultRecord;
				ResultRecord.length=reclen;

				// allocate memory
				ResultRecord.data = malloc(ResultRecord.length);
				
				int tempOffset = 0;
				Record tempRecord;

				// put the value in the result
				for (int i = 0; i < projCnt; i++)
				{
					if (!strcmp(attrDescArray[i].relName, attrDesc1.relName))
					{
						tempRecord = Rel_1_Record;
					}					
					else
					{
						tempRecord = Rel_2_Record;
					}
					
					memcpy ((char*)ResultRecord.data+tempOffset, (char*)tempRecord.data+attrDescArray[i].attrOffset, attrDescArray[i].attrLen);
					tempOffset+=attrDescArray[i].attrLen;
				}
				temp=resultfile.insertRecord(ResultRecord, ResultRID);
				if (temp != OK)
					return temp;
				free(ResultRecord.data);
			}
			temp=idx.endScan();
			if (temp != OK)
				return temp;
		}
	}
  	return OK;
}

