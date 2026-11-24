#ifndef __LGE_BOARD_E0EU_H
#define __LGE_BOARD_E0EU_H

/* ARM9 function declarations for DIAG */
extern PACK(void *) diagpkt_alloc (diagpkt_cmd_code_type code, unsigned int length);
extern PACK(void *) diagpkt_free (PACK(void *)pkt);
extern void send_to_arm9(void *pReq, void *pRsp);
extern void lge_write_block(unsigned int bytes_pos, unsigned char *buf, size_t size);
extern int boot_info;
extern unsigned int srd_bytes_pos_in_emmc;
extern unsigned char *load_srd_base;
extern unsigned char *load_srd_shard_base;
extern unsigned char *load_srd_kernel_base;

#endif /* __LGE_BOARD_E0EU_H */
