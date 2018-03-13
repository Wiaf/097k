cc          = gcc

cflags		= -c -O0 -x c -ansi -Wall -pedantic -DLINUX

# -c   ggc soll nur compilieren output ist .o
# -O0  Keine Optimierung
# -x c Sprache ist C
# -ansi Nur ANSI-Standard
# -Wall All Warnings enabled (But not realy all!)
# -pedantic also was heisst das wohl ?
# -DLINUX  wie #define LINUX

objects		= main.o filio.o liobs.o logic.o util.o objects.o

.c.$(s):
		$(cc) $(cflags) $<

tb097:	$(objects)
		$(cc) $(objects) -o tb097

main.o:		main.c filio.h liobs.h logic.h  util.h defs.h objects.h makefile
		$(cc) $(cflags) $<

logic.o:	logic.c logic.h  util.h defs.h objects.h makefile
		$(cc) $(cflags) $<

objects.o:	objects.c objects.h util.h defs.h liobs.h makefile
		$(cc) $(cflags) $<

liobs.o:	liobs.c liobs.h util.h defs.h objects.h makefile
		$(cc) $(cflags) $<

filio.o:	filio.c filio.h util.h liobs.h defs.h objects.h makefile
		$(cc) $(cflags) $<

util.o:		util.c util.h defs.h makefile
		$(cc) $(cflags) $<

