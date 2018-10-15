//BBA lib

#ifndef _BBA_H_
#define _BBA_H_

#include "types.h"
#include "gc_exi.h"
#include "memory.h"
#include "dprintf.h"


#define TYPE_IP			0x0800
#define TYPE_ARP		0x0806

#define ARP_REQUEST		0x0001
#define ARP_REPLY		0x0002
#define ARP_REVREQUEST	0x0003
#define ARP_REVREPLY	0x0004

#define BBA_LONGCMD		0x80000000
#define BBA_WRITE		0x40000000

#define NET_ERROR		0
#define NET_SUCCESS		1
#define NET_ARPRECV		2
#define NET_TIMEOUT		3

#define BBAMODE_10HD	0
#define BBAMODE_10FD	1
#define BBAMODE_100HD	2
#define BBAMODE_100FD	3

#define NB_BLOCKING		0
#define NB_NOBLOCKING	1
#define NB_WAITTIMEOUT	2


#define iptoi(a,b,c,d)	((a<<24)|(b<<16)|(c<<8)|(d))
#define ntohs(a)		(a&0xFFFF)
#define htons(a)		(a&0xFFFF)
#define ntohl(a)		(a)
#define htonl(a)		(a)


typedef u32 ip4;

typedef struct MACHEAD {
	u8 dst[6];
	u8 src[6];
	u16 type;
} MACHEAD;

typedef struct IPHEAD {
	u8	version;
	u8	tos;
	u16	len;
	u16	id;
	u16	fragment;
	u8	ttl;
	u8	protocol;
	u16	checksum;
	ip4	src;
	ip4	dst;
	u8	*data;
} IPHEAD;

typedef struct UDPHEAD {
	u16	src;
	u16	dst;
	u16	len;
	u16	checksum;
} UDPHEAD;

typedef struct ARPHEAD {
	u16	hw;
	u16	protocol;
	u8	hwlen;
	u8	protolen;
	u16	opcode;
	u8	*hwsrc;
	u8	*protosrc;
	u8	*hwdst;
	u8	*protodst;
} ARPHEAD;

typedef struct UDPHANDLE {
	u8		id;
	MACHEAD	mac;
	IPHEAD	ip;
	UDPHEAD	udp;
} UDPHANDLE;

typedef struct ARPHANDLE {
	u8		id;
	MACHEAD	mac;
	ARPHEAD	arp;
} ARPHANDLE;

//u8 revid;


//Low level BBA commands
void BBAWriteCmd(u8 addr, u8 *abuf, u32 size);
void BBAWriteLongCmd(u16 addr, u8 *abuf, u32 size);
void BBAReadCmd(u8 addr, u8 *abuf, u32 size);
void BBAReadLongCmd(u16 addr, u8 *abuf, u32 size);

//Low level BBA functions
void BBAReset();
u8 BBAInit(u8 bbamode);
u8 BBAGetStatus();
void BBASend(u8 *abuf, u16 size);
u8 BBARecv(u8 *abuf, u16 *size);

//'Medium-Low' level net functions
u8 NetInit(u8 bbamode, ip4 srcaddr);

u8 NetUDPOpen(UDPHANDLE *uh, u16 srcport, ip4 dstaddr, u16 dstport);
void NetUDPClose(UDPHANDLE *uh);
u8 NetUDPSend(UDPHANDLE *uh, u8 *abuf, u16 size);
u8 NetUDPRecv(UDPHANDLE *uh, u8 *abuf, u16 *size, u8 noblocking);

void __ARPBuild(ARPHANDLE *ah, u8 *abuf);
void __ARPInit(ARPHANDLE *ah, u8 *abuf);
u8 NetARPResolve(UDPHANDLE *uh);
u8 NetARPRequest(ip4 addr);
u8 NetARPReply(ARPHANDLE *ah);

char *makeip(ip4 ip);
char *makelongip(ip4 ip);


#endif //_BBA_H_
