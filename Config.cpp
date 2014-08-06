#include "Config.h"
#include <cpputils/Util.h>
#include <stdio.h>
#include <windows.h>
#include "def.h"

Config::Config(void) {
}

Config::~Config(void) {
}

string Config::GetInstallPath() {
	return Util::GetCurrentPath() + "\\";
}

string Config::GetConfigFile() {
	return Util::GetCurrentPath() + "\\config.ini";
}

string Config::GetHost() {
	return Util::GetIniString("bank", "host", SERVER_HOST, GetConfigFile());
}

UINT Config::GetPort() {
	return Util::GetIniInt("bank", "port", SERVER_PORT, GetConfigFile());
}

UINT Config::GetUpdateInterval() {
	return Util::GetIniInt("bank", "update", 20000, GetConfigFile());
}

string Config::GetUrl() {
	return Util::GetIniString("bank", "url",
			SERVER__URL, GetConfigFile());
}

string Config::GetUuidUrl() {
	return Util::GetIniString("bank", "uuidurl",
			"/bank/cn/wizool/bank/servlet/DepartmentServlet?method=getUUIDByIp",
			GetConfigFile());
}

string Config::GetSystemDir() {
	return Util::GetIniString("bank", "systemdir", "C:\\WINDOWS\\system32",
			GetConfigFile());
}

string Config::GetDownloadUrl() {
	return Util::GetIniString("bank", "downloadurl", "/bank/taskes", GetConfigFile());
}

string Config::GetDownloadFileUrl() {
	return Util::GetIniString("bank", "downloadfileurl",
			"/bank/cn/wizool/bank/servlet/DocumentServlet?method=download&id=",
			GetConfigFile());
}

string Config::GetVersionUrl() {
	return Util::GetIniString("bank", "versionurl",
			SERVER_VERSION_URL,
			GetConfigFile());
}

string Config::GetUpdateUrl() {
	return Util::GetIniString("bank", "updateurl", SERVER_UPGRADE_URL,
			GetConfigFile());
}

string Config::GetRegisterUrl() {
	char chrs[6];
	sprintf(chrs, "%d", Config::GetPort());
	return "http://" + Config::GetHost() + ":" + chrs
			+ Util::GetIniString("bank", "registerurl", "", GetConfigFile());
}

//string Config::GetExeFile(string name) {
//	return Util::GetIniString("exefile", name, "", GetConfigFile());
//}

string Config::GetWindowTitle(string name) {
	return Util::GetIniString("windowtitle", name, "", GetConfigFile());
}

string Config::GetProcessName(string name) {
	return Util::GetIniString("process", name, "", GetConfigFile());
}

string Config::GetRootDir() {
	return Util::GetIniString("bank", "rootdir", CLIENT_ROOT, GetConfigFile());
}

string Config::GetFileDir() {
	return Util::GetIniString("bank", "filedir", CLIENT_FILE, GetConfigFile());
}

string Config::GetTempDir() {
	return Util::GetIniString("bank", "tempdir", CLIENT_TEMP, GetConfigFile());
}

string Config::GetDownTmpFile() {
	return Util::GetIniString("bank", "downtmpdir", CLIENT_DOWN, GetConfigFile());
}

string Config::GetRccExamDir() {
	return Util::GetIniString("bank", "rccexamdir",
			"C:\\Program Files\\山东农信-业务技能评测\\client", GetConfigFile());
}
string Config::GetRccExamExe() {
	return Util::GetIniString("bank", "rccexamexe",
			"C:\\Program Files\\山东农信-业务技能评测\\client\\RccExam.exe", GetConfigFile());
}

string Config::GetIePar() {
	return Util::GetIniString("bank", "iepar", "http://51.64.1.98", GetConfigFile());
}

string Config::GetStartupDir() {
	return Util::GetIniString("bank", "startupdir",
			"C:\\Users\\Administrator\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup",
			GetConfigFile());
}

string Config::TheDayOfWeek(string dayofweek) {
	string week = Util::GetIniString("bank", "dayofweek", " ", GetConfigFile());
	vector<string> tempweek = Util::Split(week, ';');
	unsigned int weeknum = atoi(dayofweek.c_str());
	string thedayofweek = tempweek.at(weeknum);
	return thedayofweek;
}

string Config::GetDownUrl() {
	return Util::GetIniString("bank", "downurl",
			"/bank/cn/wizool/bank/servlet/InterfaceServlet?method=download&id=",
			GetConfigFile());
}

