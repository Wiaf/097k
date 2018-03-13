/*
 * liobs.h
 * requires object.h
 */

#ifdef LIOBS
	/*Student * CreateStudent  ( char * Name, int Verlass, float Note, char * Vorlieben ) ;  In Ojkects!!!*/
	void      ConcatStudent  ( int GroupNr, Student * Who ) ;
	int       CompLikes      ( int GroupNr, int StudentNr ) ;  
	void      InitLiobs      ( void ) ;
#else
	/*extern Student * CreateStudent ( char * Name, int Verlass, float Note, char * Vorlieben ) ;*/
	extern void      ConcatStudent  ( int GroupNr, Student * Who ) ;
	extern int       CompLikes      ( int GroupNr, int StudentNr ) ;
	extern void      InitLiobs      ( void ) ;
	extern void      TestPrint      ( void ) ;
#endif

