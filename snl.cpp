#include "catalog.h"
#include "query.h"
#include "sort.h"
#include "index.h"
#include <cstdlib>
#include <string.h>

Status Operators::SNL(const string& result,           // Output relation name
                      const int projCnt,              // Number of attributes in the projection
                      const AttrDesc attrDescArray[], // Projection list (as AttrDesc)
                      const AttrDesc& attrDesc1,      // The left attribute in the join predicate
                      const Operator op,              // Predicate operator
                      const AttrDesc& attrDesc2,      // The left attribute in the join predicate
                      const int reclen)               // The length of a tuple in the result relation
{
  cout << "Algorithm: Simple NL Join" << endl;

  /* Your solution goes here */
	Status temp;

	// new heapfile for the result
	HeapFile resultfile (result, temp);
	if (temp != OK)
		return temp;
	
	// out loop scan the first relation
	HeapFileScan Rel_1_Scan(attrDesc1.relName, temp);
	if (temp != OK)
		return temp;
	
	// traverse all the record in the first relation
	RID Rel_1_RID;
	Record Rel_1_Record;
	
	while (!Rel_1_Scan.scanNext(Rel_1_RID, Rel_1_Record))
	{
		// traverse all the recod in the second relation
		RID Rel_2_RID;
		Record Rel_2_Record;
		// inner loop scan for the second relation	
		HeapFileScan Rel_2_Scan (attrDesc2.relName, temp);
		if (temp != OK)
			return temp;
		while (!Rel_2_Scan.scanNext(Rel_2_RID, Rel_2_Record))
		{
			if ((op == LT && matchRec(Rel_1_Record, Rel_2_Record, attrDesc1, attrDesc2) < 0)||
				(op == LTE && matchRec(Rel_1_Record, Rel_2_Record, attrDesc1, attrDesc2) <= 0)||
				(op == EQ && matchRec(Rel_1_Record, Rel_2_Record, attrDesc1, attrDesc2) == 0)||
				(op == GTE && matchRec(Rel_1_Record, Rel_2_Record, attrDesc1, attrDesc2) >= 0)||
				(op == GT && matchRec(Rel_1_Record, Rel_2_Record, attrDesc1, attrDesc2) > 0)||
				(op == NE && matchRec(Rel_1_Record, Rel_2_Record, attrDesc1, attrDesc2) != 0)||
				(op == NOTSET))
			{ 
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
		}
		temp=Rel_2_Scan.endScan();
		if (temp != OK)
			return temp;
	}
 	return OK;
}

