/*
 * objects.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OBJECTS

#include "util.h"
#include "defs.h"
#include "objects.h"




/* Interface Funktionen */
int * GetRelValue ( void )
{
static int RelValue [] = {33,66,100} ;

	return RelValue ;

}

Average * GetAvs (void)
{
static Average Avs ;

	return &Avs ;
}
Student *** GetStudiStruct (void)
{
static Student ** Studi;

	return &Studi ;
}

Group *** GetGroupStruct (void)
{
static Group   ** Groups;

	return &Groups ;
}

Student *** GetLastStudentOfGroup (void)
{
static Student ** LastStudentOfGroup = NULL;

	return &LastStudentOfGroup ;
}

Student ** GetStudiList (void)
{
static Student * StudiList   = NULL ;

	return &StudiList ;
}

Student ** GetLastStudent ( void ) 
{
static Student * LastStudent = NULL ;

	return &LastStudent ;
}

int *** GetMatrix ( void )
{
static int ** Matrix ;

	return &Matrix ;
}

int * GetAmountStudents ( void )
{
static int AmountStudents = -1 ;

	return &AmountStudents ;
}

int * GetAmountGroups (void)
{
static int AmountGroups   = -1 ;

	return &AmountGroups ;
}

/* Interface on the Fly */
void SetStudents ( int i ) { *(GetAmountStudents()) = i ; }
void SetGroups   ( int i ) { *(GetAmountGroups  ()) = i ; } 

int  GetStudents ( void )  { return *(GetAmountStudents () ); }
int  GetGroups   ( void )  { return *(GetAmountGroups   () ); }
/* Interface on the Fly end */



int * GetReliability (void)
{
static int Reliability[AnzRel] = {0,0,0}; /* Anzahl Studies mit der speziellen Rel */

	return Reliability ;
}

int ** GetBlock (void)
{
static int * Block[AnzRel];

	return Block ;
}

Student * CreateStudent ( char * Name, int Rel, float Mark, char * Liking )
{
Student * q ;

	/* Alle Char Objekte sind bereits mit MyStrDup allokiert */

	q= (Student *) MyMalloc (sizeof(Student)) ;
	q->Name        = Name ;
	q->Reliability = Rel ;
	q->Mark        = Mark ;
	q->Liking      = Liking ;
	q->Next        = NULL ;
	return q ;
}

void GenerateStudiArray ()
{
/* Interface Bereich */
Student *** Studi = GetStudiStruct () ;
Student  ** q     = GetStudiList   () ;
/* Interface End */

int i = 0;

	*Studi=(Student **) MyMalloc(sizeof(Student*)*(GetStudents()+2));

	if( q != NULL)
		{
			i=0;
		do	{
			(*Studi)[i] = *q ;
			*q = (*q)->Next ;
			(*Studi)[i]->UniqueNr =i;
			(*Studi)[i++]->Next = NULL ;
		} while (*q != NULL);
		/* } while (q->Next != NULL); */
	}
	else
	{
		fprintf(stderr,"\r\n Unerwarteter Fehler, keine Studenten in Datenstruktur.\r\n");
		fprintf(stderr,"\r\n Programmabbruch");
		exit(1);
	}
}


void  GenerateMatrix     ( void )
{
/* Interface Bereich */
Student *** Studi   = GetStudiStruct () ;
int     *** Matrix  = GetMatrix() ;
Average *   Avs     = GetAvs ();
int     *   RelVal  = GetRelValue () ;
/* Interface End */

static char Dummy[BUFFERLEN];
int i, j, welcher;
int * p;
int AnzSt = GetStudents() ;

	*Matrix=(int**)MyMalloc(sizeof(int*)*AnzSt);

	p = (int *) MyMalloc (sizeof(int)*(AnzSt*AnzSt));

	Avs->Mark = 0.0 ;
	Avs->Rel  = 0.0 ;

	for(i=0 ; i<AnzSt ; i++)
	(*Matrix)[i] = &p[ (i*AnzSt) ];
	/* Befuelle Matrix mit Nullen */

	for(j=0;j<AnzSt;j++)
		for(i=0;i<AnzSt;i++)
			(*Matrix)[j][i]=0;

	for (j=0;j<AnzSt;j++)
		{
		for(welcher=0;welcher<AnzSt;welcher++)
			{
			if( (*Studi)[welcher]->Liking == NULL ) continue ;
			Dummy[0]='+';
			Dummy[1]=0x00;
			strcat(Dummy, (*Studi)[j]->Name);
			strcat(Dummy,",");
			if(strstr((*Studi)[welcher]->Liking,Dummy)!=NULL)
				(*Matrix)[welcher][j]=1;
			Dummy[0]='-';
			if((strstr((*Studi)[welcher]->Liking,Dummy)!=NULL) && (*Matrix)[welcher][j]==0)
				(*Matrix)[welcher][j]=-1;
			else if (strstr((*Studi)[welcher]->Liking,Dummy)!=NULL)
			(*Matrix)[welcher][j]=0;
			}	
		}

	for(j=0;j<AnzSt;j++)
		{
		Avs->Mark += (*Studi)[j]->Mark ;
		Avs->Rel  += RelVal[(*Studi)[j]->Reliability] ;
		}

	Avs->Mark = Avs->Mark / AnzSt ;
	Avs->Rel  = Avs->Rel  / AnzSt ;
}


void CreateAllGroups   ( void ) 
{
/* Interface Bereich */
Group   *** Groups = GetGroupStruct();
Student *** LastStudentOfGroup = GetLastStudentOfGroup() ;
/* Interface End */

int i;

	*Groups = (Group**) MyMalloc (sizeof(Group*)*GetGroups());
	*LastStudentOfGroup = (Student **) MyMalloc(sizeof(Student*) * GetGroups()) ;
	
	for(i=0; i< GetGroups(); i++){	
		(*Groups)[i]=(Group*) MyMalloc(sizeof(Group));
		(*Groups)[i]->Count    = 0 ;
		(*Groups)[i]->AvRel    = 0 ;
		(*Groups)[i]->AvLike    = 0 ;
		(*Groups)[i]->AvMark   = 0.0 ;
		(*Groups)[i]->First    = NULL ;
		(*LastStudentOfGroup)[i] = NULL ;
	}
}

void MakeBlocks ( void ) 
{
/* Interface Berteich */
int     ** Block       = GetBlock() ;
int      * Reliability = GetReliability() ;
Student ***Studi       = GetStudiStruct();
/* Interface end */

int BlockCount[AnzRel] = {0,0,0}; /* Schleifenzähler je Block */
int i = 12 ;

	for (i=0;i<AnzRel;i++)
		Block[i] = (int *) MyMalloc (sizeof(int)*Reliability[i]);

	for (i=0;i<GetStudents();i++)
		Block[(*Studi)[i]->Reliability][ (BlockCount[(*Studi)[i]->Reliability])++ ] = i ;

	for (i=0;i<AnzRel;i++)
		Block[i] = MergeSort ( Block[i], BlockCount[i] );

	/* Ab hier gibt es 3 Blöcke[0-AnzRel] (33,66,100) sortiert nach Note (Mark) */
}

/*
 * Mergesort Variante basierend auf der Java Version von:
 *
 * code codex //the free Code Wiki
 *
 * http://www.codecodex.com/wiki/Merge_sort#Java
 *
 * Die Java Variante wurde wegen des uebersichtlicheren 
 * Stils gewaehlt und portiert
 */

/* pre: array is full, all elements are valid integers (not null) */
/* post: array is sorted in ascending order (lowest to highest)   */


static int *  MergeSort(int * ToSort, int Len)
{
/* Interface Berteich */
Student *** Studi       = GetStudiStruct();
/* Interface end */
int * arr1, * arr2 ;
int i = 0, j = 0, k = 0 ;
int elementsInA1 ;
int elementsInA2 ;

	if(Len > 1)
		{
		elementsInA1 = Len/2;
		elementsInA2 = elementsInA1;

		if((Len % 2) == 1)
			elementsInA2 += 1;
 

		arr1 = (int*) MyMalloc ( sizeof (int)*(elementsInA1+2) );
		arr2 = (int*) MyMalloc ( sizeof (int)*(elementsInA2+2) );

		for(i = 0; i < elementsInA1; i++)
			arr1[i] = ToSort[i];

		for(i = elementsInA1; i < (elementsInA1 + elementsInA2); i++)
			arr2[i - elementsInA1] = ToSort[i];

		arr1 = MergeSort(arr1, elementsInA1);
		arr2 = MergeSort(arr2, elementsInA2);

		i = 0 ;

		while(elementsInA1 != j && elementsInA2 != k)
			{
			if((*Studi)[arr1[j]]->Mark <= (*Studi)[arr2[k]]->Mark) /*###*/
				{
				ToSort[i] = arr1[j];
				i++;
				j++;
				}
			else
				{
				ToSort[i] = arr2[k];
				i++;
				k++;
				}
			}

		while(elementsInA1 != j)
			{
			ToSort[i] = arr1[j];
			i++;
			j++;
			}

		while(elementsInA2 != k)
			{
			ToSort[i] = arr2[k];
			i++;
			k++;
			}

		free (arr1);
		free (arr2);
	
		} /* if len */

	return ToSort;
}

