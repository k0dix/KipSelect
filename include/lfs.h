#pragma once

#include <string>
#include <vector>

#include "menu.h"

typedef struct {
	std::string titleId;
	std::string titleName;
	std::string titleDiscription;
	bool titleEnabled;
} lfsItem;

class LFS {
public:
	void scanLFS();
	void setLFSItemEnabled(unsigned int lfsId, bool enabled);
	bool getLFSItemEnabled(unsigned int lfsId);
	unsigned int getLFSCount();
	menuItem getLFSMenuItem(unsigned int lfsId);
private:
	std::vector<lfsItem> lfsItems;
};