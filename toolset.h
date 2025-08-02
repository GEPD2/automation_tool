#define NUM_TOOLS 4

typedef struct {
    const char *name;
    const char *check_cmd;
    const char *install_cmd_unix;   // Linux (APT)
    const char *install_cmd_macos;  // macOS (Brew)
    const char *install_cmd_win;    // Windows (Chocolatey)
} Tool;

Tool tools[NUM_TOOLS] = {
    { "nmap",      "nmap --version > /dev/null 2>&1",     "sudo apt install nmap",     "brew install nmap",     "choco install nmap" },
    { "python3",   "python3 --version > /dev/null 2>&1",  "sudo apt install python3",  "brew install python3",  "choco install python3" },
    { "netcat",    "nc -h > /dev/null 2>&1",              "sudo apt install netcat",   "brew install netcat",   "choco install nmap" },
    { "tcpdump",   "tcpdump -h > /dev/null 2>&1",         "sudo apt install tcpdump",  "brew install tcpdump",  "choco install windump" }
};
