/*
 * Logic.c
 */

#include <stdio.h>

#define LOGIC

#include "defs.h"
#include "util.h"
#include "objects.h"
#include "liobs.h"
#include "logic.h"



void Analyse ( void )
{
Group   *** Groups = GetGroupStruct();
int      ** Block  = GetBlock();
int       * Reliability    = GetReliability();
int y, l, MaxGroup, Ueberhang ;

	MaxGroup  = (GetStudents() / GetGroups());
	Ueberhang = (GetStudents() % GetGroups());

	for(y=0; y<GetGroups(); y++)	
		{
		(*Groups)[y]->MaxCount = MaxGroup  ;
		if (Ueberhang > 0)
			{
			(*Groups)[y]->MaxCount++  ;
			Ueberhang -- ;
			}
		}

	for (y=(AnzRel-1); y>=0; y--)   				/*y zählt die Reliabilitys hoch*/
		for(l=0; l < Reliability[y];l++) 		/*l geht alle studenten in einem block durch*/
			FindGroup(Block[y][l]); 		

	for(y=0; y<GetGroups(); y++)	
		(*Groups)[y]->AvLike = CompLikes (y, (*Groups)[y]->First->UniqueNr);	
	
}

float ComputeDiff(float FloatWert1, float FloatWert2){

	if (FloatWert1<=FloatWert2)
		return FloatWert2-FloatWert1;
	else 
		return FloatWert1-FloatWert2;
}


void FindGroup(int ThisStudi)
{
/* Interface Bereich */
Group   *** Groups      = GetGroupStruct();
Student *** Studi       = GetStudiStruct();
int       * Reliability = GetReliability () ;
/* Interface End */
static float * DmaxMark = NULL ;
static float * DmaxRel  = NULL ;
int   DiffWork = -1 ;
int   x;
	
	if (DmaxMark == NULL) DmaxMark = (float *) MyMalloc ((GetGroups()*sizeof(float))+2) ;
	if (DmaxRel  == NULL) DmaxRel  = (float *) MyMalloc ((GetGroups()*sizeof(float))+2) ;
	
	for (x=0;x<GetGroups();x++)
		{
		if((*Groups)[x]->Count >= (*Groups)[x]->MaxCount ) continue; /* Group Ready */

		if ((*Groups)[x]->Count == 0)
			{
			ConcatStudent (x,(*Studi)[ThisStudi]) ; /* Erster Student */
			return ;
			}
		else		/*if count==0*/
 			{
			DmaxMark[x] = ComputeDiff((*Groups)[x]->AvMark,(*Studi)[ThisStudi]->Mark); 
			DmaxRel [x] = ComputeDiff((*Groups)[x]->AvRel, Reliability[(*Studi)[ThisStudi]->Reliability] ); 

			if ( DiffWork != -1 )
				{
				if ( (DmaxRel[x] > 33) && 
					  (DmaxRel[x] > DmaxRel[DiffWork]) )
					{
					DiffWork = x;
					}
				else
					{
					if ( ComputeDiff(DmaxMark[x], DmaxMark[DiffWork]) <= (0.5) )
						{
						if ( CompLikes(x, ThisStudi) > CompLikes(DiffWork, ThisStudi) ) DiffWork=x; 
						/* else keine Zuweisung auf DiffWork */
						}	
					else if(DmaxMark[x]>DmaxMark[DiffWork]) DiffWork = x;
							/* else keine Zuweisung auf DiffWork */
					}
				}
			else 								/*if DiffWork !=-1*/
				DiffWork = x;
			}
		}

	ConcatStudent (DiffWork,(*Studi)[ThisStudi]);
	
}
