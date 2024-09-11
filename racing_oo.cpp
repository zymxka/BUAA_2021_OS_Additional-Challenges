#include "pageReplace.h"
#define MAX_PAGE 12
#define get_Page(x) (x>>MAX_PAGE)

void pageReplace(long * physic_memery, long nwAdd) {
        static int clock = 0;
        static int age[64];
        static int page = 0;
        if (clock == 0) {
                for (register int i = 0;i < 64; i++) {
                        age[i] = 0;
                }
        }
        clock++;
        if (page < 64) {
                long num = get_Page(nwAdd);
                for (register int i = 0;i < page;i++) {
                        if (num == physic_memery[i]) {
                                age[i] = clock;
                                return;
                        }
                }
                physic_memery[page] = num;
                age[page] = clock - 400;
                page++;
                return;
        } else {
                long num = get_Page(nwAdd);
                register int min = age[0];
                register int index = 0;
                for (register int i = 0;i < 64;i++) {
                        int time = age[i];
                        if (num == physic_memery[i]) {
                                age[i] = clock;
                                return;
                        }
                        if (time < min) {
                                min = time;
                                index = i;
                        }
                }
                physic_memery[index] = get_Page(nwAdd);
                age[index] = clock - 400;
        }
}
