#ifndef _BIO_H_
#define _BIO_H_ 1
#if defined(__cplusplus)
extern "C" { 
#endif

#ifdef AUTOLIB
AUTOLIB(bio)
#endif

#include <fcntl.h>	/* for O_RDONLY, O_WRONLY */

typedef	struct	Biobuf	Biobuf;

enum
{
	Bsize		= 8*1024,
	Bungetsize	= UTFmax+1,	/* space for ungetc */
	Bmagic		= 0x314159,
	Beof		= -1,
	Bbad		= -2,

	Binactive	= 0,		/* states */
	Bractive,
	Bwactive,
	Bracteof,
};

struct	Biobuf
{
	int	icount;		/* neg num of bytes at eob */
	int	ocount;		/* num of bytes at bob */
	int	rdline;		/* num of bytes after rdline */
	int	runesize;	/* num of bytes of last getrune */
	int	state;		/* r/w/inactive */
	int	fid;		/* open file */
	int	flag;		/* magic if malloc'ed */
	vlong	offset;		/* offset of buffer in file */
	int	bsize;		/* size of buffer */
	uchar*	bbuf;		/* pointer to beginning of buffer */
	uchar*	ebuf;		/* pointer to end of buffer */
	uchar*	gbuf;		/* pointer to good data in buf */
	void	(*errorf)(char *);	/* called on error if not nil */
	int	(*iof)(Biobuf*, void *, long);	/* called to do i/o */
	uchar	b[Bungetsize+Bsize];
};

/* Dregs, redefined as functions for backwards compatibility */
#define	BGETC(bp)	Bgetc(bp)
#define	BPUTC(bp,c)	Bputc(bp,c)
#define	BOFFSET(bp)	Boffset(bp)
#define	BLINELEN(bp)	Blinelen(bp)
#define	BFILDES(bp)	Bfildes(bp)

int	Bbuffered(Biobuf*);
int	Bfildes(Biobuf*);
int	Bflush(Biobuf*);
int	Bgetc(Biobuf*);
int	Bgetd(Biobuf*, double*);
long	Bgetrune(Biobuf*);
int	Binit(Biobuf*, int, int);
int	Binits(Biobuf*, int, int, uchar*, int);
int	Blinelen(Biobuf*);
vlong	Boffset(Biobuf*);
Biobuf*	Bopen(char*, int);
Biobuf*	Bfdopen(int, int);
int	Bprint(Biobuf*, char*, ...);
int	Bvprint(Biobuf*, char*, va_list);
int	Bputc(Biobuf*, int);
int	Bputrune(Biobuf*, long);
void*	Brdline(Biobuf*, int);
char*	Brdstr(Biobuf*, int, int);
long	Bread(Biobuf*, void*, long);
vlong	Bseek(Biobuf*, vlong, int);
int	Bterm(Biobuf*);
int	Bungetc(Biobuf*);
int	Bungetrune(Biobuf*);
long	Bwrite(Biobuf*, void*, long);
void	Blethal(Biobuf*, void(*)(char*));
void	Berror(Biobuf*, char*, ...);
void	Biofn(Biobuf*, int(*)(Biobuf*, void*, long));

#if defined(__cplusplus)
}
#endif
#endif
