/*
 ** All rights reserved – Nex-G Exuberant Solutions Private Limited.                                                               
 ** File Name    : harq_function.h                                                                                         
 ** Module Name  : MAC-E-MULTIPLEX                                                                                                       
 ** Project Name : MAC-ES-E UE Side                                                                                                 
 ** Description  : definition of mac_e_e_harq() function which is called by mac_es_e_harq_rcv.c file                             
 ** Author       : MAC-ES-E Project Team                                                                                            
 ** Start date   : 04-12-2012                                                                                                       
 ** End date     : 05-12-2012                                                                                                      
 */
#include "../mac_es_e_include/header.h"
#include "../mac_es_e_include/structures.h"
#include "../mac_es_e_include/wrapper.h"
#define DEBUG
typedef struct			/* declare and typedef structure for mac_e_pdu_tbs_rcv */
{
  long int mtype;
  mac_e_pdu mac_e_pdu_send_tbsONE;
  char padding[TWO];
} mac_e_pdu_tbs_rcv;
typedef struct			/* declare and typedef structure for mac_e_pdu_tbs_rcv */
{
  long int mtype;
  mac_e_pdu harq_data;
  char padding[TWO];
  unsigned int rsn:TWO;
} harq_send_t;
harq_send_t *harq_send;		/* Define the Structure's pointer of harq_send_t type */
mac_e_pdu_tbs_rcv *mac_e_pdu_rcvONE;	/* Define the Structure's pointer of mac_e_pdu_tbs_rcv type */

int
harq_func ()			/* start of mac_es_e_harq() Function definition */
{
  int qidONE = ZERO;		/* Define and initiate an integer type of message queue id */
  int qidTWO = ZERO;		/* Define and initiate an integer type of message queue id */

  int msgrcvONE = ZERO;		/* Define variables name & type integer which will use in code */
  int msgsndONE = ZERO;		/* Define variables name & type integer which will use in code */
  int mac_d_sdu_size;		/* Define variables name & type integer which will use in code */
  char current_tx_nb = ZERO;	/* Define and initiate the  variables of char which will use in code */
  char current_rsn = ZERO;	/* Define variables name & type integer which will use in code */

  FILE *fp_harq;

  fp_harq = nexg_fopen ("../logfiles/harq_mac_es_e.txt", "a");	/*creation of a file which will use in code */

  nexg_fprintf (fp_harq, "\t\nDATA CREATED ON:-%s\t\n\n", __TIMESTAMP__);	/*print date and time in file */
  nexg_fprintf (fp_harq, "%s", "IE's COPIED ARE:-\n");

  nexg_delay (ONE);
#ifdef DEBUG
  nexg_printf
    ("\t\t\t\t_________________________________________________________\n");
  nexg_printf
    ("\t\t\t\t======================||mac_es_e_harq_function||=========\n");
  nexg_printf
    ("\t\t\t\t_________________________________________________________\n");
  nexg_printf ("\n");
  nexg_printf ("\n");
  nexg_printf
    ("\t\t\t\t _______________________________________________________________________\n");
#endif

  nexg_printf ("\t\t\t\t|The name of this file is:-%s\t|\n", __FILE__);	/*predefined macros to print file name */
  nexg_printf ("\t\t\t\t|The Current Time is:-%s\t\t\t\t|\n", __TIMESTAMP__);	/*predefined macros to print the time */
  nexg_printf
    ("\t\t\t\t|_______________________________________________________________________|\n");

/* HARQ process start */


  mac_e_pdu_rcvONE = (mac_e_pdu_tbs_rcv *) nexg_malloc (sizeof (mac_e_pdu_tbs_rcv));	/* allocate memory to  
										   mac_e_pdu_tbs_rcv type structure pointer */
  harq_send = (harq_send_t *) nexg_malloc (sizeof (harq_send_t));	/* allocate memory to  harq_send_t type structure pointer */

  nexg_memset (mac_e_pdu_rcvONE, ZERO, sizeof (mac_e_pdu_tbs_rcv));	/* fills memory with a constant byte in mac_e_pdu_rcvONE */
  nexg_memset (harq_send, ZERO, sizeof (harq_send_t));	/* fills memory with a constant byte in harq_send */

  qidONE = nexg_msgget (FORTY_FIVE, IPC_CREAT | PERMISSION);
  if (qidONE < ZERO)		/*start of  if use to check return value of msgget function used above */
    {

      nexg_perror ("msgget failed");
      return (ZERO);
    }				/*end of  if use to check return value of msgget function used above */

  msgrcvONE =
    nexg_msgrcv (qidONE, mac_e_pdu_rcvONE, ONE_HUNDRED_SEVENTY_SIX, TWO, ZERO);

  if (msgrcvONE < ZERO)		/*start of  if use to check return value of msgrcv function used above */
    {
      nexg_perror ("msgrcv failed");
      return (ZERO);
    }				/*end of  if use to check return value of msgrcv function used above */

  nexg_delay (ONE);
#ifdef DEBUG
  nexg_printf
    ("\n\t-----------------------------------mac-e PDU received into HARQ PROCESS-------------------------------------------\n");
  nexg_printf
    ("\n\t-----------------------------------MAC-E--------------------------------------------------------------------------\n");
  nexg_printf
    ("\n\t___________________________________HARQ ENTITY____________________________________________________________________\n");
  nexg_printf
    ("\n\t___________________________________HARQ ENTITY____________________________________________________________________\n");

  nexg_printf
    ("\t\t\t\t_________________________________________________________\n");
  nexg_printf
    ("\t\t\t\t======================||mac_es_e_harq_function||========= \n");
  nexg_printf
    ("\t\t\t\t_________________________________________________________\n");
  nexg_printf ("\n");

  nexg_printf
    ("\n\t-----------------------------------PHYSICAL LAYER-----------------------------------------------------------------\n");
#endif

  nexg_fprintf (fp_harq, "\n\n\tmac_e pdu receivied into harq entity\n\n");
  nexg_delay (ONE);
  nexg_printf ("\n\n\tDDI and N for first mac_e_sdu is as below\n ");
  nexg_fprintf (fp_harq,
		"\n\n\t DDI and N for first mac_e_sdu is as below\n ");
  nexg_delay (ONE);
  nexg_printf ("\n\tlogical channel\t\t=%d",
	       mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
	       mac_e_header_ONE.mac_e_ddi.logical_channel_type);
  nexg_fprintf (fp_harq, "\n\tlogical channel=%d",
		mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
		mac_e_header_ONE.mac_e_ddi.logical_channel_type);
  nexg_delay (ONE);
  nexg_printf ("\n\tmacdflow\t\t=%d",
	       mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
	       mac_e_header_ONE.mac_e_ddi.mac_d_flow);
  nexg_fprintf (fp_harq, "\n\tmacdflow=%d",
		mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
		mac_e_header_ONE.mac_e_ddi.mac_d_flow);
  if (mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.mac_e_header_ONE.mac_e_ddi.mac_es_sdu_size == ONE)/* if start to assign mac-es sdu size */
    {
      mac_d_sdu_size = FORTY_TWO;
    }				/* if end to assign mac-es sdu size */
  nexg_delay (ONE);
  nexg_printf ("\n\tmac_es_sdu_size\t\t=%d", mac_d_sdu_size);
  nexg_fprintf (fp_harq, "\n\tmac_es_sdu_size=%d", mac_d_sdu_size);
  nexg_delay (ONE);
  nexg_printf ("\n\t----n----\t\t=%d",
	       mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.mac_e_header_ONE.n);
  nexg_fprintf (fp_harq, "\n\t----n----=%d",
		mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.mac_e_header_ONE.n);
  nexg_delay (ONE);
  nexg_printf ("\n\n\tDDI and N for second mac_e_sdu is as below ");
  nexg_fprintf (fp_harq,
		"\n\n\t DDI and N for second mac_e_sdu is as below ");
  nexg_delay (ONE);
  nexg_printf ("\n\tlogical channel\t\t=%d",
	       mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
	       mac_e_header_TWO.mac_e_ddi.logical_channel_type);
  nexg_fprintf (fp_harq, "\n\tlogical channel\t\t=%d",
		mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
		mac_e_header_TWO.mac_e_ddi.logical_channel_type);
  nexg_delay (ONE);
  nexg_printf ("\n\tmacdflow\t\t=%d",
	       mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
	       mac_e_header_TWO.mac_e_ddi.mac_d_flow);
  nexg_fprintf (fp_harq, "\n\tmacdflow=%d",
		mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
		mac_e_header_TWO.mac_e_ddi.mac_d_flow);
  if (mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.mac_e_header_TWO.mac_e_ddi.
      mac_es_sdu_size == ONE)
    {				/* if start to assign mac-es sdu size */
      mac_d_sdu_size = FORTY_TWO;
    }				/* if end to assign mac-es sdu size */
  nexg_delay (ONE);
  nexg_printf ("\n\tmac_es_sdu_size\t\t=%d", mac_d_sdu_size);
  nexg_fprintf (fp_harq, "\n\tmac_es_sdu_size\t\t=%d", mac_d_sdu_size);
  nexg_delay (ONE);
  nexg_printf ("\n\t----n----\t\t=%d",
	       mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.mac_e_header_TWO.n);
  nexg_fprintf (fp_harq, "\n\t----n----=%d",
		mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.mac_e_header_TWO.n);
  nexg_delay (ONE);
  nexg_printf ("\n\n\tTSN and data for first mac_e_sdu is as below ");
  nexg_fprintf (fp_harq,
		"\n\n\t TSN and data for first mac_e_sdu is as below ");
  nexg_delay (ONE);
  nexg_printf ("\n\tmacesduONETSN\t\t=%d",
	       mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.macesdu_ONE.header);
  nexg_fprintf (fp_harq, "\n\tmacesduONETSN\t\t=%d",
		mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.macesdu_ONE.header);
  nexg_delay (ONE);
  nexg_printf ("\n\ttmacesduONEDATA\t\t=%s",
	       mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
	       macesdu_ONE.mac_es_sdu);
  nexg_fprintf (fp_harq, "\n\ttmacesduONEDATA=%s",
		mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
		macesdu_ONE.mac_es_sdu);
  nexg_delay (ONE);
  nexg_printf ("\n\n\tTSN and data for second mac_e_sdu is as below ");
  nexg_fprintf (fp_harq,
		"\n\n\t TSN and data for second mac_e_sdu is as below ");
  nexg_delay (ONE);
  nexg_printf ("\n\tmacesduTWOTSN\t\t=%d",
	       mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.macesdu_TWO.header);
  nexg_fprintf (fp_harq, "\n\tmacesduTWOTSN=%d",
		mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.macesdu_TWO.header);
  nexg_delay (ONE);
  nexg_printf ("\n\tmacesduTWODATA\t\t=%s\n\n\n",
	       mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
	       macesdu_TWO.mac_es_sdu);
  nexg_printf ("\n\tmessage have been send from HARQ to Physical Layer");
  nexg_fprintf (fp_harq, "\n\tmacesduTWODATA=%s\n\n\n",
		mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE.
		macesdu_TWO.mac_es_sdu);
  harq_send->harq_data = mac_e_pdu_rcvONE->mac_e_pdu_send_tbsONE;
  nexg_strcpy (harq_send->padding, mac_e_pdu_rcvONE->padding);
  harq_send->rsn = current_rsn;
  harq_send->mtype = TWO;


  qidTWO = nexg_msgget (FIFTY, IPC_CREAT | PERMISSION);

  if (qidTWO < ZERO)		/*start of  if use to check return value of msgget function used above */
    {
      nexg_perror ("msgget failed");
      return (ZERO);
    }				/*end of  if use to check return value of msgget function used above */
/************************************************************************************************************************************
  * System Call: msgsnd														    * 																	 
  * Purpose : To send message into message queue.										    * 				
  * Inputs  : message queue identifier returned from a msgget function,pointer to the message to be sent,size of the message 
		pointed to by msg_ptr,msgflg.				                     			                    *
                         
  * Return  : On success, msgsnd returns zero,and returns negative number on error. 						    *
		    									                                  ************************************************************************************************************************************/
  msgsndONE = nexg_msgsnd (qidTWO, harq_send, ONE_HUNDRED_SEVENTY_SEVEN, ZERO);
  if (msgsndONE < ZERO)		/*start of  if use to check return value of msgsnd function used above */
    {
      nexg_perror ("msgsnd failed");
      return (ZERO);
    }				/*end of  if use to check return value of msgsnd function used above */


  current_rsn++;		/*increment counters */
  current_tx_nb++;

   nexg_fclose (fp_harq);		/*close a file pointer */

  nexg_free (mac_e_pdu_rcvONE);	/*freeing memory */
  nexg_msgctl (qidONE, IPC_RMID, ZERO);		/*function call of msgnexg_ctl() function which is defined in nexg_msgctl.c header file */
  nexg_printf
    (".............................................ALL POINTERS ARE FREED...................................................\n");
  nexg_printf ("\t Total no of lines in harq_fun.c file %d\n", __LINE__);	/* predefined macros to print number of lines */

  return (ZERO);		/* returning control to the main function in mac_es_e_harq_rcv.c file */
}				/* end of mac_es_e_harq() Function definition */

/************************************************************************************************************************************
*                                              end of file harq_function.c	                                                    *
************************************************************************************************************************************/
