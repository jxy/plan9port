#include	"lib9.h"
#include	<bio.h>

void
Berror(Biobuf *bp, char *fmt, ...)
{
	va_list va;
	char buf[ERRMAX];

	if(bp->errorf == nil)
		return;
	
	va_start(va, fmt);
	vsnprint(buf, ERRMAX, fmt, va);
	va_end(va);
	bp->errorf(buf);
}

static void
Bpanic(char *s)
{
	sysfatal("%s", s);
}

void
Blethal(Biobuf *bp, void (*errorf)(char *))
{
	if(errorf == nil)
		errorf = Bpanic;

	bp->errorf = errorf;
}
