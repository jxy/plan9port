#define setcursor dsetcursor

Memimage *attachscreen(char*, char*);
void	setmouse(Point);
void	setcursor(Cursor*);
void	setlabel(char*);
char*	getsnarf(void);
void	putsnarf(char*);
void	topwin(void);

void	mousetrack(int, int, int, uint);
void	keystroke(int);
void	kicklabel(char*);

void	servep9p(void);
void	zlock(void);
void	zunlock(void);

void resizeimg(void);

Rectangle mouserect;

#if OSX_VERSION < 101400
int mouseresized;
#else
#include<stdatomic.h>
atomic_int mouseresized;
void resizewindow(Rectangle);
#endif
