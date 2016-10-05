#include "catalog.h"
#include "query.h"
#include "sort.h"
#include "index.h"
#include <cstdlib>
#include <string.h>


/* Consider using Operators::matchRec() defined in join.cpp
 * to compare records when joining the relations */
  
Status Operators::SMJ(const string& result,           // Output relation name
                      const int projCnt,              // Number of attributes in the projection
                      const AttrDesc attrDescArray[], // Projection list (as AttrDesc)
                      const AttrDesc& attrDesc1,      // The left attribute in the join predicate
                      const Operator op,              // Predicate operator
                      const AttrDesc& attrDesc2,      // The left attribute in the join predicate
                      const int reclen)               // The length of a tuple in the result relation
{
  cout << "Algorithm: SM Join" << endl;

  /* Your solution goes here */
	
	Status temp;

	// sort two attributes


	// get the record length
	AttrDesc* attrs;
	int attrCnt;
	int tupleLen = 0;
	temp = attrCat->getRelInfo(attrDesc1.relName, attrCnt, attrs);
	if (temp != OK)
		return temp;
	for (int i = 0; i < attrCnt; i++)
	{
		tupleLen = tupleLen + attrs[i].attrLen;
	} 
	// get the number of pages to perform sort
	unsigned num_page = 0.8 * bufMgr->numUnpinnedPages();
	// get the number of record that can be sorted one time
	unsigned num_byte = 1024 * num_page;	
	// get the number of tuple
	int num_tuple = num_byte/tupleLen;
		
	SortedFile sorted_attr_1(attrDesc1.relName, attrDesc1.attrOffset, attrDesc1.attrLen, (Datatype)attrDesc1.attrType, num_tuple, temp);
	if (temp != OK)
		return temp;

	tupleLen = 0;	
	temp = attrCat->getRelInfo(attrDesc2.relName, attrCnt, attrs);
	if (temp != OK)
		return temp;
	for (int i = 0; i < attrCnt; i++)
	{
		tupleLen = tupleLen + attrs[i].attrLen;
	}
	num_page = 0.8 * bufMgr->numUnpinnedPages();
	num_byte = 1024 * num_page;
	num_tuple = num_byte/tupleLen;

	SortedFile sorted_attr_2(attrDesc2.relName, attrDesc2.attrOffset, attrDesc2.attrLen, (Datatype)attrDesc2.attrType, num_tuple, temp);
	if (temp != OK)
		return temp;

	// begin merge

	Record rec1;
	Record rec2;
	HeapFile resultfile (result, temp);
	if (temp != OK)
		return temp;


	Record tempRecord;

	// merge algorithm

	if(!sorted_attr_2.next(rec2))
	{
		sorted_attr_2.setMark();
	}
	else
	{
		return OK;
	}

	while (!sorted_attr_1.next(rec1))
	{
		sorted_attr_2.gotoMark();
		sorted_attr_2.next(rec2);

		while(matchRec(rec1,rec2,attrDesc1,attrDesc2)>0)//rec2<rec1
		{
			if(sorted_attr_2.next(rec2))
			{
				return OK;
			}
		}
		sorted_attr_2.setMark();
		while(matchRec(rec1,rec2,attrDesc1,attrDesc2)==0)//=
		{
			RID ResultRID;
			Record ResultRecord;
			ResultRecord.data = malloc(ResultRecord.length);
			ResultRecord.length=reclen;
			int tempOffset = 0;

			for (int i = 0; i < projCnt; i++)
			{
				if (!strcmp(attrDescArray[i].relName, attrDesc1.relName))
				{
					tempRecord = rec1;
				}					
				else
				{
					tempRecord = rec2;
				}		
				memcpy ((char*)ResultRecord.data+tempOffset, (char*)tempRecord.data+attrDescArray[i].attrOffset, attrDescArray[i].attrLen);
				tempOffset+=attrDescArray[i].attrLen;
			}
			temp=resultfile.insertRecord(ResultRecord, ResultRID);
			if (temp != OK)
				return temp;
			free(ResultRecord.data);
			if(sorted_attr_2.next(rec2))
			{
				break;
			}
			if(matchRec(rec1,rec2,attrDesc1,attrDesc2)<0)//rec2>rec1
			{
				break;
			}
		}
	}
	return OK;
}

