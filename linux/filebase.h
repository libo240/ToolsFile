#ifndef FILEBASE_H
#define FILEBASE_H

#include <string>

class FileBase
{
public:
    FileBase();
    virtual ~FileBase();

    bool OpenFile(const char* open_mode);

    void CloseFile();

    std::string GetFileFullPath();

    void SetFileName(const std::string& file_name);
    void SetFilePath(const std::string& file_path);

    bool IsOpen();

    bool Write(const void *content, size_t size, size_t count);

protected:
    bool MakeDir();

protected:
    FILE* file_;
    std::string file_path_;
    std::string file_name_;
    std::string file_full_path_;
    std::string file_open_modes_;

    struct timeval start_time_;
    struct timeval current_time_;

    bool modify_file_name_flag_;
    bool file_status_;
};

#endif // FILEBASE_H
