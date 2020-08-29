#include <string>
#include <iostream>
#include "AUiDirBar.h"
#include "AOsUtils.h"
#include <algorithm>

AUiDirBar::AUiDirBar() : _filename("None"), _dir("None")
{
}

AUiDirBar::~AUiDirBar()
{
    clear();
}

void AUiDirBar::setFileClickedCb(FileClickedCb fn, void* usr)
{
    _fileClickedCb = fn;
    _usrData = usr;
}

void AUiDirBar::clear()
{
    for (unsigned int i = 0; i < _files.size(); i++)
    {
    	TwRemoveVar(_filesBar, _files[i].c_str());
    	delete _loadData[i];
    }
    _files.clear();
    _loadData.clear();
}

void AUiDirBar::initialize()
{
    char buff[1024];
    sprintf(buff, " min='%d' max='%d' step=0.1", 0, 100);

    _filesBar = TwNewBar("File controls");

    TwDefine(" 'File controls' size='200 300' position='5 185' "
        "iconified=false fontresizable=false alpha=200");

    TwAddVarRW(_filesBar, "Motion", TW_TYPE_STDSTRING, &_filename, "");

    TwAddVarRW(_filesBar, "Directory", TW_TYPE_STDSTRING, &_dir, " group='Dir'");

    TwAddButton(_filesBar, "Browse", onBrowseCb, this, 
        " label='--> Browse' group='Dir'");
}

void AUiDirBar::loadDir(const std::string& dir)
{
    clear();
    _dir = dir;

    char buff[1024];
    std::vector<std::string> dirs = GetFilenamesInDir(dir);
    for (unsigned int i = 0; i < dirs.size(); i++)
    {
    	std::string ext = dirs[i].substr(std::max<int>(4, dirs[i].size()) - 4);
    	if (ext != ".bvh") continue;

    	LoadData* ld = new LoadData;
    	ld->viewer = this;
    	ld->fileid = _files.size();
    	_files.push_back(dir + "/" + dirs[i]);
    	_loadData.push_back(ld);

    	sprintf(buff, " label='%s' group='Dir'", dirs[i].c_str());
    	TwAddButton(_filesBar, _files.back().c_str(), onLoadCb, ld, buff);
    }
}

std::string AUiDirBar::getFilename() const
{
    return _filename;
}

void AUiDirBar::setFilename(const std::string& filename)
{
    _filename = PruneName(filename);
}

void AUiDirBar::browse()
{    
    std::string dir = PromptToLoadDir();
    if (dir != "")
    {
        std::cout << dir << std::endl;
        loadDir(dir);
    }
}

void TW_CALL AUiDirBar::onLoadCb(void *clientData)
{
    LoadData* data = (LoadData*)clientData;
    AUiDirBar* viewer = data->viewer;
    int fileid = data->fileid;
    const char* filename = viewer->_files[fileid].c_str();
    viewer->_fileClickedCb(filename, viewer->_usrData);
    viewer->setFilename(filename);
}

void TW_CALL AUiDirBar::onBrowseCb(void* usr)
{
    ((AUiDirBar*)usr)->browse();
}

