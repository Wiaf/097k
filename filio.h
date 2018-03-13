/*
 * filio.h
 */

#ifdef FILIO
	static int PreCreateStudent (char * Line);
	       int ProcessFile ( char * DateiName );
#else
	extern int ProcessFile ( char * DateiName );
#endif
