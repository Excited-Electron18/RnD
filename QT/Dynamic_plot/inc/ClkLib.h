///
/// @file	     ClkLib.h
/// @copyright   Copyright (c) 2012 Toradex AG
/// @author	     $Author: gap $
/// @version     $Rev: 1138 $ 
/// @date        $Date: 2012-10-31 13:29:08 +0100 (Wed, 31 Oct 2012) $
/// @brief	     Library to manange clock settings
/// 
/// @target      PXAxxx. T20
/// 

#ifndef __CLKLIB_H__
#define __CLKLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

/// Version Info
#define CLK_VER_MAJ     1
#define CLK_VER_MIN     3
#define CLK_VER_BUILD   0

/*****************************************
/*  ClkLib
/*  Try to use the independent defines first,
/*  they will work on PXA270 and PXA3xx
/*****************************************/

// Independent stuff
#define  CKEN_PWM               0         // the same as PXA3xx CKEN_PWM_1_0
#define  CKEN_AC97              2         // AC97[2] for PXA270
#define  CKEN_SSP1             23
#define  CKEN_SSP2              3
#define  CKEN_SSP3              4
#define  CKEN_UART1             5
#define  CKEN_UART2             6
#define  CKEN_UART3             7
#define  CKEN_USBH             10
#define  CKEN_USBC             11         // the same as PXA270 CKEN_USBC_48MHZ
#define  CKEN_MMC              12         // the same as PXA3xx CKEN_MMC0
#define  CKEN_I2C              14
#define  CKEN_LCD              16
#define  CKEN_MSL              17
#define  CKEN_USIM             18         // the same as PXA3xx CKEN_USIM0 
#define  CKEN_KEYPAD           19
#define  CKEN_INTERNAL_MEM     20         // the same as PXA3xx CKEN_INTERNAL_SRAM
#define  CKEN_QUICKCAPTURE     24         // the same as PXA3xx CKEN_CIF

// PXA270 stuff
#define  CKEN_AC97CFG           1         // AC97[31] for PXA270
#define  CKEN_FFUART           CKEN_UART1
#define  CKEN_BTUART           CKEN_UART2
#define  CKEN_STUART           CKEN_UART3
#define  CKEN_I2S               8
#define  CKEN_OST               9
#define  CKEN_USBC_48MHZ       CKEN_USBC
#define  CKEN_IR               13
#define  CKEN_PWRI2C           15
#define  CKEN_MSTICK           21
#define  CKEN_MEMC             22
#define  CKEN_TPM              25

// PXA3xx stuff
#define  CKEN_PWM_2_0          CKEN_PWM
#define  CKEN_PWM_3_1           1
#define  CKEN_INTR             32
#define  CKEN_GPIO             33
#define  CKEN_1WIRE            34
#define  CKEN_HSIO2             8
#define  CKEN_MINI_IM           9
#define  CKEN_CIF              CKEN_QUICKCAPTURE
#define  CKEN_NAND             15
#define  CKEN_USB2             29
#define  CKEN_GRAPHIC          26
#define  CKEN_DMEM             21
#define  CKEN_SMEM             22
#define  CKEN_INTERNAL_SRAM    CKEN_INTERNAL_MEM
#define  CKEN_BOOTROM          25
#define  CKEN_MMC0             CKEN_MMC
#define  CKEN_MMC1             27
#define  CKEN_CONSUMER_IR      28
#define  CKEN_USIM0            CKEN_USIM
#define  CKEN_USIM1            30
#define  CKEN_MINI_LCD         31
#define  CKEN_TOUCHS           35
#define  CKEN_SSP4             36

// PXA310 stuff
#define CKEN_MMC2              35  // is called MMC3 in PXA datasheet
#define CKEN_MMC3              CKEN_MMC2
#define CKEN_VIDEO             13

#define CKEN_MAX               37

// List for devices only
// For L, don't add anything
// For H, add 32
// For U, add 64
// Tegra T20 stuff
#define PWM_CLK_TEG						(17)

// SLINK SPI Controller
#define SLINK_SPI1_CLK_TEG				(41)
#define SLINK_SPI2_CLK_TEG				(44)	
#define SLINK_SPI3_CLK_TEG				(46)	
#define SLINK_SPI4_CLK_TEG				(68)
#define SERIAL_FLASH_SPI1_CLK_TEG		(43)

// IIC
#define IIC1_CLK_TEG					(12)
#define IIC2_CLK_TEG					(54)
#define IIC3_CLK_TEG					(67)

// SNOR
#define SNOR_CLK_TEG					(42)

//******************************************************************************
/// Initialises the library, call before calling any other functions
void InitClkLib(void);

//******************************************************************************
/// Releases the library resources, call when finsihed with the library
void DeInitClkLib (void);

//******************************************************************************
/// Enables / disables clock for a specific peripheral.
/// @param[in]	        clkID	        Clock ID (refer to ClkLib.h)           
/// @param[in]	        value	        TRUE: Enable clock, FALSE: Disable clock
/// @retval		        TRUE: Success, FALSE: Error
BOOL SetClk(DWORD clkID, BOOL value);

//******************************************************************************
/// Enables / disables clock for a specific peripheral - extended version.
/// @param[in]	        clkID	        Clock ID (refer to ClkLib.h)            
/// @param[in]	        value	        TRUE for enable clock, FALSE for disable clock
/// @param[in]	        ClkDivider	    Clock Divisor, set to -1 to use default  (Tegra only)
/// @retval		        TRUE: Success, FALSE: Error
BOOL SetClkEx ( DWORD clkID, BOOL value, DWORD ClkDivider);

//******************************************************************************
/// Request clock enable status for a specific peripheral
/// @param[in]	        clkID	        Clock ID (refer to ClkLib.h)      
/// @retval		        TRUE: Success, FALSE: Error
BOOL GetClkEn ( DWORD clkID );

//******************************************************************************
/// Delay with microsecond resolution.
/// @param[in]	        uSec            Number of microseconds.          
void Waitus(UINT32 uSec);

//******************************************************************************
/// Returns the library Version.
/// @param[out]         pVerMaj         Returns the major version number. Set this parameter to NULL if not required.
/// @param[out]         pVerMin         Returns the minor version number. Set this parameter to NULL if not required.
/// @param[out]         pBuild          Returns the build number.         Set this parameter to NULL if not required.
void CLKGetLibVersion(DWORD *pVerMaj, DWORD *pVerMin, DWORD *pBuild);

#ifdef __cplusplus
}
#endif

#endif  // __CLKLIB_H__
