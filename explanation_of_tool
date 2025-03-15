automation tool creation,scanning hosts with nmap,xml bomb creation,xss code creation,capture live with wireshark traffic
// the tool checks if everything is installed in your machine,posibly it's going to ask for super user (the root user) password to install the needed tools,if you are very based on privacy
// and for some reason you want to do manually the installations you are free to do,just interupt the programm with Ctrl+C.
//The -h argument is to show you what options you have in the app
// -sI argument is to show your status on everything
// -sIm argument is to show more details about
// -sO argument is a typical scan for me (nmap -sC -sV -v <ip_address>) 
// -sP argument is a default scan with given port with more details (nmap nmap -sC -sV -v <ip_address> -p <port number)
// -iU argument is for an intense scan (nmap -sS -sU -T4 -v --traceroute <ip_address>)
// -scs argument is for a slow comprenhesive scan (nmap -sS -sU -T4 -v -PE -PP -PS80,443 -PA3389 -PU40125 -PY -g 53 --traceroute  <ip_address>)
// -sa argument is for an intensive scan to all TCP Ports (nmap -T4 -A -v -PE -PS22,25,80 -PA21,23,80,3389 --traceroute <ip_address>)
// -iN argument is for an intense scanwith no ping method (nmap -T4 -A -v -Pn --traceroute <ip_address>)
// -i argument is for an intense scan (nmap -T4 -A -v -PE -PS22,25,80 -PA21,23,80,3389 --traceroute -sC -sV  <ip_address>)
// -q argument is for a quick scan (nmap -T4 --traceroute <ip_address>)
// -sF argument is for a default scan with base nse scriptand it forces ipv6 (nmap --script=default,safe -sS -sV -O -T4 -v -6 --traceroute <ip_address>)
// -sdb argument is for a default scan with base nse script (nmap --script=default,safe -sS -sV -O -T4 -v --tracerout <ip_address>)
// -sA argument is a default scan but aggresive (nmap --script=default,safe -sS -sV -O -T4 -v --tracerout <ip_address>)
// -d6 argument is for default scan and forces ipv6 (nmap -sS -sV -O -T4 -v -6 --traceroute <ip_address>)
// -d argument is for default scan (nmap -sS -sV -O -T4 -v --traceroute <ip_address>)
// -w argument is watch live the traffic,in otherwords it opens wrishark
// -l argument is to listen to a port with netcat (nc -tunlp <port_number>)
// -c argument creates a simple server with port with python (python3 -m http.server <port_number>) it's going to have the 0.0.0.0 address because in some cases it can't obtain an ip address
// -xs argument is for xss code creation,it creates a cross site script,you must start a python server to get the response
// -xm argument creates an xml bomb but the size is given by you
// -spA argument is to spam attack,you just send udp packet to the ip on a specific port,most of the times the other machine will not be able to handle them and the browser will not be able to load
// or generally any traffic response to that port for example i tested it from a laptop and attack a phone (it's from the modern one) and it couldn't handle the traffic in port 8080
// instagram or any website couldn't load at all or in other ports it made it but very slowly
// -sE argument see who is connected to a wifi, e.g 192.168.1.1/24 this will scan your wifi for any device that it uses it, ip adresses who use it are in the form of example (192.168.1.101,
// 192.168.1.103,192.168.1.105 and so on,they have the form of 192.168.1.x or 192.168.0.x,if you use a wifi pineapple it possible will have 172.16.42.x where is a number till 255)
// for the moment i will add the -Pn method
