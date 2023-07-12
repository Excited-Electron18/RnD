///
/// @file	     GPIOLib.h
/// @copyright   Copyright (c) 2012 Toradex AG
/// @author	     $Author: bis $
/// @version     $Rev: 1142 $ 
/// @date        $Date: 2012-11-06 12:49:03 +0100 (Tue, 06 Nov 2012) $
/// @brief	     This library allows easy access to the GPIO pins.
/// 
/// @target      PXAxx, T20
/// 

#ifndef _GPIOLIB_H_
#define _GPIOLIB_H_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

//Version Info
#define GPIO_VER_MAJ     2
#define GPIO_VER_MIN     1
#define GPIO_VER_BUILD   2

#define DIR_IN	            0
#define DIR_OUT	            1

#define GPIO_EDGE_RISING    1		
#define EDGE_RISING		    1
#define GPIO_EDGE_FALLING   2
#define EDGE_FALLING	    2
#define GPIO_EDGE_BOTH      3
#define EDGE_BOTH           3

#define MFP_PULLUP          (MFP_PULL_SEL | MFP_PULLUP_EN)
#define MFP_PULLDOWN        (MFP_PULL_SEL | MFP_PULLDOWN_EN)
#define MFP_NOPULL          MFP_PULL_SEL
#define MFP_EDGE_DISABLE    MFP_EDGE_CLEAR

#define MFP_PULL_SEL        0x8000
#define MFP_PULLUP_EN       0x4000
#define MFP_PULLDOWN_EN     0x2000
#define MFP_SLEEP_SEL       0x0200
#define MFP_SLEEP_DATA      0x0100
#define MFP_SLEEP_OE_N      0x0080
#define MFP_EDGE_CLEAR      0x0040
#define MFP_EDGE_FALL_EN    0x0020
#define MFP_EDGE_RISE_EN    0x0010

typedef struct {
	BYTE inst1; //:  8; // instance 1
	BYTE inst2; //:  8; // instance 2
  //DWORD res   : 16; // reserved
} PIN_INSTANCE;

//**************************************
///@name Tegra Specific Defines
//**************************************
///@{
//Converts a Tegra GPIO Name in a GPIONr.
//x is Port Name y is bit nr,
//e.g TEGRA_GPIONUM('w',0) is GPIO W4
#define TEGRA_GPIONUM(x,y) ((((x)-'a')*8)+y)

//Define Max lenght of the Group name
#define TEGRA_MAX_GROUPNAME 6

//Define Max number of GPIOGroups
#define TEGRA_MAX_GROUPNUM 115

#define TEGRA_NOPULL	0x00
#define TEGRA_PULLDOWN	0x01
#define TEGRA_PULLUP	0x02
///@}

void InitGPIOLib();
BOOL InitGPIOLibEx(void* pRegAdress);
void DeInitGPIOLib();

//**************************************************
/// @name Tegra Specific Functions
//**************************************************
///@{

//******************************************************************************
/// Updates the Tristate setting of a pin group of GPIO pins.
/// @param[in]	        gpioNum			GPIO Pin Number              
/// @param[in]	        tristate        (0: floating, 1:pullup, 2:pulldown) 
/// @retval		        TRUE            Success
/// @retval             FALSE           Error
///
/// Remarks:            Please note - this affects the whole pin group.
BOOL TegraSetTristatePinGroup(DWORD gpioNum, BOOL tristate);

//******************************************************************************
/// Get the Tristate setting of a pin group of GPIO pins.
/// @param[in]	        gpioNum         GPIO Pin Number
/// @retval		        1               Tristated
/// @retval             0               Active
DWORD TegraGetTristatePinGroup(DWORD gpioNum);

//******************************************************************************
/// Set the Pullup/Pulldown setting of a pin group of GPIO pins.
/// @param[in]	        gpioNum			GPIO Pin Number             
/// @param[in]	        pullState       (0: nothing, 1:pullup, 2:pulldown)             
/// @retval		        TRUE            Success
/// @retval             FALSE           Error
///
/// Remarks:            Please note - this affects the whole pin group.
BOOL TegraSetPullStatePinGroup(DWORD gpioNum, DWORD pullState);

//******************************************************************************
/// Get the Pullup/Pulldown setting of a GPIO pin group
/// @param[in]	        gpioNum			GPIO Pin Number
/// @retval		        Pull status    (0: nothing, 1:pullup, 2:pulldown)          
DWORD TegraGetPullStatePinGroup(DWORD gpioNum);

//******************************************************************************
/// Get the Pin Group Name of a GPIO pin.
/// @param[in]	        gpioNum			GPIO Pin Number
/// @param[out]         *groupName	    Ascii string containing the name of the Pin group max TEGRA_MAX_GROUPNAME characters.           
/// @retval		        TRUE            Success
/// @retval             FALSE           Error
BOOL TegraGetPinGroupName(DWORD gpioNum, char *groupName);
///@}

//**************************************************
/// @name General Functions
//**************************************************
///@{

//******************************************************************************
/// Get the Input/Output direction of the specified SODIMM Pin Number
/// @param[in]	        pinNum          SODIMM Pin Number                           
/// @retval		        GPIO Direction  (0: Input, 1: Output)           
DWORD GetPinDir(DWORD pinNum);

//******************************************************************************
/// Get the Input/Output direction of the specified GPIO Pin Number
/// @param[in]	        gpioNum         GPIO Pin Number             
/// @retval		        GPIO Direction  (0: Input, 1: Output)          
DWORD GetGPIODir(DWORD gpioNum);

//******************************************************************************
/// Set the Input/Output direction of the specified SODIMM Pin Number
/// @param[in]	        ponNum          SODIMM Pin Number              
/// @param[in]	        dirOut          Direction (0: Input, 1:Output)           
void SetPinDir(DWORD gpioNum, BOOL dirOut);

//******************************************************************************
/// Set the Input/Output direction of the specified GPIO Pin Number
/// @param[in]	        gpioNum:        GPIO Pin  Number
/// @param[in]	        dirOut          Direction (0: Input, 1:Output)          
void SetGPIODir(DWORD gpioNum, BOOL dirOut);

//******************************************************************************
/// Get the Alternative Function setting of the specified GPIO Pin Number
/// @param[in]	        gpioNum:        GPIO Pin Number            
/// @retval		        Alternative Function Setting Number           
///
/// Remarks:            On the Tegra, function can return -1 (0xFFFFFFFF)
DWORD GetGPIOAltFn(DWORD gpioNum);

//******************************************************************************
/// Get the Alternative Function setting of the specified SODIMM Pin Number
/// @param[in]	        pinNum          SODIMM Pin Number            
/// @retval		        Alternative Function Setting Number              
///
/// Remarks:            On the Tegra, function can return -1 (0xFFFFFFFF)
DWORD GetPinAltFn(DWORD pinNum);

//******************************************************************************
/// Set the Alternative Function setting of the specified SODIMM Pin Number
/// @param[in]	        pinNum:         SODIMM Pin Number              
/// @param[in]	        altFn:	        Alternative Function Setting, -1 does always mean GPIO Function, (You need to use -1 on the Tegra if you like to set a pin as GPIO)
/// @param[in]          dirOut:         GPIO Direction [False: Input, True: Output]             
/// @retval		        TRUE            Success
/// @retval             FALSE           Error          
BOOL SetPinAltFn(DWORD pinNum, DWORD altFn, BOOL dirOut);

//******************************************************************************
/// Set the Alternative Function setting of the specified GPIO Pin Number
/// @param[in]	        gpioNum:        GPIO Number              
/// @param[in]	        altFn:	        Alternative Function Setting, -1 does always mean GPIO Function,(You need to use -1 on the Tegra if you like to set a pin as GPIO)
/// @param[in]          dirOut:         GPIO Direction [False: Input, True: Output]           
void SetGPIOAltFn(DWORD gpioNum, DWORD altFn, BOOL dirOut);

//******************************************************************************
/// Get the MRPReg setting of the specified GPIO Pin Number
/// @param[in]	        gpioNum:        GPIO Number              
/// @retval		        MFPReg data
DWORD GetGPIOMFPReg(DWORD gpioNum);

//******************************************************************************
/// Set the MRPReg setting of the specified GPIO Pin Number
/// @param[in]	        gpioNum:        GPIO Number              
/// @param[in]	        mfpRegVal:      MFPREg Data             
void SetGPIOMFPReg(DWORD gpioNum, DWORD mfpRegVal);

//******************************************************************************
/// Get the logic level of the specified SODIMM Pin Number
/// @param[in]	        pinNum          Sodimm Pin Number             
/// @retval		        Pin Level       (False: Logic Low, True: Logic High)           
BOOL GetPinLevel(DWORD pinNum);

//******************************************************************************
/// Get the logic level of the specified GPIO Pin Number
/// @param[in]	        gpioNum         GPIO Pin Number
/// @retval		        GPIO Level      (False: Logic Low, True: Logic High) 
BOOL GetGPIOLevel(DWORD gpioNum);

//******************************************************************************
/// Set the logic level of the specified SODIMM Pin Number
/// @param[in]	        pinNum          SODIMM Pin. Number            
/// @param[in]	        val             [0: Logic Low   >0: Logic High]            
/// @retval		        TRUE            Success
/// @retval             FALSE           Error 
BOOL SetPinLevel(DWORD pinNum, DWORD val);

//******************************************************************************
/// Set the Logic level of a GPIO Pin
/// @param[in]	        gpioNum         GPIO Pin Number              
/// @param[in]	        val             [0: Logic Low   >0: Logic High]            
void SetGPIOLevel(DWORD gpioNum, DWORD val);

//******************************************************************************
/// Get the GPIO Edge detect
/// @param[in]	        gpioNum         GPIO Pin Number            
/// @retval		        [EDGE_RISING(1): rising edge, EDGE_FALLING(2): falling edge]              
DWORD GetGPIOEdgeDetect(DWORD gpioNum);

//******************************************************************************
/// Set the GPIO Pin Edge Detect 
/// @param[in]	        gpioNum         GPIO Pin Number             
/// @param[in]	        edge            [EDGE_RISING(1): rising edge, EDGE_FALLING(2): falling edge]          
void SetGPIOEdgeDetect(DWORD gpioNum, DWORD edge);

//******************************************************************************
/// Get GPIO Pin Edge Status
/// @param[in]	        gpioNum         GPIO Pin Number                        
/// @retval		        Edge Status (0: Cleared, 1: Set)         
BOOL GetGPIOEdgeStatus(DWORD gpioNum);

//******************************************************************************
/// Clears GPIO Pin Edge Status
/// @param[in]	        gpioNum         GPIO Pin Number                                    
void ClearGPIOEdgeStatus(DWORD gpioNum);

//******************************************************************************
/// Gets GPIO from SODIMM or Extension Pin.
/// @param[in]	        pin                     Pin Number (SODIMM pin or extension connector pin)              
/// @param[in]	        extensionConnector      FALSE:SODIMM pin, TRUE:Extension connector
/// @param[out]         gpio                    gpio Number with second instance
/// @retval		        TRUE            Success
/// @retval             FALSE           Error            
///
BOOL GetGPIOFromPin(DWORD pin, BOOL extensionConnector, PIN_INSTANCE *gpio);

//******************************************************************************
/// Gets the Alternative Function Status of a GPIO Pin
/// @param[in]	        gpioNum:	GPIO Pin Number           
/// @retval		        Alternative Function Status Code
/// @retval             Normal case 0;
/// @retval             No GPIO Function: -1;
///
DWORD GetGPIOFunctionalityAltFn(DWORD gpioNum);

//******************************************************************************
/// Outputs library version
/// @param[out] verMaj  Major version number. Set this parameter to NULL if not required
/// @param[out] verMin  Minor version number. Set this parameter to NULL if not required
/// @param[out] build   Build number.         Set this parameter to NULL if not required
void GPIOGetLibVersion(DWORD *pVerMaj, DWORD *pVerMin, DWORD *pBuild);
///@}

#ifdef __cplusplus
}
#endif

#endif //_GPIOLIB_H_