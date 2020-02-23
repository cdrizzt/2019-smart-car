/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,Öğ·É¿Æ¼¼
 * All rights reserved.
 * ¼¼ÊõÌÖÂÛQQÈº£º179029047
 *
 * ÒÔÏÂËùÓĞÄÚÈİ°æÈ¨¾ùÊôÖğ·É¿Æ¼¼ËùÓĞ£¬Î´¾­ÔÊĞí²»µÃÓÃÓÚÉÌÒµÓÃÍ¾£¬
 * »¶Ó­¸÷Î»Ê¹ÓÃ²¢´«²¥±¾³ÌĞò£¬ĞŞ¸ÄÄÚÈİÊ±±ØĞë±£ÁôÖğ·É¿Æ¼¼µÄ°æÈ¨ÉùÃ÷¡£
 *
 * @file       		MK60_lptmr
 * @company	   		³É¶¼Öğ·É¿Æ¼¼ÓĞÏŞ¹«Ë¾
 * @author     		Go For It(1325536866)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.17
 * @Target core		MK66FX
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-09-19
 ********************************************************************************************************************/
 
 
 
#ifndef _MK60_lptmr_h
#define _MK60_lptmr_h


#include "misc.h"
#include "common.h"
#include "MK60_port.h"
#include "MK60_gpio.h"
#include "MK60_port_cfg.h"


typedef enum
{
    lpt0_alt1 = 1,      // A19
    lpt0_alt2 = 2       // C5
} LPT0_ALTn;

typedef enum
{
    LPT_Rising  = 0,    //ÉÏÉıÑØ´¥·¢
    LPT_Falling = 1     //ÏÂ½µÑØ´¥·¢
} LPT_CFG;


#define LPTMR_Flag_Clear()  (LPTMR0->CSR |= LPTMR_CSR_TCF_MASK)         //Çå³ıLPT±È½Ï±êÖ¾Î»




void lptmr_pulse_init(LPT0_ALTn altn, uint16 count, LPT_CFG cfg);
uint16 lptmr_pulse_get(void);
void lptmr_pulse_clean(void);


#endif
/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,é€é£ç§‘æŠ€
 * All rights reserved.
 * æŠ€æœ¯è®¨è®ºQQç¾¤ï¼š179029047
 *
 * ä»¥ä¸‹æ‰€æœ‰å†…å®¹ç‰ˆæƒå‡å±é€é£ç§‘æŠ€æ‰€æœ‰ï¼Œæœªç»å…è®¸ä¸å¾—ç”¨äºå•†ä¸šç”¨é€”ï¼Œ
 * æ¬¢è¿å„ä½ä½¿ç”¨å¹¶ä¼ æ’­æœ¬ç¨‹åºï¼Œä¿®æ”¹å†…å®¹æ—¶å¿…é¡»ä¿ç•™é€é£ç§‘æŠ€çš„ç‰ˆæƒå£°æ˜ã€‚
 *
 * @file       		MK60_lptmr
 * @company	   		æˆéƒ½é€é£ç§‘æŠ€æœ‰é™å…¬å¸
 * @author     		Go For It(1325536866)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.17
 * @Target core		MK66FX
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-09-19
 ********************************************************************************************************************/
 
 
 
#ifndef _MK60_lptmr_h
#define _MK60_lptmr_h


#include "misc.h"
#include "common.h"
#include "MK60_port.h"
#include "MK60_gpio.h"
#include "MK60_port_cfg.h"


typedef enum
{
    lpt0_alt1 = 1,      // A19
    lpt0_alt2 = 2       // C5
} LPT0_ALTn;

typedef enum
{
    LPT_Rising  = 0,    //ä¸Šå‡æ²¿è§¦å‘
    LPT_Falling = 1     //ä¸‹é™æ²¿è§¦å‘
} LPT_CFG;


#define LPTMR_Flag_Clear()  (LPTMR0->CSR |= LPTMR_CSR_TCF_MASK)         //æ¸…é™¤LPTæ¯”è¾ƒæ ‡å¿—ä½




void lptmr_pulse_init(LPT0_ALTn altn, uint16 count, LPT_CFG cfg);
uint16 lptmr_pulse_get(void);
void lptmr_pulse_clean(void);


#endif
