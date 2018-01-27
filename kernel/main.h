#ifndef MAIN_H
#define MAIN_H

#include <linux/ioctl.h>

#define MODULE_NAME "aos"
#define MAJOR_NUM 100

#define START_DIVBYZERO  _IOR(MAJOR_NUM, 1, int)
#define STOP_DIVBYZERO   _IOR(MAJOR_NUM, 2, int)
#define STATS_DIVBYZERO  _IOR(MAJOR_NUM, 3, unsigned long)

#endif
