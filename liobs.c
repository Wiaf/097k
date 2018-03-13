/*
 * liobs.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIOBS

#include "defs.h"
#include "util.h"
#include "objects.h"
#include "liobs.h"


void TestPrint ( void )
{
 /*Interface Bereich */
Student*** Studi       = GetStudiStruct () ;
int    *** Matrix      = GetMatrix () ;
int     ** Block       = GetBlock () ;
int      * Reliability = GetReliability () ;
 /*Interface End */

int i,j;

/*
matrix
Liste der studies
Liste Studies nach blocks 
*/

	for(i=0;i<GetStudents(); i++){
		for(j=0;j<GetStudents(); j++)
			printf("%2d",(*Matrix)[i][j]);
		printf("\r\n");
	}

	for(i=0;i<GetStudents();i++)
		if ((*Studi)[i]->Liking != NULL)
			printf("\r\nName:%s Verlass:%2d Note:%f Vorlieben:%s\r\n",
					(*Studi)[i]->Name, 
					(*Studi)[i]->Reliability, 
					(*Studi)[i]->Mark, 
					(*Studi)[i]->Liking);
		else
			printf("\r\nName:%s Verlass:%2d Note:%f Vorlieben:keine\r\n",
					(*Studi)[i]->Name, 
					(*Studi)[i]->Reliability, 
					(*Studi)[i]->Mark);

	
	for(i=0; i<AnzRel;i++){
		printf("\r\nBlock %d: ",i+1);
		for(j=0; j<Reliability[i]; j++)
			printf("%s ", (*Studi)[ Block[i][j]  ]->Name );
		printf("\r\n");
	}
}	

void  ConcatStudent  ( int ThisGroup , Student * q ) /* -1 = Student, sonst GruppenNr */
{
/* Interface Bereich */
Group   *** Groups             = GetGroupStruct () ;
Student *** LastStudentOfGroup = GetLastStudentOfGroup () ;
Student  ** StudiList          = GetStudiList () ;
Student  ** LastStudent        = GetLastStudent () ;
int      * Reliability         = GetReliability () ;
int      * RelVal              = GetRelValue () ;
/* Interface End */

	if ( ThisGroup == -1 ) /* Concat an Student Liste */
		{
		Reliability[q->Reliability]++;
		if (*StudiList == NULL)
			{
			*StudiList   = q ;
			*LastStudent = q ;
			return ;
			}
		else
			(*LastStudent)->Next = q ;
			*LastStudent         = q ;
		}
	else
		{
		if ((*LastStudentOfGroup)[ThisGroup] == NULL)
			{
			(*Groups)[ThisGroup]->First      = q ;
			(*LastStudentOfGroup)[ThisGroup] = q ;
			}
		else
			{
			(*LastStudentOfGroup)[ThisGroup]->Next = q ;
			(*LastStudentOfGroup)[ThisGroup]       = q ;
			}
		(*Groups)[ThisGroup]->AvMark =
			(((*Groups)[ThisGroup]->AvMark * (*Groups)[ThisGroup]->Count) + q->Mark ) / 
			(++(*Groups)[ThisGroup]->Count) ;

		(*Groups)[ThisGroup]->AvRel = 
			((*Groups)[ThisGroup]->AvRel * ((*Groups)[ThisGroup]->Count-1) + RelVal[q->Reliability]) /(*Groups)[ThisGroup]->Count ;
		}
}


int	CompLikes	( int GroupNr, int StudentNr )
{
/* Interface Bereich */
int   *** Matrix = GetMatrix();
Group *** Groups = GetGroupStruct ();
/* Interface End */

Student * p;
int Like = 0 ;
	
	p = (*Groups)[GroupNr]->First;

	while (p!=NULL)
		{
		if(p->UniqueNr!=StudentNr)
			{
			Like += (*Matrix) [p->UniqueNr] [StudentNr]  ;
			Like += (*Matrix) [StudentNr]   [p->UniqueNr];
			}
		p = p->Next ;
		}
	return Like ;
}


void InitLiobs ( void )
{
	GenerateStudiArray () ;
	GenerateMatrix () ;
	CreateAllGroups () ;
	MakeBlocks () ;
}

