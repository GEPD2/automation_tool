// os.h
#ifndef OS_H
#define OS_H

// Windows
#if defined(_WIN32) || defined(_WIN64)
    #define OS_NAME "Windows"
    #define IS_WINDOWS 1
#else
    #define IS_WINDOWS 0
#endif

// Linux
#if defined(__linux__)
    #define OS_NAME "Linux"
    #define IS_LINUX 1
#else
    #define IS_LINUX 0
#endif

// macOS
#if defined(__APPLE__) && defined(__MACH__)
    #define OS_NAME "macOS"
    #define IS_MACOS 1
#else
    #define IS_MACOS 0
#endif

// Unix (fallback)
#if defined(unix) || defined(__unix__) || defined(__unix)
    #define IS_UNIX 1
#else
    #define IS_UNIX 0
#endif

#endif // OS_H