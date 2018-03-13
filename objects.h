/*
 * object.h
 */

struct _Student ;
struct _Group ;

typedef struct _Student Student ;
typedef struct _Group Group ;

struct _Student {
	char * Name;
	int    Reliability ;
	float  Mark;
	char * Liking ;
	int    UniqueNr ;
	Student * Next ;
} ;

struct _Group {
	int    Count ;
	int    MaxCount ;
	int    AvRel ;
	int    AvLike ;
	float  AvMark;
	Student * First ;
} ;

typedef struct {
	float Mark ;
	float Rel ;
} Average ;

typedef enum {Neutral=0, Like=1, UnLike=-1, MaxLike=2, MaxUnLike=-2} Likes ; 

#ifdef OBJECTS
	Student *** GetStudiStruct ( void ) ;
	Group   *** GetGroupStruct (void) ;
	Student *** GetLastStudentOfGroup (void) ;
	Student  ** GetStudiList (void) ;
	Student  ** GetLastStudent ( void )  ;
	Student   * CreateStudent ( char * Name, int Rel, float Mark, char * Liking ) ;
	Average   * GetAvs (void) ;
	int     *** GetMatrix ( void ) ;
	int       * GetAmountStudents ( void ) ;
	int       * GetAmountGroups (void) ;
	int       * GetReliability (void) ;
	int      ** GetBlock (void) ;
	int       * GetRelValue (void) ;
	void        GenerateStudiArray ( void ) ;
	void        GenerateMatrix     ( void ) ;
	void        SetStudents ( int i )  ;
	int         GetStudents ( void ) ;
	void        SetGroups( int i ) ;
	int         GetGroups ( void ) ;
	void        CreateAllGroups   ( void )  ;
	void        MakeBlocks ( void )  ;
	/*
	 * Private Functions
	 */
	static int *  MergeSort(int * ToSort, int Len) ;
#else
	extern Student *** GetStudiStruct ( void ) ;
	extern Group   *** GetGroupStruct (void) ;
	extern Student *** GetLastStudentOfGroup (void) ;
	extern Student  ** GetStudiList (void) ;
	extern Student  ** GetLastStudent ( void )  ;
	extern Student   * CreateStudent ( char * Name, int Rel, float Mark, char * Liking ) ;
	extern Average   * GetAvs (void) ;
	extern int     *** GetMatrix ( void ) ;
	extern int       * GetAmountStudents ( void ) ;
	extern int       * GetAmountGroups (void) ;
	extern int       * GetReliability (void) ;
	extern int      ** GetBlock (void) ;
	extern int       * GetRelValue (void) ;
	extern void        GenerateStudiArray ( void ) ;
	extern void        GenerateMatrix     ( void ) ;
	extern void        SetStudents ( int i )  ;
	extern int         GetStudents ( void ) ;
	extern void        SetGroups( int i ) ;
	extern int         GetGroups ( void ) ;
	extern void        CreateAllGroups   ( void )  ;
	extern void        MakeBlocks ( void )  ;
#endif


