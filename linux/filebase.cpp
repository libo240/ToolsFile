#include "filebase.h"

#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

FileBase::FileBase()
{
    file_ = NULL;
    file_path_ = "";
    file_name_ = "";
    file_full_path_ = "";
    file_open_modes_ = "w+";//默认为可读可写

    start_time_ = {0,0};
    current_time_ = {0,0};

    modify_file_name_flag_ = false;
    file_status_ = false;
}

FileBase::~FileBase()
{
    CloseFile();
}

bool FileBase::IsOpen()
{
    return file_status_;
}

bool FileBase::Write(const void *content, size_t size, size_t count)
{
    if(NULL == file_ || NULL == content)
    {
        return false;
    }

    fwrite(content, size, count, file_);
    return true;
}

bool FileBase::OpenFile(const char* open_mode)
{
    file_open_modes_ = open_mode;
    CloseFile();

    if(file_path_.empty() || file_name_.empty())
    {
        return false;
    }

    if(-1 == access(file_path_.c_str(),F_OK))
    {
        MakeDir();
    }


    file_full_path_ = file_path_ + file_name_;
    if(NULL == (file_ = fopen(file_full_path_.c_str(),open_mode)) )
    {
        return false;
    }

    modify_file_name_flag_ = false;
    file_status_ = true;

    return true;
}

void FileBase::CloseFile()
{
    if(NULL != file_)
    {
        fclose(file_);
        file_ = NULL;
        file_status_ = false;
    }
}

bool FileBase::MakeDir()
{
    if(file_path_.empty())
    {
        return false;
    }
    char* temp = new char[file_path_.size()];
    memcpy(temp, file_path_.c_str(),file_path_.size());
    char* pos = temp;

    if(0 == strncmp(temp,"/",1) )
    {
        pos ++;
    }
    else if(0 == strncmp(temp,"./",2))
    {
        pos += 2;
    }

    for ( ; *pos != '\0'; ++ pos)
    {
        if (*pos == '/') {
            *pos = '\0';
            mkdir(temp, 0777);
            *pos = '/';
        }
    }

    delete[] temp;
    temp = nullptr;
    return true;
}

std::string FileBase::GetFileFullPath()
{
    return file_full_path_;
}

void FileBase::SetFileName(const std::string &file_name)
{
    file_name_ = file_name;
}

void FileBase::SetFilePath(const std::string &file_path)
{
    if(*(file_path.rbegin()) != '/')
    {
        file_path_ = file_path + "/";
    }
    else
    {
        file_path_ = file_path;
    }
}
