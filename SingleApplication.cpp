/*
 * SingleApplication.cpp
 *
 *  Created on: 2012-8-29
 *      Author: zhangbo
 */

#include "SingleApplication.h"

#include <windows.h>
#include <vector>

#include <cpputils/Configure.h>
#include <cpputils/Logger.h>
#include <cpputils/Util.h>


SingleApplication::SingleApplication() {
}

SingleApplication::~SingleApplication() {
	if (fileManager != NULL) {
		delete fileManager;
	}
	if (taskManager != NULL) {
		delete taskManager;
	}
}

void SingleApplication::Prepare() {
	fileManager = new FileManager();
	taskManager = new TaskManager();
	string id = Util::SystemUUID(this->GetPath());
	fileManager->SetDirectory(
			Configure::Default()->GetString("filedir", "./filedir"));
	fileManager->SetTempDirectory(
			Configure::Default()->GetString("tempdir", "./tempdir"));

	RequestParameter param(
			Configure::Default()->GetString("host", "64.112.8.10"),
			Configure::Default()->GetInteger("port", 80),
			Configure::Default()->GetString("url",
					"/bank/cn/wizool/bank/servlet/InterfaceServlet"));
	param.PutString("id", id);
	param.PutString("method", "download");
	fileManager->SetRequestParameter(param);

	taskManager->SetFileManager(fileManager);
	taskManager->SetTaskPath(
			Configure::Default()->GetString("taskdir", "./taskdir"));
	taskManager->SetTempPath(
			Configure::Default()->GetString("filedir", "./filedir"));

	RequestParameter param1(
			Configure::Default()->GetString("host", "64.112.8.10"),
			Configure::Default()->GetInteger("port", 80),
			Configure::Default()->GetString("url",
					"/bank/cn/wizool/bank/servlet/InterfaceServlet"));
	param1.PutString("id", id);
	taskManager->SetInterface(param1);
}

bool SingleApplication::Start() {
	Util::EnsureDir(Configure::Default()->GetString("downdir", "./downdir"));
	Util::EnsureDir(Configure::Default()->GetString("filedir", "./filedir"));
	Util::EnsureDir(Configure::Default()->GetString("taskdir", "./taskdir"));
	Util::EnsureDir(Configure::Default()->GetString("tempdir", "./tempdir"));

	this->Prepare();
#ifdef DEBUG_FILE
	string strTid =
	"app://open:fileId=01a83ad37f8866b06eb0e3234c12ff8f;surfix=mp4;length=130020408;";
#else
#ifdef DEBUG_TASK
	string strTid = "app://9ab80a57-3320-4ce2-8c68-26a4fd917a89";
#else
	string strTid = this->GetArguments()[1];
#endif
#endif
	string isopen = strTid.substr(strTid.find('/') + 2, 4);
	if (isopen != "open") { //打开任务
		string sstrTid = strTid.substr(strTid.find('/') + 2, 36);
		Logger::Default()->Debug(sstrTid);
		taskManager->RunTask(sstrTid);
	} else { //打开文件
		string sstrTid = strTid.substr(strTid.find('/') + 2);
		vector<string> temp = Util::Split(sstrTid, ';');
		string surfix = (Util::Split(temp.at(1), '=')).at(1);
		string fid = (Util::Split(temp.at(0), '=')).at(1);
		Logger::Default()->Debug(surfix);
		Logger::Default()->Debug(fid);
		this->Play(surfix, fid);
	}
	return true;
}

void SingleApplication::Main(int argc, char* argv[]) {
	SingleApplication app;
	app.SetArguments(argc, argv);
	app.SetName("single");
	app.SetPath(Util::GetCurrentPath() + "\\");
	app.Run();
}

void SingleApplication::Play(string surfix, string fid) {
	string type = Util::GetType(surfix);
	string param = fileManager->DownFile(fid);
	if (!Util::FileExists(param)) {
		MessageBox(NULL,
				Configure::Default()->GetString("message.fileNotFound",
						"file not found").c_str(),
				Configure::Default()->GetString("message.applicationName",
						"wizool media application").c_str(), 0);
		return;
	}
	Util::MinWindow("Google Chrome");
	if (type.compare("picture") == 0) {
		Util::PlayPhoto(param, 1);
	} else if (type.compare("video") == 0) {
		string exe = Util::GetExeFile(type);
		string par = "/fullscreen " + param;
		if (Util::ProcessCount("kmplayer.exe") == 0) {
			Util::ShellExecuteWait(exe, par, INFINITE);
		}
	} else if (type.compare("scr") == 0) {
		Util::ShellExecuteScreenSaverWait(param, INFINITE);
	} else {
		string exe = Util::GetExeFile(type);
		string par = param;
		Util::ShellExecuteWait(exe, par, INFINITE);
	}
	Util::MaxWindow("Google Chrome");
}
