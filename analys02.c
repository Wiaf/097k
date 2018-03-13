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
int y, l, MaxGroup ;

	MaxGroup=(GetStudents()/GetGroups());
	for (y=(AnzRel-1); y>=0; y--){   				/*y zählt die Reliabilitys hoch*/
		for(l=0; l < Reliability[y];l++) 		/*l geht alle studenten in einem block durch*/
			FindGroup(Block[y][l], MaxGroup); 		
	
	}
	for(y=0; y<GetGroups(); y++){	
	(*Groups)[y]->AvLike = CompLikes (y, (*Groups)[y]->First->UniqueNr);	
	printf ("\r\nHere01\r\n");
	}
}

float ComputeDiff(float FloatWert1, float FloatWert2){

	if (FloatWert1<=FloatWert2)
		return FloatWert2-FloatWert1;
	else 
		return FloatWert1-FloatWert2;
}


void FindGroup(int ThisStudi, int MaxGroup){
/* Interface Bereich */
Group   *** Groups      = GetGroupStruct();
Student *** Studi       = GetStudiStruct();
/* Interface End */
static float * DmaxMark = NULL ;
static float * DmaxRel  = NULL ;
int   Reliability[3] = {33,66,100} ;
int   DiffWork = -1 ;
int   x;
float zwischenspeicher =0.0;
	
	if (DmaxMark == NULL) DmaxMark = (float *) MyMalloc ((GetGroups()*sizeof(float))+2) ;
	if (DmaxRel  == NULL) DmaxRel  = (float *) MyMalloc ((GetGroups()*sizeof(float))+2) ;
	
	for (x=0;x<GetGroups();x++)
		{
		if((*Groups)[x]->Count>=MaxGroup)
			continue;
		
		if ((*Groups)[x]->Count == 0)
			{
			ConcatStudent (x,(*Studi)[ThisStudi]) ;
printf("\r\nLeere Gruppe... Concat %s zu gruppe %d\r\n",(*Studi)[ThisStudi]->Name, x);
			return ;
			}
		else  /*if count==0*/
 			{


			DmaxMark[x] = ComputeDiff((*Groups)[x]->AvMark,(*Studi)[ThisStudi]->Mark); 
			DmaxRel [x] = ComputeDiff((*Groups)[x]->AvRel, Reliability[(*Studi)[ThisStudi]->Reliability] ); 
			

			if ( DiffWork!= -1 ){
printf("\r\nDmaxRel [x] = %f,  %d->AvRel = %d,%s->Reliability = %d", DmaxRel[x], x, (*Groups)[x]->AvRel,  (*Studi)[ThisStudi]->Name, Reliability[(*Studi)[ThisStudi]->Reliability]);

printf("\r\n %f > %f ?\r\n",DmaxRel[x],DmaxRel[DiffWork]);
				if (DmaxRel[x]>25&&DmaxRel[x]>DmaxRel[DiffWork])
					{
printf("\r\nja");
					if(DmaxRel[x]>DmaxRel[DiffWork])
						{
						DiffWork = x;
						}
					printf("\r\nHeyHo dmaxrelX=%f>DmaxrelDW =%f",DmaxRel[x],DmaxRel[DiffWork]);
					}
				
				else
					{
printf("\r\nnein");
					if (ComputeDiff(DmaxMark[x],DmaxMark[DiffWork])<=(0.0))
						{
					printf("\r\nliking \r\n");
						 if(DmaxMark[x]>DmaxMark[DiffWork])
							  {
							  DiffWork = x; printf("\r\nbest %d",x);
							  }


						/*if(CompLikes(x, ThisStudi)>CompLikes(DiffWork, ThisStudi)) ; funktioniert noch nicht!!!!!!!!
							{
								DiffWork=x;
							}*/
						}	
					else{
					printf("\r\nMark \r\n");
printf("DmaxMark[x] %f >DmaxMark[DiffWork] %f ", DmaxMark[x], DmaxMark[DiffWork]);
						if(DmaxMark[x]>DmaxMark[DiffWork])
							{
							DiffWork = x; printf("\r\nbest %d",x);
							}
					}}
				}
			else 								/*if DiffWork !=-1*/
				DiffWork = x;
			}
		}
	ConcatStudent (DiffWork,(*Studi)[ThisStudi]);
	
printf("\r\nConcat %s zu gruppe %d\r\n",(*Studi)[ThisStudi]->Name, DiffWork);

}
/*
int ComputeMaxGroup (int Groups, int Studis){
int MaxGroup=0;

	MaxGroup=(Studis/Groups);  ### brauch man nicht mehr!

	return MaxGroup; 	
} */
