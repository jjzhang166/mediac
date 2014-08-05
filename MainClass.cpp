/*
 * MainClass.cpp
 *
 *  Created on: Jun 16, 2012
 *      Author: zhangbo
 */

#include "MediaApplication.h"

#include "Config.h"
#include <cpputils/Util.h>
#include <cpputils/Logger.h>

int main(int argc, char* argv[]) {
	MediaApplication::Main(argc, argv);

//	Logger::SetDefault("Z:\\log.txt", Logger::LOG_DEBUG);
//	string ret = Util::GetIniString("bank", "host", "10.0.2.3", "C:\\Users\\zhangbo\\git\\mediac\\config.ini");
//	Logger::Default()->Debug(ret);

	return (0);
}
