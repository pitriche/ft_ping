
	sendto arguments:
	socket fd(4o):		sock			-> ok
	packet data(~o):	&pack			-> ICMP head + payload (no ipv4 header)
	packet size(8o):	sizeof(pack)	-> ok
	sendto flags(4o):	0				-> ok
	
	dest address(16o):	(struct sockaddr*)addr	-> struct sockaddr_in
		-> family(2o):	2 (INET ipv4)
		-> port(2o):	0 (no port specified)
		-> addr(4o):	192.168.56.105 (concatenated as an uint32)
		-> pad(8o)
	size dest addr(4o):	sizeof(struct sockaddr_in)	-> 16 octets
