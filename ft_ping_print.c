#include "ft_ping.h"	/* t_ipv4_header */
#include "libft.h"		/* putstr_fd */
#include <stdlib.h>		/* exit */
#include <stdio.h>		/* printf */

/* printf an ipv4 address */
void	ft_ipv4_print(t_u32 addr)
{
	printf("%hhu.%hhu.%hhu.%hhu", addr >> 24, addr >> 16, addr >> 8, addr);
}

/* debug */
void	ft_ipv4_header_print(t_ipv4_header *head)
{
	printf("ipv4 header:\n");
	printf("version:%hhd | IHL:%hhd     | ", (head->version_ihl >> 4) & 0xf,
		head->version_ihl & 0xf);
	printf("DSCP:%hhd   | ECN:%hhd\n", (head->version_ihl >> 2) & 0x3f,
		head->version_ihl & 0x3);
	printf("identification:%3hd    | ", ft_swap16(head->identification));
	printf("flag:%hd    | fragment offset:%d\n\n",
		(head->flag_offset >> 13) & 0x7, (head->flag_offset & (0x1fff)));

	printf("packet length: %hd bytes\n", ft_swap16(head->packet_length));
	printf("ttl          : %hhd\n", head->ttl);
	printf("protocol     : %hhd\n", head->protocol);
	printf("checksum>%x  check>%x\n\n", ft_swap16(head->header_checksum),
		ft_checksum16((t_u16 *)head, sizeof(t_ipv4_header)));

	printf("source address > ");
	ft_ipv4_print(ft_swap32(head->source_ip));
	printf("\ndest address   > ");
	ft_ipv4_print(ft_swap32(head->dest_ip));
	printf("\n");
}

/* debug */
void	ft_icmp_header_print(t_icmp_header *head)
{
	printf("icmp header:\n");
	printf("Type:%hhd    | Code:%hhd\n", head->type, head->code);
	printf("pid:%5u | Sequence:%hu\n", ft_swap16(head->pid),
		ft_swap16(head->sequence));
	printf("checksum>%x\n", ft_swap16(head->checksum));
}

/*
	>>> if is_ip

PING 199.232.81.140 (199.232.81.140) 56(84) bytes of data.
64 bytes from 199.232.81.140: icmp_seq=1 ttl=63 time=12.4 ms
64 bytes from 199.232.81.140: icmp_seq=2 ttl=63 time=12.5 ms
^C
--- 199.232.81.140 ping statistics ---
2 packets transmitted, 2 received, 0% packet loss, time 1002ms
rtt min/avg/max/mdev = 12.447/12.468/12.490/0.021 ms

################################################################################

PING <IP> (<IP>) <PAYLOAD SIZE>(<TOTAL SIZE>) bytes of data.
64 bytes from <IP>: icmp_seq=1 ttl=63 time=12.4 ms
64 bytes from <IP>: icmp_seq=2 ttl=63 time=12.5 ms
^C
--- <IP> ping statistics ---
2 packets transmitted, 2 received, 0% packet loss, time 1002ms
rtt min/avg/max/mdev = 12.447/12.468/12.490/0.021 ms

################################################################################

From 10.0.2.15 icmp_seq=45 Destination Host Unreachable

From <IP> icmp_seq=45 Destination Host Unreachable

*/

/*
	>>> if not is_ip
	
PING dualstack.reddit.map.fastly.net (199.232.81.140) 56(84) bytes of data.
64 bytes from 199.232.81.140 (199.232.81.140): icmp_seq=1 ttl=63 time=12.4 ms
64 bytes from 199.232.81.140 (199.232.81.140): icmp_seq=2 ttl=63 time=12.4 ms
^C
--- dualstack.reddit.map.fastly.net ping statistics ---
2 packets transmitted, 2 received, 0% packet loss, time 1001ms
rtt min/avg/max/mdev = 12.374/12.404/12.434/0.030 ms

PING www.google.com (216.58.213.164) 56(84) bytes of data.
64 bytes from par21s04-in-f4.1e100.net (216.58.213.164): icmp_seq=1 ttl=63 time=2.15 ms
64 bytes from par21s04-in-f164.1e100.net (216.58.213.164): icmp_seq=2 ttl=63 time=1.95 ms
^C
--- www.google.com ping statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2004ms
rtt min/avg/max/mdev = 1.951/2.019/2.153/0.094 ms

################################################################################

PING <CANON NAME> (<IP>) <PAYLOAD SIZE>(<TOTAL SIZE>) bytes of data.
64 bytes from <PTR RECORD> (<IP>): icmp_seq=1 ttl=63 time=12.4 ms
64 bytes from <PTR RECORD> (<IP>): icmp_seq=2 ttl=63 time=12.4 ms
^C
--- <CANON NAME> ping statistics ---
2 packets transmitted, 2 received, 0% packet loss, time 1001ms
rtt min/avg/max/mdev = 12.374/12.404/12.434/0.030 ms

################################################################################

From 10.0.2.15 (10.0.2.15) icmp_seq=46 Destination Host Unreachable

From <IP> (<IP>) icmp_seq=46 Destination Host Unreachable

*/

void	ft_ping_header_print(t_destination *dest)
{
	printf("PING ");
	if (!dest->is_ip)
		printf("%s", dest->canon_name);
	else
		ft_ipv4_print(ft_swap32(dest->ip));
	printf(" (");
	ft_ipv4_print(ft_swap32(dest->ip));
	printf("): 56 data bytes\n");
}

void	ft_ping_packet_print(t_ipv4_icmp_packet *pack)
{
	printf("%hd bytes ", ft_swap16(pack->ipv4.packet_length) -
		(t_u16)sizeof(t_ipv4_header));
	printf("from ");
	ft_ipv4_print(ft_swap32(pack->ipv4.source_ip));
	printf(": icmp_seq=%hd ", ft_swap16(pack->icmp.sequence));
	printf("ttl=%hhd ", pack->ipv4.ttl);
	printf("time=%.3f ms\n", (float)all.stat.delta / 1000.0f);
}

/* returns mdev in ms as float */
float	ft_mdev(t_stat *stat)
{
	float	mdev;
	float	tmp;
	long	average;

	average = (long)stat->sum_delta / (long)stat->packet_recvd;
	mdev = 0.0f;
	for (unsigned i = 0; i < stat->ad_size; ++i)
	{
		tmp = (float)((long)(stat->all_delta[i]) - average) / 1000.0f;
		mdev += tmp * tmp;
	}
	return (ft_sqrt(mdev / (float)stat->ad_size));
}

/* print tailer and exit */
void	ft_ping_tailer_print(int sig)
{
	t_u64	average;

	(void)sig;
	printf("--- ");
	if (!all.dest.is_ip)
		printf("%s", all.dest.canon_name);
	else
		ft_ipv4_print(ft_swap32(all.dest.ip));
	printf(" ping statistics ---\n");
	printf("%hu packets transmitted, %hu packets received, ", all.stat.packet_sent,
		all.stat.packet_recvd);
	if (all.stat.packet_sent == all.stat.packet_recvd)
		printf("0%% packet loss\n");
	else
		printf("%u%% packet loss\n", (all.stat.packet_sent * 100) /
		(all.stat.packet_sent - all.stat.packet_recvd));

	/* ligne RTT */
	average = all.stat.sum_delta / all.stat.packet_recvd;
	printf("round-trip min/avg/max/stddev = ");
	printf("%.3f/", (float)all.stat.min_delta / 1000.0f);
	printf("%.3f/", (float)average / 1000.0f);
	printf("%.3f/", (float)all.stat.max_delta / 1000.0f);
	printf("%.3f ms\n", ft_mdev(&all.stat));
	exit(0);
}
