#ifndef AUIDirBar_H_
#define AUIDirBar_H_

#include <AntTweakBar.h>
#include <vector>

class AUiDirBar
{
public:
    AUiDirBar();
    virtual ~AUiDirBar();
    void loadDir(const std::string& dir);
    void initialize();
    void browse();
    void clear();

    typedef void (*FileClickedCb)(const char* filename, void* usr);
    void setFileClickedCb(FileClickedCb fn, void* usr);

    std::string getFilename() const;
    void setFilename(const std::string& filename);

protected:

    static void TW_CALL onLoadCb(void *clientData);
    static void TW_CALL onBrowseCb(void* usr);

protected:
    TwBar *_filesBar;
    std::string _filename;
    std::string _dir;
    std::vector<std::string> _files;
    struct LoadData { AUiDirBar* viewer; int fileid; };
    std::vector<LoadData*> _loadData;
    FileClickedCb _fileClickedCb;
    void* _usrData;
};

#endif
