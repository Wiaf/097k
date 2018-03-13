/*
 * filio.c
 */

#define FILIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "objects.h"
#include "util.h"
#include "filio.h"
#include "liobs.h"


/* beide */

int ProcessFile ( char * DateiName )
{
	char * DummyString ;
	FILE * fp;
	int i, Leer ;
	int FehlerToleranz = FEHLERTOLERANZ ; /* Nur damit es keine Warning
														* "Condition is always true"
														* gibt. */

	fp = fopen ( DateiName, "r" ) ;
	if ( fp == NULL ) return false ;

	DummyString = MyMalloc (BUFFERLEN) ;

	for(Leer=0,i=0;;i++){
		if (!fgets ( DummyString, BUFFERLEN-6, fp)) break;

		BeautyStr (DummyString) ;

		if (strlen(DummyString)==0)
			{
			if (FehlerToleranz)
				{
				Leer ++ ;
				continue ; /*  freizeilen werden ignoriert */
				}
			else break ;                   /*  sonst EOF */
			}

	if (!PreCreateStudent (DummyString))
		{
		fprintf (stderr,"\r\n\r\nSyntax Error File (%s) in Line (%d)\r\n",DateiName,i+1 );
		fprintf (stderr,"Programmabbruch.\r\n");
		fclose (fp) ;
		exit (1);
		}
	}

	fclose (fp) ;

	SetStudents (i-Leer) ;/* i Studenten von 1-i */

	free (DummyString) ;

	return true ;
}

static int PreCreateStudent (char * Line)
{
	char * p , * Name, * Liking ;
	int Rel ;
	float Mark;
	int FehlerToleranz = FEHLERTOLERANZ ; /* Nur damit es keine Warnig
														* "Condition is always true"
														* gibt. */

	p = strchr (Line,DELIMITER);
	if (p==NULL) return false ;
	p[0] = 0x00 ;
	Name = MyStrDup (Line) ;
	if (strlen(Name)==0) return false ;

	p[0] = DELIMITER ;

	Rel = atoi (&p[1]);
	if (FehlerToleranz)
		{
		if (Rel<=33) Rel=33 ;
		if (Rel>33 && Rel<=66) Rel=66 ;
		if (Rel>66) Rel=100 ;
		}
	else

		if (Rel!=33&&Rel!=66&&Rel!=100) return false ;

	switch (Rel)
		{
		case  33: Rel =  r33 ; break ;
		case  66: Rel =  r66 ; break ;
		case 100: Rel = r100 ; break ;
		} /* default ist unmöglich */

	p[0] = ' ' ;
	p = strchr (Line,DELIMITER);

	if (p==NULL) return false ;

	Mark = atof (&p[1]);
	if (Mark<=MINMARK||Mark>MAXMARK) return false ;

	p[0] = ' ' ;
	p = strchr (Line,DELIMITER);
	if (p==NULL) Liking = NULL ;
	else
	{
	if (strlen (p) == 0 ) Liking = NULL ;
	else Liking = MyStrDup (p) ;
	}
	
	ConcatStudent ( -1 , CreateStudent ( Name, Rel, Mark, Liking ) );

	return true ;
}



