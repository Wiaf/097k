/*
 * Logic.c
 */

#include <stdio.h>
#include <stdlib.h>

#define LOGIC

#include "defs.h"
#include "util.h"
#include "objects.h"
#include "liobs.h"
#include "logic.h"



void Analyse ( void )
{
/*Interface*/
Group   *** Groups = GetGroupStruct();
int      ** Block  = GetBlock();
int       * Reliability    = GetReliability();
/*Interface Ende*/
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

	/* exit(0) ; */

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
int       * Reliability = GetRelValue () ;
Average   * Avs         = GetAvs () ;
/* Interface End */
static float * DmaxMark = NULL ;
static float * DmaxRel  = NULL ;
static int   * DmaxLike = NULL ;
int   DiffWorkRel  = 0 ;
int   DiffWorkMark = 0 ;
int   DiffWorkLike = 0 ;
int   x, AnzGr = GetGroups() ;
int GroupMaxCount = 0 ; /* Die vollste Gruppe */
int GroupMinCount = 30000 ; /* Die leerste Gruppe */
int BigGroup = 0 ;
int SmallGroup = 0 ;

	if (DmaxMark == NULL) DmaxMark = (float *) MyMalloc ((GetGroups()*sizeof(float))+2) ;
	if (DmaxRel  == NULL) DmaxRel  = (float *) MyMalloc ((GetGroups()*sizeof(float))+2) ;
	if (DmaxLike == NULL) DmaxLike = (  int *) MyMalloc ((GetGroups()*sizeof(int))+2) ;

	for (x=0;x<AnzGr;x++)
		{
		if((*Groups)[x]->Count < GroupMinCount )
			{
			GroupMinCount = (*Groups)[x]->Count ;
			SmallGroup = x ;
			}
		if((*Groups)[x]->Count > GroupMaxCount )
			{
			GroupMaxCount = (*Groups)[x]->Count ;
			BigGroup = x ;
			}

		if((*Groups)[x]->Count >= (*Groups)[x]->MaxCount )
			{
			/* Gruppe x ist voll, naechste nehmen */
			if (DiffWorkMark == x) DiffWorkMark++;
			if (DiffWorkRel  == x) DiffWorkRel++;
			if (DiffWorkLike == x) DiffWorkLike++;
			continue; /* Group Ready */
			}

		if ((*Groups)[x]->Count == 0)
			{
			ConcatStudent (x,(*Studi)[ThisStudi]) ; /* Erster Student der Gruppe, fertig*/
			return ;
			}

		DmaxMark[x] = ComputeDiff((*Groups)[x]->AvMark,(*Studi)[ThisStudi]->Mark); 
		DmaxRel [x] = ComputeDiff((*Groups)[x]->AvRel, Reliability[(*Studi)[ThisStudi]->Reliability] ); 
		DmaxLike[x] = CompLikes (x,ThisStudi) ;

		if ( !(ComputeDiff (DmaxRel[x], DmaxRel[DiffWorkRel]) < 0.01 )) 
			if( DmaxRel[x] > DmaxRel[DiffWorkRel] ) DiffWorkRel = x;

		if ( DmaxMark[x] > DmaxMark[DiffWorkMark] ) DiffWorkMark = x ;

		if ( DmaxLike[x] > DmaxLike[DiffWorkLike] ) DiffWorkLike = x ;
		} /* for */

		if ( (GroupMaxCount - GroupMinCount) < GROUPDIFF )
			{
			if ( ComputeDiff ((*Groups)[DiffWorkMark]->AvMark, Avs->Mark ) > MARKDIFF )
				{
				ConcatStudent (DiffWorkMark ,(*Studi)[ThisStudi]);
				}	
			else
				{
				if (DmaxLike[DiffWorkLike] >= LIKEDIFF )
					{
					ConcatStudent (DiffWorkLike,(*Studi)[ThisStudi]);
					}
				else /* Nimm die naechste kleine Gruppe */
					{
					ConcatStudent ( SmallGroup,(*Studi)[ThisStudi]);
					}
				}
			}
		else /* Nimm die naechste kleine Gruppe */
			{
			ConcatStudent ( SmallGroup,(*Studi)[ThisStudi]);
			}
}

void Evaluation (void){
/*Interfacei Bereich*/
Group *** Groups = GetGroupStruct();
/*Interface End*/
int i, AnzGr=GetGroups();
int Wmin=0, Wmax=0, Amin=0, Amax, Smin=0, Smax=0;
int M=0, A=0, W=0;
float S = 0.0;
	for(i=0; i<AnzGr; i++)
		{
	
	        if((*Groups)[Wmin]->AvLike>(*Groups)[i]->AvLike)
                        Wmin=i;
                if((*Groups)[Wmax]->AvLike<(*Groups)[i]->AvLike)
                        Wmax=i;

                if((*Groups)[Amin]->AvRel>(*Groups)[i]->AvRel)
                        Amin=i;
                if((*Groups)[Amax]->AvRel<(*Groups)[i]->AvRel)
                        Amax=i;
                                 
                if((*Groups)[Smin]->AvMark>(*Groups)[i]->AvMark)
                        Smin=i;
                if((*Groups)[Smax]->AvMark<(*Groups)[i]->AvMark)
                        Smax=i;
		}


	M = ComputeDiff(((*Groups)[0]->Count)    , ((*Groups)[(AnzGr-1)]->Count)) ;
	S = ComputeDiff(((*Groups)[Smax]->AvMark), ((*Groups)[Smin]->AvMark));
	A = ComputeDiff(((*Groups)[Amax]->AvRel) , ((*Groups)[Amin]->AvRel)) ;
	W = ComputeDiff(((*Groups)[Wmax]->AvLike), ((*Groups)[Wmin]->AvLike));
	

	printf("\r\n\r\nKennzahlen:\r\nM (Abweichung Mitgliedsanzahl) = %d\r\nS (Abweichung Noten) = %f\r\nA (Abweichung Zuverlässigkeit) = %d\r\nW (Abweichung Wünsche) = %d\r\n", M, S, A, W);
 
}
void NewEvaluation (void){
/*Interfacei Bereich*/
Group *** Groups = GetGroupStruct();
/*Interface End*/
int i, AnzGr=GetGroups();
int  Amin=0, Amax, Smin=0, Smax=0;
int M=0, A=0, W1=0, W2=0;
float S = 0.0;
int * PlusMinus;
int   Plus  [2]={0,30000};
int   Minus [2]={0,30000};

        for(i=0; i<AnzGr; i++)
                {

                PlusMinus = NewLikeFunction(i);
printf("\r\nGruppe %d Plus=%d, Minus=%d",i,PlusMinus[0],PlusMinus[1]);

		/*Minus[Min]*/
                if(PlusMinus[1]<Minus[1])
			{
			Minus[1]=PlusMinus[1];
			}
		/*Minus[Max]*/
                if(PlusMinus[1]>Minus[0])
			{
			Minus[0]=PlusMinus[1];
			}
		/*Plus[Wer][Min]*/
                if(PlusMinus[0]<Plus[1])
			{
			Plus[1]=PlusMinus[0];
			}
		/*Plus[Wer][Max]*/
                if(PlusMinus[0]>Plus[0])
			{
			Plus[0]=PlusMinus[0];
			}

		if(((*Groups)[Amin]->AvRel*(*Groups)[Amin]->Count)>((*Groups)[i]->AvRel*(*Groups)[i]->Count))
                        Amin=i;
                if(((*Groups)[Amax]->AvRel*(*Groups)[Amin]->Count)<((*Groups)[i]->AvRel*(*Groups)[i]->Count))
                        Amax=i;

                if(((*Groups)[Smin]->AvMark*(*Groups)[Smin]->Count)>((*Groups)[i]->AvMark*(*Groups)[i]->Count))
                        Smin=i;
                if(((*Groups)[Smax]->AvMark*(*Groups)[Smin]->Count)<((*Groups)[i]->AvMark*(*Groups)[i]->Count))
                        Smax=i;
                }


        M = ComputeDiff(((*Groups)[0]->Count)    , ((*Groups)[(AnzGr-1)]->Count)) ;
        S = ComputeDiff(((*Groups)[Smax]->AvMark*(*Groups)[Smax]->Count), ((*Groups)[Smin]->AvMark*(*Groups)[Smin]->Count));
        A = ComputeDiff(((*Groups)[Amax]->AvRel* (*Groups)[Amin]->Count) ,((*Groups)[Amin]->AvRel* (*Groups)[Amin]->Count));
        W1= ComputeDiff(Plus[0],Plus[1]);
        W2= ComputeDiff(Minus[0],Minus[1]);

printf("\r\nMinMinus=%d, MaxMinus=%d", Minus[1], Minus[0]);
printf("\r\nWPlus=%d, WMinus=%d", W1, W2);

        printf("\r\n\r\nKennzahlen:\r\nM (Abweichung Mitgliedsanzahl) = %d\r\nS (Abweichung Noten) = %f\r\nA (Abweichung Zuverlässigkeit) = %d\r\nW (Abweichung Wünsche) = %d\r\n", M, S, A, W1+W2);

}

int *  NewLikeFunction       ( int GroupNr )
{
/* Interface Bereich */
int   *** Matrix = GetMatrix();
Group *** Groups = GetGroupStruct ();
int 	  AmountStudi=GetStudents();
/* Interface End */

static int PlusMinus[2];
int i;
Student * p;
Student * q;

	PlusMinus[0]=0;
	PlusMinus[1]=0;
        p = (*Groups)[GroupNr]->First;
        q = (*Groups)[GroupNr]->First;

        while (p!=NULL)
                {
		for(i=0; i<AmountStudi; i++)
			{
			if(p->UniqueNr!=i)
				{
				if((*Matrix)[p->UniqueNr][i]==-1) PlusMinus[1]++ ;
                        	}
			}

		while(q!=NULL)
			{
			if(p != q)
				{
printf("hiho");
				if((*Matrix)[p->UniqueNr][q->UniqueNr]< 0) {PlusMinus[1]--; printf("\r\nZUUU");} ;
				if((*Matrix)[p->UniqueNr][q->UniqueNr]> 0){ PlusMinus[0]++; printf("\r\nLoLo");} ;
                        	}
			q = q->Next;
			}

                p = p->Next ;
                }

        return PlusMinus;
}

