# Networking and Scans Automation Tool 🔍

![Network Security](https://img.shields.io/badge/Network-Security-blue) 
![Multi-Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-green)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A powerful command-line utility for automating network scanning, testing, and security assessment tasks across multiple platforms.

## Features ✨

- **🔎 15+ Nmap Scan Profiles** - From quick scans to comprehensive vulnerability assessments
- **🌐 Cross-Platform Support** - Unified interface for Linux, Windows, and macOS
- **🛡️ Security Testing Suite** - XSS/XML payload generation and network stress tools
- **⚡ Utility Functions** - Port listening, HTTP servers, interface diagnostics
- **🤖 Smart Dependency Management** - Auto-installs nmap, netcat, python3, tcpdump

## Installation 📦

```bash
# Clone the repository
git clone https://github.com/yourusername/networking-scans-automation.git

# Compile and prepare
cd networking-scans-automation
gcc networking_and_scans_automation.c -o networking_and_scans_automation
chmod +x networking_and_scans_automation
#or you can type:
make

# Run with help flag to verify
./networking_and_scans_automation -h
```
Usage Examples 🚀
Basic Network Scanning

```bash
# Standard vulnerability scan
./networking_and_scans_automation -sO 192.168.1.1

# Quick scan with traceroute
./networking_and_scans_automation -q 10.0.0.1
```
Security Testing

```bash
# Generate XSS test scripts (saved to flag.txt)
./networking_and_scans_automation -xs flag.txt 192.168.1.10:80

# Create XML bomb (size parameter 10)
./networking_and_scans_automation -xm 10
```

Network Utilities
```bash
# Start Python HTTP server on port 8000
./networking_and_scans_automation -c 8000

# Show all network interfaces
./networking_and_scans_automation -sI
```
## Command Reference 📖

### Network Scanning
| Command | Description | Example |
|---------|-------------|---------|
| `-sO`   | Standard vulnerability scan (SYN, version detection, scripts) | `./networking_and_scans_automation -sO 192.168.1.1` |
| `-iU`   | Intense scan with UDP ports included (T4 timing) | `./networking_and_scans_automation -iU 10.0.0.1` |
| `-scs`  | Slow comprehensive scan (all probes, traceroute) | `./networking_and_scans_automation -scs 192.168.1.0/24` |

### Security Testing
| Command | Description | Example |
|---------|-------------|---------|
| `-xs`   | Generate XSS test scripts (saves to specified file) | `./networking_and_scans_automation -xs payload.txt target.com:80` |
| `-spA`  | UDP stress test (flood target with UDP packets) | `./networking_and_scans_automation -spA 192.168.1.50 53` |
| `-xm`   | Generate XML bomb (specify size parameter) | `./networking_and_scans_automation -xm 15` |

### Network Utilities
| Command | Description | Example |
|---------|-------------|---------|
| `-c`    | Start Python HTTP server | `./networking_and_scans_automation -c 8000` |
| `-l`    | Netcat port listener | `./networking_and_scans_automation -l 4444` |
| `-sI`   | Show network interface configuration | `./networking_and_scans_automation -sI` |

### Special Modes
| Command | Description | Example |
|---------|-------------|---------|
| `-d6`   | IPv6 scan with version detection | `./networking_and_scans_automation -d6 2001:db8::1` |
| `-sF`   | Force IPv6 with default NSE scripts | `./networking_and_scans_automation -sF 2001:db8::1` |

Security Notice ⚠️
This tool includes features that:

May generate malicious payloads (-xs, -xm)

Can perform network stress tests (-spA)

Execute privileged operations

Use Responsibly:
✓ Only test systems you own or have permission to scan
✓ Comply with all applicable laws and regulations
✓ Not for malicious use
