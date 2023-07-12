///
/// @file	     CoProcLib.h
/// @copyright   Copyright (c) 2012 Toradex AG
/// @author	     $Author: gap $
/// @version     $Rev: 1138 $ 
/// @date        $Date: 2012-10-31 13:29:08 +0100 (Wed, 31 Oct 2012) $
/// @brief	     Library to interface with the co-processor
/// 
/// @target      PXAxxx, T20   
///

#ifndef _COPROC_LIB_H_
#define _COPROC_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#define CPL_VER_MAJ     2
#define CPL_VER_MIN     0
#define CPL_VER_BUILD   0

/// SoC family Type.
#define PXA 1
#define TEG 2

/// Defines for getPROCID.
#define TYPE_PXA270		0x11
#define TYPE_MONAHANS	0x02
#define TYPE_PXA320		0x02
#define TYPE_PXA300		0x08
#define TYPE_PXA310		0x09
#define TYPE_TEGRA2     0x411FC09

/// Defines for CLKCFG
#define CLKCFG_FAST_BUS_MODE    0x0008  ///< B  - 0: System bus freq. half run-mode freq, 1: System bus freq. equalt to run-mode freq.
#define CLKCFG_HALF_TURBO_MODE  0x0004  ///< HT - 0: Core freq equal to run or turbo clock, 1: core freq turbo clock divided by 2
#define CLKCFG_FREQUENCY_CHANGE 0x0002  ///< F  - 0: A change sequence is initiated, 1: No freq. change performed
#define CLKCFG_TURBO_MODE       0x0001  ///< T  - 0: Run mode, 1: Turbo mode

/// Defines for PWRMODE
#define PWRMODE_VOLTAGE_CHANGE  0x0008  ///< VC - 0: No voltage change, 1: Voltage change initiated
#define PWRMODE_MODE_MASK       0x0007  ///< M  - Mode Mask
#define PWRMODE_MODE_NORMAL     0x0000  ///< M  - Normal Mode
#define PWRMODE_MODE_IDLE       0x0001  ///< M  - Idle Mode
#define PWRMODE_MODE_STANDBY    0x0002  ///< M  - Standby Mode
#define PWRMODE_MODE_SLEEP      0x0003  ///< M  - Sleep Mode
#define PWRMODE_MODE_DEEP_SLEEP 0x0007  ///< M  - Deep Sleep Mode

//******************************************************************************
/// Returns the library Version.
/// @param[out]         pVerMaj         Returns the major version number. Set this parameter to NULL if not required.
/// @param[out]         pVerMin         Returns the minor version number. Set this parameter to NULL if not required.
/// @param[out]         pBuild          Returns the build number.         Set this parameter to NULL if not required.
void CPLGetLibVersion(DWORD *pVerMaj, DWORD *pVerMin, DWORD *pBuild);

//******************************************************************************
/// Gets CLKCFG (Coprocessor 14, cr6) Core Clock Configuration            
/// @retval             0           Error.
/// @retval             >0          Clock configuration value - see defines.
DWORD getCLKCFG(void);

//******************************************************************************
/// Sets CLKCFG (Coprocessor 14, cr6) Core Clock Configuration
/// @param[in]	        val         Clock configuration - see defines          
void setCLKCFG(DWORD val);

//******************************************************************************
/// Gets PWRMODE (Coprocessor 14, cr7) Power Modes.             
/// @retval		        0           Error
/// @retval             >0          Power mode configuration value - see defines.
DWORD getPWRMODE(void);

//******************************************************************************
/// Set PWRMODE (Coprocessor 14, cr7) Power Modes.
/// @param[in]	        val         Power mode configuration value - see defines.
void setPWRMODE(DWORD val);

//******************************************************************************
/// Gets CPUID (Coprocessor 15, cr0) Processor information.             
/// @retval		        CPU ID
DWORD getCPUID(void);

//******************************************************************************
/// Gets Processor ID, use this function to detect on which processor your programm is running.
/// @retval		        Processor ID
DWORD getPROCID(void);

//******************************************************************************
/// Checks if L2 cache is enabled.            
/// @retval		        TRUE: Enabled, FALSE: Disabled
DWORD getL2Enabled(void);

//******************************************************************************
/// Find out the SoC family type.
/// @retval		        PXA             CPU type is PXA.
/// @retval             TEG             CPU type is Tegra.
DWORD GetSoCType(void);

#ifdef __cplusplus
}
#endif

#endif  // _COPROC_LIB_H_
