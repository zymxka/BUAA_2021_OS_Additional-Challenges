#include "pageReplace.h"
#define MAX_PAGE 12
#define get_Page(x) (x>>MAX_PAGE)

void pageReplace(long * physic_memery, long nwAdd) {
	static int clock = 0;
	static int age[64] = {0};
	static int cache_page[4] = {0};
	clock++;
	long num = get_Page(nwAdd);
	int index = get_Page(nwAdd) & 0x3;
	if (cache_page[index] < 16) {
		register int tail = cache_page[index] + (index << 4);
		for (register int i = (index << 4);i < tail;i++) {
			if (num == physic_memery[i]) {
				age[i] = clock;
				return;
			}
		}
		physic_memery[tail] = num;
		age[tail] = clock - 400;
		cache_page[index]++;
		return;
	} else {
		register int min = clock;
		register int replace = 0;
		register int tail = (index + 1) << 4;
		for (register int i = index << 4;i < tail;i++) {
			int time = age[i];
			if (num == physic_memery[i]) {
				age[i] = clock;
				return;
			}
			if (time < min) {
				min = time;
				replace = i;
			}
		}
		physic_memery[replace] = num;
		age[replace] = clock - 400;
	}
}
