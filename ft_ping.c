#include <sys/socket.h>	/* socket */
#include <netinet/in.h>	/* IPPROTO_ICMP */
#include <unistd.h>		/* close */
#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc */
#include "libft.h"		/* ft_bzero */
#include "ft_ping.h"	/* all */

t_ping	all; /* global variable for ping */

void	ft_ping(int ac, char **av)
{
	t_icmp_packet	pack;
	
	ft_ping_parse_flags(ac, av, &all.flags);
	if ((all.sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		err_quit("Can't open socket");
	printf("%d\n", all.sock);


	/* init icmp packet for echo request */
	ft_bzero(&pack, sizeof(t_icmp_packet));	/* zero all fields */

	/* ipv4 header initialisation */
	// pack.ipv4.version_ihl	|= 4 << 4;	/* ip version 4 */
	// pack.ipv4.version_ihl	|= 5;		/* 5 * 4 bytes header length */
	// pack.ipv4.dscp_ecn		|= 16 << 2;	/* DSCP 010000 (16) for ping */
	// pack.ipv4.dscp_ecn		|= 0;		/* no ECN */
	// pack.ipv4.packet_length	= sizeof(t_icmp_packet);
	// pack.ipv4.identification = 0;		/* no identification */
	// pack.ipv4.flag_offset	|= 0 << 13;	/* no flags */
	// pack.ipv4.flag_offset	|= 0;		/* no fragment offset */
	// pack.ipv4.ttl			= 64;		/* time to live, default 64 */
	// pack.ipv4.protocol		= 1;		/* 1 = ICMP */
	// pack.ipv4.header_checksum = 0;		/* checksum computed later */
	// pack.ipv4.source_ip		= 0x0;
	// pack.ipv4.dest_ip		= 0x0;
	// ft_bitdump((unsigned char *)&pack, sizeof(t_ipv4_header));
	// pack.ipv4.header_checksum = ft_checksum16((short *)&pack.ipv4, 10);
	// printf("checksum>%x\n", ft_checksum16((short *)&pack.ipv4, 10));

	/*
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
	*/

	pack.icmp.type		= 8;	/* echo request */
	pack.icmp.code		= 0;	/* no code */
	pack.icmp.checksum	= 0;	/* checksum computed later */
	pack.icmp.pid		= ft_swap16((t_u16)getpid());
	pack.icmp.sequence	= ft_swap16(1);	/* first packet sent is 1 (lso first) */
	ft_memmove(pack.payload, "Alors on sniffe mes packets ? iiiiiiiiiiiiiiiiiii"
		"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", 56);
	pack.icmp.checksum = ft_checksum16((unsigned short *)&pack,
		sizeof(t_icmp_packet));

	// ft_bitdump((unsigned char *)&pack, sizeof(t_icmp_packet));
	// pack.payload[55] -= 1;
	// pack.payload[53] += 1;
	// printf("checkchecksum>%x\n", ft_checksum16((unsigned short *)&pack,
	// 	sizeof(t_icmp_packet)));
	ft_chardump((unsigned char *)&pack, sizeof(t_icmp_packet));


	struct sockaddr_in	addr;
	ft_bzero(&addr, sizeof(struct sockaddr_in));	/* zero all fields */
	addr.sin_family			= AF_INET;				/* 2, ipv4 */
	addr.sin_port			= 0;					/* no port used */
	/* least significant octets are first, but within octets it's msb first */
	// addr.sin_addr.s_addr	= (192 << 0) | (168 << 8) | (56 << 16) | (105 << 24);
	addr.sin_addr.s_addr	= (93 << 0) | (184 << 8) | (216 << 16) | (34 << 24);
	

	if (sendto(all.sock, &pack, sizeof(pack), 0,
		(struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0)
		err_quit("failed to send packet, temporary, remove this");
	else
		printf("packet sent\n");

	struct msghdr	msg;
	ft_bzero(&msg, sizeof(struct msghdr));	/* zero all fields */
	// msg.msg_name = malloc(10000);
	// msg.msg_namelen = 10000;
	msg.msg_iov = malloc(sizeof(struct iovec));
	msg.msg_iovlen = sizeof(struct iovec);
	msg.msg_iov->iov_base = malloc(10000);
	msg.msg_iov->iov_len = 10000;
	// msg.msg_control = malloc(10000);
	// msg.msg_controllen = 10000;

	long int	ret;
	if ((ret = recvmsg(all.sock, &msg, MSG_TRUNC)) < 0)
		err_quit("failed to recieve packet, temporary, remove this");

	printf("packet recieved, ret>%ld\n", ret);
	// ft_hexdump((t_u8 *)&msg, sizeof(struct msghdr));
	// printf("field name> %p\n", msg.msg_name);
	// printf(" 	-> len %d\n", msg.msg_namelen);
	// printf(" -> field name > >%lx<\n\n", *(unsigned long *)msg.msg_name);
	// printf("field iov > %p\n", msg.msg_iov);
	// printf(" 	-> len %ld\n", msg.msg_iovlen);
	// printf(" -> field iov > %p\n", msg.msg_iov->iov_base);
	// printf(" ->		-> len %ld\n\n", msg.msg_iov->iov_len);
	// ft_hexdump((t_u8 *)msg.msg_iov->iov_base, 84);
	// printf("field cont> %p\n", msg.msg_control);
	// printf(" 	-> len %d\n\n", msg.msg_controllen);
	// printf("field flags> %d\n", msg.msg_flags);

	if (ret >= 84)
	{
		t_ipv4_icmp_packet	*answ;
		answ = (t_ipv4_icmp_packet *)msg.msg_iov->iov_base;
		printf("\n\n");
		ft_ipv4_header_print(&answ->ipv4);
		printf("\n");
		ft_icmp_header_print(&answ->icmp);
		printf("\n\n");
		printf("\n\n");
		ft_ping_packet_print(answ);
	}


	close(all.sock);
}