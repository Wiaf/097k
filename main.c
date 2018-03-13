/*
 * Main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "util.h"
#include "objects.h"
#include "filio.h"
#include "liobs.h"
#include "logic.h"


static void Print ( void ) ;

int main ( int argc, char ** argv )
{
static char * DateiName ;
static int AnzahlGruppen ;
FILE * fp ;
int FehlerToleranz = FEHLERTOLERANZ ; /* Nur damit es keine Warning
													* "Condition is always true"
                                       * gibt. */


	if (argc != 3)
		{
		fprintf (stderr,"\r\n\r\nAnzahl Parameter (%d) ungueltig.\r\n",argc);
		fprintf (stderr,"Programmabbruch.\r\n");
		Usage( argv[0]);
		exit (1);
		}

	if (strlen(argv[1]) == 0)
		{
		fprintf (stderr,"\r\n\r\nDateiname ungueltig, Laenge 0.\r\n");
		fprintf (stderr,"Programmabbruch.\r\n");
		Usage( argv[0]);
		exit (1);
		}

	DateiName = MyStrDup (argv[1]) ;
	AnzahlGruppen = atoi (argv[2]) ;

	if (AnzahlGruppen < MINGRUP || AnzahlGruppen > MAXGRUP)
		{
		fprintf (stderr,"\r\n\r\nAnzahl Gruppen (%d) ungueltig.\r\n",AnzahlGruppen);
		fprintf (stderr,"Programmabbruch.\r\n");
		Usage( argv[0]);
		exit (1);
		}

	if ((fp=fopen(DateiName,"r")) == NULL)
		{
		fprintf (stderr,"\r\n\r\nDatei Name (%s) ungueltig\r\noder Datei nicht lesbar.\r\n",DateiName);
		fprintf (stderr,"Programmabbruch.\r\n");
		Usage(argv[0]);
		exit (1);
		}
	else  fclose (fp) ;



	if (ProcessFile (DateiName) == false)
		{
		fprintf (stderr,"\r\nUnerwarteter Fehler in File (%s)\r\n",DateiName);
		fprintf (stderr,"Programmabbruch.\r\n");
		exit (1);
		}

	if (GetStudents() < AnzahlGruppen)
		{
		if (FehlerToleranz)
			{
			fprintf (stderr,"\r\nWarning: Anzahl Gruppen (%d) auf Anzahl Studenten (%d) gekuerzt!\r\n",
					AnzahlGruppen,GetStudents());
			}
		SetGroups (GetStudents());
		}
	else
		SetGroups (AnzahlGruppen);

	InitLiobs ();
	Analyse () ;
	TestPrint();
	Print () ;
	Evaluation();
	NewEvaluation();
	return true ;
	

}

static void Print ( void )
{
/*Interface*/
Group   *** Groups = GetGroupStruct() ;
/*Interface End*/
Student * p ;	
int i;

	for(i=0; i<GetGroups(); i++){
		p = (*Groups)[i]->First ;
		printf("\r\n\r\nGruppe %d:", i+1);
		while ( p != NULL ){
			printf("\r\n%s", p->Name);	
			p = p->Next;
		}
		printf("\r\nDurchschnittsnote: %f", (*Groups)[i]->AvMark);
		printf("\r\nDurchschnittszuverlaessigkeit: %d", (*Groups)[i]->AvRel);
		printf("\r\nZu-/Abneigung (+/-): %d\r\n", (*Groups)[i]->AvLike);
	}

}
