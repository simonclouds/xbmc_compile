#include <stdio.h>

extern int plus(int , int);
extern int vp1;

int main()
{
	printf("call a func in another file. plus(3,5)=%d\n",plus(3,5));
	vp1 = 5;
	printf("varibal vp1 in part1,vp1=%d\n",vp1);
	return 0;
}
