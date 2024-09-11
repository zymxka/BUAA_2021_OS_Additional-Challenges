#include "pageReplace.h"
#define MAX_PHY_PAGE 64
#define MAX_PAGE 12
#define get_Page(x) (x>>MAX_PAGE)

void pageReplace(long * physic_memery, long nwAdd) {
	static int clock = 0;
	static int age[64];
	if (clock == 0) {
		for (int i = 0;i < MAX_PHY_PAGE; i++) {
			age[i] = 0;
		}
	}
	clock++;
	for (int i = 0;i < MAX_PHY_PAGE;i++) {
		if ((nwAdd >> MAX_PAGE) == physic_memery[i]) {
			age[i] = clock;
			return;
		}
	}
	int min = age[0];
	int index = 0;
	int flag = 0;
	for (int i = 0;i < MAX_PHY_PAGE; i++) {
		if (age[i] < min) {
			min = age[i];
			index = i;
		}
		if (physic_memery[i] == 0) {
			physic_memery[i] = get_Page(nwAdd);
			age[i] = clock - 400;
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		physic_memery[index] = get_Page(nwAdd);
		age[index] = clock - 400;
	}
}
