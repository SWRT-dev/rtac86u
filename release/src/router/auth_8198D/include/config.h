/* include/config.h.  Generated automatically by configure.  */
/* include/config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* #undef LIBNET_BSDISH_OS */
/* #undef LIBNET_BSD_BYTE_SWAP */
/* #undef DLPI_DEV_PREFIX */
/* #undef HAVE_DEV_DLPI */
/* #undef HAVE_SOCKADDR_SA_LEN */
/* #undef HAVE_SOLARIS */
/* #undef HAVE_DLPI */
/* #undef HAVE_PF_PACKET */
/* #undef HAVE_STRUCT_IP_CSUM */
#define HAVE_LIB_PCAP 1
/* #undef LBL_ALIGN */
/* #undef STUPID_SOLARIS_CHECKSUM_BUG */
#define _BSD_SOURCE 1
#define __BSD_SOURCE 1
#define __FAVOR_BSD 1

#if 0  // move define to Makefile
#undef LIBNET_LIL_ENDIAN 
#define  LIBNET_BIG_ENDIAN 1
/*#define LIBNET_LIL_ENDIAN 1*/
#endif

/* Define if you have the strerror function.  */
#define HAVE_STRERROR 1

/* Define if you have the <net/ethernet.h> header file.  */
#define HAVE_NET_ETHERNET_H 1

/* Define if you have the <sys/bufmod.h> header file.  */
/* #undef HAVE_SYS_BUFMOD_H */

/* Define if you have the <sys/dlpi_ext.h> header file.  */
/* #undef HAVE_SYS_DLPI_EXT_H */

/* Define if you have the <sys/sockio.h> header file.  */
/* #undef HAVE_SYS_SOCKIO_H */

/* Define if you have the nsl library (-lnsl).  */
/* #undef HAVE_LIBNSL */

/* Define if you have the socket library (-lsocket).  */
/* #undef HAVE_LIBSOCKET */
