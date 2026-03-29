#ifndef UTIL_H
#define UTIL_H

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#define ALIGN_UP_POW2(n, p) (((u64)(n) + ((u64)(p) - 1)) & (~((u64)(p) - 1)))

// very hacky but whatever
#define VOID (123456789)
#define ASSERT(n, c) \
do{ \
	if(!(c)) { \
		if((n) != VOID) { return (n); } \
		else { return; } \
	} \
}while(0)

#endif