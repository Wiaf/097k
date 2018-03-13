
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define UTIL
#include "defs.h"
#include "util.h"


/*------------------------------------------------------------*
* Funktion: MallocFehler Autor : Jakob Otten *
* Input: Anzahl der durch malloc zu allokierenden Bytes *
* Ouput: Die Funktion ist void sie beendet mit Fehlercode *
* *
* *
* Beschreibung: Fehlermeldung wird an stdout ausgegeben und *
* das Programm wird mit exit Code 2 abgebrochen. Diese *
* Funktion dient der Lesbarkeit des Codes *
*------------------------------------------------------------*/
void MallocFehler ( size_t Count )
{
	printf ("\r\nSchwerer Fehler, malloc (%d), Programm wird beendet\r\n", (unsigned int)Count ) ;
	exit (2) ;
}
/*------------------------------------------------------------*
* Funktion: MyStrDup Autor : Jakob Otten *
* Input: Pointer auf einen Text String *
* Ouput: Pointer auf einen neuen Text String *
* *
* Beschreibung: Die Funktion arbeitet wie strdup oder new *
* und wurde entwickelt weil strdup kein anshi-Standard ist. *
* Es wird mit MyMalloc ein neuer Speicherberreich allokiert *
c:\Users\Wiaf\Documents\Uni\SchneeRelease3.1\util.c 4
* und der Text String mt strcpy hineinkopiert. MyStrDup *
* erwartet einen mit 0x00 terminierten String. *
*------------------------------------------------------------*/
char * MyStrDup (char * Text)
{
	char * Dest ;
	Dest = (char *) MyMalloc (strlen(Text)+2) ; 
	strcpy (Dest,Text);
	return Dest ;
}

/*-------------------------------------------------------------*
* Funktion: CleanString | Autor: Sarah Hoenigsberg *
* CleanString ist public. *
* Input: Es wird ein String uebergeben. *
* Output: Returnwert *
* src *
* ClenString terminiert gegebenenfalls einen mit fgets *
c:\Users\Wiaf\Documents\Uni\SchneeRelease3.1\MENU.C 7
* geholten und mit 0x0a/0x0d terminierten string mit 0x00. *
* *
* Beschreibung: Der uebergebene String wird gereinigt und *
* zurueckgegeben. *
*-------------------------------------------------------------*/
char * CleanString (char * src )
{
	register int i ;
	for (i=0;i<(signed)strlen(src)+1;i++)
	{
		switch (src[i])
		{
			case '\n':
			case '\r':
				src[i]=0x00 ;
				break ;
			default:
				break ;
		}
	}
	return src ;
}
/*-------------------------------------------------------------*
* Funktion: WhiteSpace | Autor: Sarah Hoenigsberg *
* WhiteSpace ist public. *
* Input: Es wird ein String uebergeben. *
* Output: Die Finktion ist void und liefert keinen Returnwert *
* *
* Beschreibung: Die Funktion WhiteSpace entfernt fuehrende *
* und folgende Freizeichen (Blanks) und Terminiert den *
* String mit 0x00. *
*-------------------------------------------------------------*/
void White_Space (char * src)
{
	register int i ;
	int Found = false ;

	for (i=0;i<(signed)strlen(src)+1;i++)
	{
		if (src[i]==' ')
		{
			Found = true ;
		}
		else
		{
		if (Found)
			strcpy (src, &src[i]) ;
		break ;
		}
	}
	for (i=0;i<(signed)strlen(src)+1;i++)
	{
		if (src[i]==' ')
		{
			src[i] = 0x00 ;
			break ;
		}
	}
	printf ("\r\nWhiteSpace out <%s>\r\n", src);
}


char * MyMalloc ( size_t Count )
{
	char * q ; q = (char *)malloc ( Count ) ;
	if (q==NULL) MallocFehler ( Count ) ;
	return (q) ;
}

void Usage ( char * Name )
{
	fprintf(stderr,"\r\nUsage:\r\n");
	fprintf(stderr,"\r\n%s (Dateiname.ext) (Anzahl Gruppen %d-%d)\r\n\r\n",
			  Name,MINGRUP,MAXGRUP);
#ifdef WIN32
	system("pause");
#else
	fprintf (stderr,"\r\nPress [Return]\r\n");
	getchar () ;
#endif
}


/* Es wird vorausgesetzt, dass Src BUFFERLEN anzahl an Zeichen haben kann */

void BeautyStr ( char * Src )
{
int SrcLen ;
char * Dest ;
int i,j;

#ifdef DEBUG
	printf ("\r\nBeautyStr in <%s>\r\n", Src);
#endif

	Dest = MyMalloc (BUFFERLEN) ;

	SrcLen = strlen (Src) ;
	/* if (SrcLen <=1) return ; */

	/* Alle nicht zugelassene Zeichen werden geloescht */
	/* Es werden zusaetzlich nur Umlaute der Deutschen Sprache zugelassen */
	/* Freizeichen werden herausgefiltert */


	for (i=0,j=0;i<SrcLen;i++)
		{
		if (i>=BUFFERLEN) break ;  /* Abfangen von Programmierfehlern :-) */

		/* A-Z a-z 0-9 sind zugelassen */

		if ( isalpha(Src[i]) || isdigit(Src[i]) )
			{
			Dest[j++]= Src[i] ;
			continue ;
			}

		/* Weitere Zugelassene Zeichen */
		switch (Src[i])
			{
			case '+':
			case '-':
			case ',':
			case '.':
			case '·':
			case 'î':
			case 'Ñ':
			case 'Å':
			case 'ô':
			case 'é':
			case 'ö':
				Dest[j++]= Src[i] ;
				break ;
			default: /* Alle nicht aufgefuehrten Zeichen werden ignoriert */
				break ;
			}
		}

	Dest[j]  = 0x00 ;
	if (Dest[0] != 0)
		{
		strcpy (Src, Dest) ;
		strcat (Src,",");
		}
	else  Src[0] = 0 ;
	free (Dest);

#ifdef DEBUG
	printf ("\r\nBeautyStr out <%s> i=%d, j=%d\r\n", Src,i,j);
#endif

	return ;

}
