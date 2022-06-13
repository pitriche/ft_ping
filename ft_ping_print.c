#include "ft_ping.h"	/* t_ipv4_header */
#include "libft.h"		/* putstr_fd */
#include <stdlib.h>		/* exit */
#include <stdio.h>		/* printf */

/* printf an ipv4 address */
void	ft_ipv4_print(t_u32 addr)
{
	printf("%hhu.%hhu.%hhu.%hhu", addr >> 24, addr >> 16, addr >> 8, addr);
}

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

void	ft_icmp_header_print(t_icmp_header *head)
{
	printf("icmp header:\n");
	printf("Type:%hhd    | Code:%hhd\n", head->type, head->code);
	printf("pid:%5u | Sequence:%hu\n", ft_swap16(head->pid),
		ft_swap16(head->sequence));
	printf("checksum>%x\n", ft_swap16(head->checksum));
}

void	ft_ping_packet_print(t_ipv4_icmp_packet *pack)
{
	/*
	64 bytes from 93.184.216.34 (93.184.216.34): icmp_seq=1 ttl=63 time=87.3 ms
	*/


	printf("%hd bytes ", ft_swap16(pack->ipv4.packet_length) -
		(t_u16)sizeof(t_ipv4_header));
	printf("from ");

	//
	printf("<reverse dns> (");
	//

	ft_ipv4_print(ft_swap32(pack->ipv4.source_ip));
	printf("): icmp_seq=%hd ", ft_swap16(pack->icmp.sequence));
	printf("ttl=%hhd ", pack->ipv4.ttl);
	printf("time=%.1f ms\n", 666.0f);
}
