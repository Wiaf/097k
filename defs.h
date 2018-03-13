/*
 *defs.h
 */


/*#define DEBUG       12*/

#define true         1
#define false        0

#define FEHLERTOLERANZ true

#define MINGRUP      1
#define MAXGRUP     20
   
#define BUFFERLEN 1024 /* Maximale Laenge der Zeile */

#define MINMARK      0.99
#define MAXMARK      5.01

#define DELIMITER    ','

#define GROUPDIFF    2
#define MARKDIFF     0.5
#define LIKEDIFF     4

typedef enum {r33=0,r66,r100,AnzRel} Rels ;
