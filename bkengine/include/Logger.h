#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <time.h>
#include <sstream>

class Logger
{
    public:
        static std::string debug;
        static std::string info;
        static std::string warning;
        static std::string critical;
        static std::string error;

        static bool stddebug;
        static bool stdinfo;
        static bool stdwarning;
        static bool stdcritical;
        static bool stderror;

        static void SetupDebug(const std::string &path);
        static void SetupInfo(const std::string &path);
        static void SetupWarning(const std::string &path);
        static void SetupError(const std::string &path);
        static void SetupCritical(const std::string &path);
        static void LogDebug(const std::string &text);
        static void LogInfo(const std::string &text);
        static void LogWarning(const std::string &text);
        static void LogError(const std::string &text);
        static void LogCritical(const std::string &text);

        static void SetDebugStandardOut(bool b);
        static void SetInfoStandardOut(bool b);
        static void SetWarningStandardOut(bool b);
        static void SetErrorStandardOut(bool b);
        static void SetCriticalStandardOut(bool b);
};

#endif
