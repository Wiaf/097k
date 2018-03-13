/*
 *
 *logic.h
 *
 */

#ifdef LOGIC
	void		Analyse			( void );
	float		ComputeDiff		( float FloatWert1 , float FloatWert2);
	int 		ComputeMaxGroup 	( int Groups, int Studis );
	void 		FindGroup		( int ThisStudi );
	void            Evaluation 		( void );
	void            NewEvaluation 		( void );
	int  	   *	NewLikeFunction		( int GroupNr );

#else
	extern void	Analyse			( void );
	extern void 	Evaluation 		( void );
	extern void 	NewEvaluation 		( void );
	extern int *	NewLikeFunction		( int GroupNr );
#endif

