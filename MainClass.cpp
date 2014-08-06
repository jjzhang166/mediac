/*
 * MainClass.cpp
 *
 *  Created on: Jun 16, 2012
 *      Author: zhangbo
 */

#ifdef APP_SINGLE

#include "SingleApplication.h"
int main(int argc, char* argv[]) {
	SingleApplication::Main(argc, argv);
	return (0);
}

#else

#include "MediaApplication.h"
int main(int argc, char* argv[]) {
	MediaApplication::Main(argc, argv);
	return (0);
}

#endif

