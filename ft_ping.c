#include <sys/socket.h>	/* socket */
#include <netinet/in.h>	/* IPPROTO_ICMP */
#include <unistd.h>		/* close */
#include "libft.h"		/* ft_bzero */
#include "ft_ping.h"	/* all */


t_ping	all; /* global variable for ping */

/* return 1 if checksium is valid, and 0 if checksum is invalid */
unsigned short	ft_checkchecksum16(unsigned short *addr, unsigned size)
{
	unsigned int	res;

	res = 0;
	for (unsigned i = 0; i < size; ++i)
	// {
		res += addr[i];
	// 	printf("c>%x\n", addr[i]);
	// }
	return (~((res & 0xffff) + (res >> 16)) & 0xffff);
}

unsigned short	ft_checksum16(unsigned short *addr, unsigned size)
{
	unsigned int	res;

	res = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		res += addr[i];

		// printf(">%x\n", addr[i]);
	}
		// printf(">%x\n", res);
	res = (res & 0xffff) + ((res >> 16) & 0xffff);
	return (~res & 0xffff);
}

void	ft_ping(int ac, char **av)
{
	t_icmp_packet	pack;
	unsigned short	check;
	
	ft_ping_parse_flags(ac, av, &all.flags);
	if ((all.sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		err_quit("Can't open socket");
	// printf("%d\n", all.sock);


	ft_bzero(&pack, sizeof(t_icmp_packet));
	pack.ipv4.version_ihl	|= 4 << 4;	/* ip version 4 */
	pack.ipv4.version_ihl	|= 5;		/* 5 * 4 bytes header length */
	pack.ipv4.dscp_ecn		|= 16 << 2;	/* DSCP 010000 (16) for ping */
	pack.ipv4.dscp_ecn		|= 0;		/* no ECN */
	pack.ipv4.packet_length	= sizeof(t_icmp_packet);
	pack.ipv4.identification = 0;		/* no identification */
	pack.ipv4.flag_offset	|= 0 << 13;	/* no flags */
	pack.ipv4.flag_offset	|= 0;		/* no fragment offset */
	pack.ipv4.ttl			= 64;		/* time to live, default 64 */
	pack.ipv4.protocol		= 1;		/* 1 = ICMP */
	pack.ipv4.source_ip		= 0xff88ff88;	/*  */
	pack.ipv4.dest_ip		= 0x00770077;	/*  */
	ft_bitdump((unsigned char *)&pack, sizeof(t_ipv4_header));
	check = ft_checksum16((unsigned short *)&pack.ipv4, 10);
	pack.ipv4.header_checksum = check;
	// ft_putnbr_base_fd(pack.ipv4.header_checksum, "0123456789abcdef", 1);
	// ft_putstr("<<initial checksum\n");
	// write(1, &ac, 1);
	// printf(" ");



	// pack.ipv4.source_ip		-= 10;		/* time to live, default 64 */
	pack.ipv4.dest_ip		-= 10;		/* time to live, default 64 */

	printf("checksum>%x\n", ft_checkchecksum16((unsigned short *)&pack.ipv4, 10));

	pack.icmp.type		= 8;	/* echo request */
	pack.icmp.code		= 0;	/* no code */
	pack.icmp.checksum	= 0;	/* !!!!!!! add checksum compute !!!!!!! */
	
	
	
	ft_bitdump((unsigned char *)&pack, sizeof(t_ipv4_header));

	close(all.sock);
}