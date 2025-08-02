// toolset2.h
#ifndef TOOLSET2_H
#define TOOLSET2_H
#define NUM_TOOLS2 4

typedef struct {
    const char *name;
    const char *exec_cmd_unix;   
    const char *exec_cmd_macos;  
    const char *exec_cmd_win;    
} Tool2;

Tool2 tools2[NUM_TOOLS2] = {
    // name       | exec_cmd_unix      | exec_cmd_macos        | exec_cmd_win
    { "nmap",      "sudo nmap",         "sudo nmap",         "nmap" },
    { "python3",   "python3",           "python3",           "python3" },
    { "netcat",    "sudo nc",           "sudo nc",           "nc" },
    { "tcpdump",   "sudo tcpdump",      "sudo tcpdump",      "windump" } // windump is Windows tcpdump equivalent
};
#endif