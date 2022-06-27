/* Includes ------------------------------------------------------------------*/
#include "usbd_pwr.h"

struct
{
  __IO RESUME_STATE eState;
  __IO uint8_t bESOFcnt;
}
ResumeS;

__IO uint32_t remotewakeupon=0;

{{usbd_pwr_c_extern}}

void Suspend(void)
{

}


void Resume_Init(void)
{

}

{{usbd_pwr_c_Remote_Wakeup}}

void Resume(RESUME_STATE eResumeSetVal)
{

}

void Leave_LowPowerMode(void)
{

}
