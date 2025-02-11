#include <sys/socket.h>	/* socket */
#include <netinet/in.h>	/* IPPROTO_ICMP */
#include <unistd.h>		/* close, alarm, signal */
#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc */
#include <signal.h>		/* signal */
#include "libft.h"		/* ft_bzero */
#include "ft_ping.h"	/* all */

t_ping	all; /* global variable for ping */

void	ft_ping_send_packet(int sig)
{
	t_icmp_packet		pack;
	struct sockaddr_in	addr;
	struct msghdr		msg;
	long int			ret;

	(void)sig;

	/* init icmp packet for echo request */
	ft_bzero(&pack, sizeof(t_icmp_packet));	/* zero all fields */

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

	/* construct packet */
	pack.icmp.type		= 8;	/* echo request */
	pack.icmp.code		= 0;	/* no code */
	pack.icmp.checksum	= 0;	/* checksum computed later */
	pack.icmp.pid		= ft_swap16((t_u16)getpid());
	pack.icmp.sequence	= ft_swap16(all.stat.packet_sent++);
	ft_memmove(pack.payload, "Alors on sniffe mes packets ? iiiiiiiiiiiiiiiiiii"
		"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", 56);
	pack.icmp.checksum = ft_checksum16((t_u16 *)&pack, sizeof(t_icmp_packet));

	/* send packet */
	ft_bzero(&addr, sizeof(struct sockaddr_in));	/* zero all fields */
	addr.sin_family			= AF_INET;				/* 2, ipv4 */
	addr.sin_port			= 0;					/* no port used */
	addr.sin_addr.s_addr	= all.dest.ip;

	all.stat.last = ft_timestamp();
	if (sendto(all.sock, &pack, sizeof(pack), 0,
		(struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0)
		err_quit("failed to send packet");

	/* receive packet */
	ft_bzero(&msg, sizeof(struct msghdr));	/* zero all fields */
	msg.msg_iov = malloc(sizeof(struct iovec));
	msg.msg_iovlen = 1;
	msg.msg_flags = 0;
	msg.msg_iov->iov_base = malloc(1000);
	msg.msg_iov->iov_len = 84;	/* received packet expected to be 84 */

	if ((ret = recvmsg(all.sock, &msg, MSG_TRUNC)) < 0)
		err_quit("failed to recieve packet");

	all.stat.delta = ft_timestamp() - all.stat.last;
	all.stat.all_delta[all.stat.ad_size++] = all.stat.delta;
	all.stat.sum_delta += all.stat.delta;
		if (all.stat.delta < all.stat.min_delta)
		all.stat.min_delta = all.stat.delta;
	if (all.stat.delta > all.stat.max_delta)
		all.stat.max_delta = all.stat.delta;
	++all.stat.packet_recvd;

	if (ret >= 84)
	{
		t_ipv4_icmp_packet	*answ;
		answ = (t_ipv4_icmp_packet *)msg.msg_iov->iov_base;
		ft_ping_packet_print(answ);
	}

	/* call for next packet to be sent */
	alarm(1);

	free(msg.msg_iov->iov_base);
	free(msg.msg_iov);
}

void	ft_ping(int ac, char **av)
{
	
	ft_ping_parse_flags(ac, av, &all.flags);
	ft_ping_parse_address(ac, av, &all.dest);
	if ((all.sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		err_quit("Can't open socket");

	all.stat.begin = ft_timestamp();
	all.stat.last = all.stat.begin;
	all.stat.min_delta = (t_u64)-1L;
	all.stat.all_delta = malloc(sizeof(t_u64) * (1 << 16));

	ft_ping_header_print(&all.dest);

	/* packet send and recieve loop */

	signal(SIGALRM, ft_ping_send_packet);
	signal(SIGINT, ft_ping_tailer_print);
	ft_ping_send_packet(0);

	/* halt execution, everything handled by signals */
	for (;;);

	/* free before exit (useless and never called) */
	close(all.sock);
	free(all.stat.all_delta);
	if (all.dest.ptr_record)
		free(all.dest.ptr_record);
}