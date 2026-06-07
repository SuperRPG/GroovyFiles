#ifndef _FILEUTILS_H_
#define _FILEUTILS_H_

#include <vector>
#include <string>
#include "sdlutils.h"

namespace FileUtils
{

//------------------------------------------------------------------------------
   // File operations
//------------------------------------------------------------------------------

   enum class FileOperation {foCopy, foMove};

   // Copy or move a list of files to dest dir.
   // p_action: 'c' = copy, 'm' = move.
   void copyOrMoveFiles(config_t* config, const FileOperation operation, const std::vector<std::string> &p_src, const std::string &p_dest);

   // Remove files
   void removeFiles(config_t* config, const std::vector<std::string> &p_files);

   // Create new directory
   void makeDirectory(const std::string &p_file);

   // Rename a file
   void renameFile(config_t* config, const std::string &p_file1, const std::string &p_file2);

//------------------------------------------------------------------------------
   // File utilities
//------------------------------------------------------------------------------

   // Format file size to human readable (K, M, G)
   std::string formatSize(const unsigned long long int &p_size);

   // File extension
   std::string getFileExtension(const std::string &p_name);

   // File exists?
   bool fileExists(const std::string &p_path);

   // Extract file name from a path
   std::string getFileName(const std::string &p_path);

   // Extract dir name from a path
   std::string getDirName(const std::string &p_path);

   // Extract file name without extension
   std::string getRootName(const std::string &p_path);

   // Dir size
   unsigned long long int getDirSize(const std::string &p_path);

   // File is text
   bool fileIsText(const std::string &p_path);

   // String to lower case
   void toLower(std::string &s);

}

#endif
