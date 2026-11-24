#ifndef __LGE_BOARD_E0EU_H
#define __LGE_BOARD_E0EU_H

/* ARM9 function declarations for DIAG */

#if defined __GNUC__
  #define PACK(x)       x __attribute__((__packed__))
  #define PACKED        __attribute__((__packed__))
#elif defined __arm
  #define PACK(x)       __packed x
  #define PACKED        __packed
#else
  #error No PACK() macro defined for this compiler
#endif

extern void *diagpkt_alloc(diagpkt_cmd_code_type code, unsigned int length);
extern void *diagpkt_free(void *pkt);
extern void send_to_arm9(void *pReq, void *pRsp);
extern void lge_write_block(unsigned int bytes_pos, unsigned char *buf, size_t size);
extern int boot_info;
extern unsigned int srd_bytes_pos_in_emmc;
extern unsigned char *load_srd_base;
extern unsigned char *load_srd_shard_base;
extern unsigned char *load_srd_kernel_base;

#endif /* __LGE_BOARD_E0EU_H */
