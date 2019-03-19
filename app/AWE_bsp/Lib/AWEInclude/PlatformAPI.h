/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     PlatformAPI.h
********************************************************************************
*
*     Description:  Prototypes of AudioWeaver high-level interface functions
*
*     Copyright:    DSP Concepts, Inc., 2007 - 2016
*                   1800 Wyatt Drive, Suite 14
*                   Sunnyvale, CA 95054
*
*******************************************************************************/

#include "Framework.h"

/* Protect the file from multiple inclusion. */
#ifndef PLATFORMAPI_H_INCLUDED
#define PLATFORMAPI_H_INCLUDED

/* Enter C naming convention */
#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/* ----------------------------------------------------------------------------
 *   Global variables
 * ------------------------------------------------------------------------- */
//#ifdef __ADSP215xx__
	//#pragma word_addressed
//#endif

#if defined(__ADSP21000__)
//	#ifdef __ADSP215xx__
	//	#pragma byte_addressed(push)
//	#endif
    extern volatile INT32 g_target_baudrate;
    extern volatile BOOL g_bBaudRateChanged;
    extern volatile BOOL g_bPacketSendComplete;
//#ifdef __ADSP215xx__
//	#pragma byte_addressed(pop)
//#endif

#endif
    
#if defined(__ADSP21000__) || defined(DSPC_CORTEX_M)
//	#ifdef __ADSP215xx__
//		#pragma word_addressed
//	#endif
    extern volatile BOOL g_bReboot;
#endif


/* ----------------------------------------------------------------------------
 *   Function Prototypes
 * ------------------------------------------------------------------------- */

/**
 * @brief Start the audio driver.
 */
extern INT32 awe_pltAudioStart(void);

/**
 * @brief Stop the audio driver.
 */
extern INT32 awe_pltAudioStop(void);

/**
 * @brief Initialize the system.
 */
void awe_pltInit(void);

/**
 * @brief Process any background system tasks.
 */
void awe_pltTick(void);

/**
 * @brief Get target number of cores.
 */
int awe_pltGetCores(void);

/**
 * @brief Destroy all the cores
 */
void awe_pltDestroyAll(void);

#define GPIO_DIR_INPUT 0
#define GPIO_DIR_OUTPUT 1
void awe_pltGPIOSetPinDir(UINT32 nPinNo, UINT32 nPinDir);
void awe_pltGPIOSetPin(UINT32 nPinNo, UINT32 nValue);
void awe_pltGPIOGetPin(UINT32 nPinNo, UINT32 * nValue);

/**
 * @brief Initialize the Framework.
 */
void awe_fwInit(AWEInstance * pAWE);

/**
 * @brief Process any framework operations from a non-real-time thread
 * @param [in] pAWE					AWE instance pointer (this)
 * @return							0 or error code
 *
 * It is called from the main loop when packets arrive.
 */
INT32 awe_fwPacketProcess(AWEInstance * pAWE);

/**
 * @brief Initialize communication handling.
 * @param [in] packet_buf			buffer to use
 * @param [in] buf_length			its length
 */
void awe_fwPacketInit(UINT32 *packet_buf, INT32 buf_length);

/**
 * @brief Returns information about the packet buffer.
 */
void awe_fwGetPacketInfo(UINT32 **packet_buf, INT32 * buf_length);

/**
 * @brief Executes Audio Weaver binary commands using File I/O
 */
INT32 awe_fwPacketExecuteFile(const char * FILENAME);

/**
 * @brief Executes Audio Weaver binary commands from an in memory array.
 */
INT32 awe_fwPacketExecuteArray(AWEInstance * pAWE, UINT32 * array, UINT32 arraySize);

/** Register enumeration. */
typedef enum
{
    /** Target info - system name (first 4 chars) */
    AWE_REG_SYS_NAME0,

    /** Target info - system name (last 4 chars) */
    AWE_REG_SYS_NAME1,

    /** Target info - hardware revision a.b.c.d */
    AWE_REG_SYS_HWREV,

    /** Target info - serial number */
    AWE_REG_SYS_SERIALNUM,

    /** Target info - customer name (first 4 chars) */
    AWE_REG_SYS_CUSTNAME0,

    /** Target info - customer name (last 4 chars) */
    AWE_REG_SYS_CUSTNAME1,

    /** Target info - software revision a.b.c.d */
    AWE_REG_SYS_SWREV,

    /** Target info - profiling speed */
    AWE_REG_SYS_PROFILESPEED,

    /** Target info - misc packed info */
    AWE_REG_SYS_MISCINFO,

    /** Target info - command buffer length */
    AWE_REG_SYS_COMMANDBUFLEN,

    /** Audio processing - current system status */
    AWE_REG_SYS_STATUS,

    /** Audio processing - number of audio I/O modes */
    AWE_REG_SYS_NUMAUDMODES,

    /** Audio processing - current audio I/O mode */
    AWE_REG_SYS_AUDMODE,

    /** Audio processing - number of inputs and outputs and block size in current I/O mode */
    AWE_REG_SYS_AUDIOIOINFO,

    /** Audio processing - invoke preset */
    AWE_REG_SYS_INVOKEPRESET,

    /** Audio processing - software mute */
    AWE_REG_SYS_SWMUTE,

    /** A/D - sample rate for the current I/O mode, in Hz */
    AWE_REG_ADC_SAMPLERATE,

    /** A/D - range of the programmable gain attenuator (PGA) */
    AWE_REG_ADC_PGARANGE,

    /** A/D - current PGA setting */
    AWE_REG_ADC_PGAVALUE,

    /** A/D - Boolean HW mute setting */
    AWE_REG_ADC_MUTE,

    /** D/A - sample rate for the current I/O mode, in Hz */
    AWE_REG_DAC_SAMPLERATE,

    /** D/A - range of the PGA */
    AWE_REG_DAC_PGARANGE,

    /** D/A - current PGA setting */
    AWE_REG_DAC_PGAVALUE,

    /** D/A - Boolean HW mute setting */
    AWE_REG_DAC_MUTE,

    /** S/PDIF - Boolean is signal locked */
    AWE_REG_SPDIFIN_ISLOCKED,

    /** S/PDIF - current input sample rate */
    AWE_REG_SPDIFIN_SAMPLERATE,

    /** S/PDIF - current output sample rate */
    AWE_REG_SPDIFOUT_SAMPLERATE,

    /** GPIO - number of GPIO pins */
    AWE_REG_GPIO_NUM,

    /** GPIO - bit field indicating which pins are readable.  Applies to lines 0 to 31. */
    AWE_REG_GPIO_ISREADABLE0,

    /** GPIO - bit field indicating which pins are writeable.  Applies to lines 0 to 31. */
    AWE_REG_GPIO_ISWRITEABLE0,

    /** GPIO - bit field indicating the direction of each pin.  Applies to lines 0 to 31. */
    AWE_REG_GPIO_DIR0,

    /** GPIO - current value of readable pins.  Applies to lines 0 to 31. */
    AWE_REG_GPIO_VALUE0,

    /** GPIO - bit field indicating which pins are readable.  Applies to lines 32 to 63. */
    AWE_REG_GPIO_ISREADABLE1,

    /** GPIO - bit field indicating which pins are writeable.  Applies to lines 32 to 63. */
    AWE_REG_GPIO_ISWRITEABLE1,

    /** GPIO - bit field indicating the direction of each pin.  Applies to lines 32 to 63. */
    AWE_REG_GPIO_DIR1,

    /** GPIO - current value of readable pins.  Applies to lines 32 to 63. */
    AWE_REG_GPIO_VALUE1

} awe_pltRegisterName;

/**
 * @brief Reads a specified register on the target.
 * @param[in] regNum specifies the register number.
 * @param[in] mask bit mask allowing only certain bits to be read.  Set to 0xFFFFFFFF to read everything.
 * @param[in] *readVal register value returned here.
 * @return The function returns E_SUCCESS if the operation completed successfully.  Error conditions are
 * E_REGISTER_INVALID and E_REGISTER_BUSY.
 */
INT32 awe_pltReadRegister(UINT32 regNum, UINT32 mask, UINT32 *readVal);

/**
 * @brief Writes a specified register on the target.
 * @param[in] regNum specifies the register number.
 * @param[in] mask bit mask allowing only certain bits to be written.  Set to 0xFFFFFFFF to write everything.
 * @param[in] writeVal value to write.
 * @return The function returns E_SUCCESS if the operation completed successfully.  Error conditions are
 * E_REGISTER_INVALID and E_REGISTER_BUSY.
 */
INT32 awe_pltWriteRegister(UINT32 regNum, UINT32 mask, UINT32 writeVal);

/**
 * @brief Gets a pointer to a function used for reading register values.  This is used to accelerate register
 * reads by eliminating some of the intervening register/command decoding operations.
 * @param[in] regNum specifies the register number.
 * @param[in] mask bit mask
 * @return The function returns a pointer to the function used to accelerate the register access operation.
 *         If there is no special function defined, then a pointer to awe_pltReadRegister is returned;
 */
INT32 (*awe_pltGetReadRegisterFunc(UINT32 regNum, UINT32 mask))(UINT32 regNum, UINT32 mask, UINT32 *readVal);

/**
 * @brief Gets a pointer to a function used for writing register values.  This is used to accelerate register
 * writes by eliminating some of the intervening register/command decoding operations.
 * @param[in] regNum specifies the register number.
 * @param[in] mask bit mask
 * @return The function returns a pointer to the function used to accelerate the register access operation.
 *         If there is no special function defined, then a pointer to awe_pltWriteRegister is returned;
 */
INT32 (*awe_pltGetWriteRegisterFunc(UINT32 regNum, UINT32 mask))(UINT32 regNum, UINT32 mask, UINT32 readVal);

/**
 * @brief Initialization function for the register subsystem.  Call this once when the platform initializes.
 * @return The function always returns E_SUCCESS.
 */
INT32 awe_pltInitRegisters(void);


/* Leave C naming convention */
#ifdef __cplusplus
}
#endif /*__cplusplus*/


#endif /* !PLATFORMAPI_H_INCLUDED */
