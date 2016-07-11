/******************************************************************************
* File       : MOE_Timer.h
* Function   : Provide timer services.
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
* History    :  No.  When           Who           What
*               1    06/May/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_TIMER_H_
#define _MOE_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_TIMER                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_TIMER     /* According the set from project_config.h */
#endif

#ifndef PF_TIMER_SRC
#define PF_TIMER_SRC PF_TIMER_SRC
typedef uint32 (*PF_TIMER_SRC)(void);
#endif

typedef uint32 (*PF_TIMER_CB)(void *pPara);

/*******************************************************************************
* Structure  : T_TIMER
* Description: Structure of timer.
* Memebers   : PF_TIMER_CB  pfTmCallback;                       Callback when time is up 
*              void        *pPara;                              Parameters for callback  
*              uint32       u32TmStart;     0~0xFFFFFFFF        Start time point         
*              uint32       u32TmOut;       0~0xFFFFFFFF        Timeout time             
*              uint16       u16Cnt;         0xFFFF              Periodic
*                                           0~0xFFFE            Counts to start the timer  
*******************************************************************************/
typedef struct _T_TIMER
{
#ifdef __TIMER_CALLBACK_SUPPORTED
    PF_TIMER_CB  pfTmCallback;            /* Callback when time is up */
    void        *pPara;                   /* Parameters for callback  */
#endif
    uint32       u32TmStart;              /* Start time point         */
    uint32       u32TmOut;                /* Timeout time             */
    uint16       u16Cnt;                  /* Count to start the timer */
    uint16       u16Evt;                  /* Timeout event to be set  */
    uint8        u8TaskID;                /* Timeout event task ID    */
}T_TIMER;


typedef struct _T_TIMER_NODE
{
    struct _T_TIMER_NODE  *ptNext;    /* Pointer for next timer node */
    T_TIMER                tTimer;    /* Timer data of such node     */
}T_TIMER_NODE;

/* MACRO */
#define MOE_TMR_INFINITE_CNT   (0xFFFF)     /* Infinite restart count  */


/******************************************************************************
* Name       : uint8 Moe_Timer_Init(PF_TIMER_SRC pfSysTm)
* Function   : Init MOE timer
* Input      : PF_TIMER_SRC pfSysTm   Funtion which returns system time
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint8 Moe_Timer_Init(PF_TIMER_SRC pfSysTm);

/******************************************************************************
* Name       : T_TIMER_NODE* Moe_Timer_Start(uint8 u8TaskID, uint16 u16Evt, uint16 u16Cnt, uint32 u32TmOut)
* Function   : Start a timer
* Input      : T_TIMER *ptTm     Pointer of timers set by user.
* Output:    : None
* Return     : NULL           Fail to start a timer.
*              T_TIMER_NODE*  The pointer of the timer which is started.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Start(T_TIMER *ptTm);

/******************************************************************************
* Name       : T_TIMER_NODE* Moe_Timer_Periodic(uint32 u32TmOut)
* Function   : Start a timer for current task and set "EVENT_DELAY"
* Input      : uint32 u32TmOut   0~2^32   Time out in ms
* Output:    : None
* Return     : NULL           Fail to start a timer.
*              T_TIMER_NODE*  The pointer of the timer which is started.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 23rd Jun 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Periodic(uint32 u32TmOut);

/******************************************************************************
* Name       : T_TIMER_NODE* Moe_Timer_Delay(uint32 u32TmOut)
* Function   : Start a timer for current task and set "EVENT_DELAY"
* Input      : uint32 u32TmOut   0~2^32   Time out in ms
* Output:    : None
* Return     : NULL           Fail to start a timer.
*              T_TIMER_NODE*  The pointer of the timer which is started.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 23rd Jun 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Delay(uint32 u32TmOut);

/******************************************************************************
* Name       : T_TIMER_NODE* Moe_Timer_Easy_Start(uint8 u8DesTask, uint8 u8Evt,uint32 u32TmOut)
* Function   : Start a timer for current task and set "EVENT_DELAY"
* Input      : uint8 u8DesTask   1~254    The destination task ID
*              uint8 u8Evt       0~255    The event which will be create when time is up.
*              uint32 u32TmOut   0~2^32   Time out in ms
* Output:    : None
* Return     : NULL           Fail to start a timer.
*              T_TIMER_NODE*  The pointer of the timer which is started.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 23rd Jun 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Easy_Start(uint8 u8DesTask, uint8 u8Evt,uint32 u32TmOut);


/******************************************************************************
* Name       : T_TIMER_NODE* Moe_Timer_Stop(T_TIMER_NODE* ptNode)
* Function   : Stop a started timer.
* Input      : T_TIMER_NODE* ptNode  The pointer of node to be stopped
* Output:    : None
* Return     : NULL           Fail to stop a timer.
*              T_TIMER_NODE*  The pointer of the timer which is stopped.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Stop(T_TIMER_NODE* ptNode);




/******************************************************************************
* Name       : static T_TIMER_NODE *Moe_Timer_Find(T_TIMER_NODE* ptNode)
* Function   : Try to find a node.
* Input      : T_TIMER_NODE* ptNode  The pointer of node to be found
* Output:    : None
* Return     : NULL           Fail to find the node.
*              T_TIMER_NODE*  The pointer of the founed node.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Restart(T_TIMER_NODE* ptNode);


/******************************************************************************
* Name       : uint8 Moe_Timer_Process(void)
* Function   : Main process for timer updating.
* Input      : None
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint8 Moe_Timer_Process(void);

/******************************************************************************
* Name       : uint16 Moe_Timer_Test_Cnt(void)
* Function   : Get the count of timers
* Input      : None
* Output:    : None
* Return     : uint16   The count of timers
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint16 Moe_Timer_Test_Cnt(void);

/******************************************************************************
* Name       : void Moe_Timer_Test_General(void)
* Function   : General test
* Input      : None
* Output:    : None
* Return     : None
* description: To be done
*              **IT IS A TEST FUNCTION! DO NOT USE IT IN YOUR APPLICATION!**
* Version    : V1.00
* Author     : Ian
* Date       : 9th May 2016
******************************************************************************/
void Moe_Timer_Test_General(void);


 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_TIMER_H_ */

/* End of file */

