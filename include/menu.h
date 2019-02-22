#pragma once

#include <string>
#include <vector>

#include "screen/gfx.h"

#define STATUS_TYPE_DISABLED 0 //Show a grayed out box with the first value of statusNames
#define STATUS_TYPE_ONESHOT 1 //Show only the first value of statusNames
#define STATUS_TYPE_BOOL 2 //Two value toggle
#define STATUS_TYPE_LIST 3 //Display a list of values

typedef struct {
	std::string prefix;
	std::string data;
	std::string suffix;
} menuDetail;

typedef struct {
	unsigned int type;
	std::string name;
} menuStatus;

typedef struct {
	std::string name;
	std::vector<menuDetail> details;
	std::vector<menuStatus> statuses;
	unsigned int statusSelected;
	bool status;
} menuItem;

class MENU {
public:
	void loadAssets();
	void setTabSelected(unsigned int tabId);
	unsigned int getTabSelected();
	void setMenuSelected(unsigned int menuId);
	unsigned int getMenuSelected();
	unsigned int getMenuSize();
	void setStatusSelected(unsigned int statusId);
	unsigned int getStatusSelected();
	unsigned int getStatusCount();
	void addMenuItem(unsigned int tab, menuItem itm);
	void resetMenu();
	void drawMenu();
	void destroyAssets();
private:
	menuItem *getSelectedItem();
	unsigned int tabSelected;
	unsigned int menuSelected;
	std::vector<menuItem> kip;
	std::vector<menuItem> bct;
	std::vector<menuItem> layeredFS;
	std::vector<menuItem> options;
	//FONTS
	font *mainFont;
	//TEXTURES
	texture *menuBackground;
	texture *menuBar;
	texture *menuBarSelected;
	texture *menuCheckmark;
	texture *menuQuestionmark;
	texture *menuScrollUp;
	texture *menuScrollDown;
	texture *tabKips;
	texture *tabKipsSelected;
	texture *tabBCT;
	texture *tabBCTSelected;
	texture *tabLayeredFS;
	texture *tabLayeredFSSelected;
	texture *tabOptions;
	texture *tabOptionsSelected;
	texture *detailPurple;
	texture *detailGray;
};