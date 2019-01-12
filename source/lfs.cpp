#include <sstream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "lfs.h"
#include "error.h"

//netDownloadFile("http://nswdb.com/xml.php", "sdmc:/NSWreleases.xml");

void LFS::scanLFS() {
	lfsItems.clear();
	DIR* lfsDir;
	struct dirent* lfsEnt;
	lfsDir = opendir("/atmosphere/titles/");
	if (lfsDir == NULL) {
		if (mkdir("/atmosphere/titles/", 0700) == -1) {
			errorThrow(0, "/atmosphere/titles/");
		}
	}
	else {
		while ((lfsEnt = readdir(lfsDir))) {
			unsigned int pos = lfsItems.size();
			lfsItems.push_back(lfsItem());
			lfsItems[pos].titleId = lfsEnt->d_name;
			std::ostringstream flagsPath;
			flagsPath << "/atmosphere/titles/" << lfsEnt->d_name;
			struct stat info;
			stat(flagsPath.str().c_str(), &info);
			if (info.st_mode & S_IFDIR) {
				flagsPath << "/disabled.flag";
				if (stat(flagsPath.str().c_str(), &info) == 0) {
					lfsItems[pos].enabled = false;
				}
				else {
					lfsItems[pos].enabled = true;
				}
			}
			else {
				lfsItems[pos].enabled = true;
				if (mkdir(flagsPath.str().c_str(), 0700) == -1) {
					errorThrow(0, flagsPath.str().c_str());
				}
			}
		}
	}
}

void LFS::setLFSItemEnabled(unsigned int lfsId, bool enabled) {
	lfsItems[lfsId].enabled = enabled;
	std::ostringstream flagsPath;
	flagsPath << "/atmosphere/titles/" << lfsItems[lfsId].titleId << "/flags";
	struct stat info;
	stat(flagsPath.str().c_str(), &info);
	if (!(info.st_mode & S_IFDIR)) {
		if (mkdir(flagsPath.str().c_str(), 0700) == -1) {
			errorThrow(0, flagsPath.str().c_str());
		}
	}
	flagsPath << "/disabled.flag";
	if (enabled) {
		remove(flagsPath.str().c_str());
	}
	else {
		std::ofstream flag(flagsPath.str().c_str());
		if (flag.is_open()) {
			flag.close();
		}
		else {
			errorThrow(2, flagsPath.str().c_str());
		}
	}
}

bool LFS::getLFSItemEnabled(unsigned int lfsId) {
	return lfsItems[lfsId].enabled;
}

unsigned int LFS::getLFSCount() {
	return lfsItems.size();
}

menuItem LFS::getLFSMenuItem(unsigned int lfsId) {
	menuItem mnu;
	mnu.name = lfsItems[lfsId].titleId;
	mnu.status = lfsItems[lfsId].enabled;
	return mnu;
}