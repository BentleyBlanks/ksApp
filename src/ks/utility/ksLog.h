#ifndef KSLOG_H
#define KSLOG_H

#include <string>

void ksLog(const char *_Format,...);

void ksLog(const std::string &message);

void ksErrorLog(const std::string &path="log/logfile.log", bool append=true);

#endif
