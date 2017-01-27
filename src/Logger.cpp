#include "Logger.h"

static std::string GetTimeString()
{
    time_t t = time(0);
    struct tm *now = localtime(&t);
    int year = now->tm_year + 1900;
    int month = now->tm_mon + 1;
    int day = now->tm_mday;
    int hour = now->tm_hour;
    int minute = now->tm_min;
    int second = now->tm_sec;
    std::stringstream ss;
    ss << day << "/" << month << "/" << year << " " << hour << ":" << minute << ":"
       << second;
    return ss.str();
}

static void Log(const std::string &level, bool printToStdOut,
                const std::string &path, const std::string &text)
{
    static std::mutex mutex;
    mutex.lock();
    std::stringstream textstream;
    textstream << GetTimeString() << "\t[" << level  << "]\t" << text << std::endl;

    if (!path.empty()) {
        std::ofstream stream;
        stream.open(path, std::ofstream::out | std::ofstream::app);
        stream << textstream.str();
        stream.close();
    }

    if (printToStdOut) {
        std::cout << textstream.str();
    }

    mutex.unlock();
}

std::string Logger::debug = "";
std::string Logger::info = "";
std::string Logger::warning = "";
std::string Logger::error = "";
std::string Logger::critical = "";

bool Logger::stddebug = true;
bool Logger::stdinfo = true;
bool Logger::stdwarning = true;
bool Logger::stderror = true;
bool Logger::stdcritical = true;

void Logger::SetDebugStandardOut(bool b)
{
    stddebug = b;
}
void Logger::SetInfoStandardOut(bool b)
{
    stdinfo = b;
}
void Logger::SetWarningStandardOut(bool b)
{
    stdwarning = b;
}
void Logger::SetErrorStandardOut(bool b)
{
    stderror = b;
}
void Logger::SetCriticalStandardOut(bool b)
{
    stdcritical = b;
}

void Logger::SetupDebug(const std::string &path)
{
    debug = path;
}

void Logger::SetupInfo(const std::string &path)
{
    info = path;
}

void Logger::SetupWarning(const std::string &path)
{
    warning = path;
}

void Logger::SetupError(const std::string &path)
{
    error = path;
}

void Logger::SetupCritical(const std::string &path)
{
    critical = path;
}

void Logger::LogDebug(const std::string &text)
{
#ifdef DEBUG
    Log("DEBUG", stddebug, debug, text);
#endif
}

void Logger::LogInfo(const std::string &text)
{
    Log("INFO", stdinfo, info, text);
}

void Logger::LogWarning(const std::string &text)
{
    Log("WARNING", stdwarning, warning, text);
}

void Logger::LogError(const std::string &text)
{
    Log("ERROR", stderror, error, text);
}

void Logger::LogCritical(const std::string &text)
{
    Log("CRITICAL", stdcritical, critical, text);
}
