/*
 * util.h
 */

#ifndef UTIL
	extern char * MyStrDup (char * Text) ;
	extern void MallocFehler ( size_t Count ) ;
	extern char * CleanString ( char * src ) ;
	extern void WhiteSpace ( char * src ) ;
	extern char * MyMalloc ( size_t Count )  ;
	extern void Usage (char * Name ) ;
	extern void BeautyStr ( char * Src );
#else
	char * MyStrDup (char * Text) ; /* Kopiert einen String waehrend der Laufzeit */
	void MallocFehler ( size_t Count ) ; /* Wertet einen Malloc Fehler aus*/
	char * CleanString ( char * src ) ; /* Terminiert den String bei\n oder \r */
	void WhiteSpace ( char * src ) ; /* Entfernt alle Blanks */
	char * MyMalloc ( size_t Count )  ;
	void Usage (char * Name ) ;
	void BeautyStr ( char * Src );
#endif

