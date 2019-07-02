//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision v1.2.12 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include "am_app_KWD_codec.h"

#if VOS_configUSE_AUDIO_CODEC
//*****************************************************************************
//
// Audio codec init
//
//*****************************************************************************

//uint32_t g_ui32CodecDebugValue = 0;

void am_app_KWD_codec_init(void)
{
    #if VOS_configUSE_SBC_BLUEZ
        sbc_encode_init(&g_BluezSBCInstance, 0);  //0: SBC
    #endif

    #if VOS_configUSE_MSBC_BLUEZ
        sbc_encode_init(&g_BluezSBCInstance, 1);  //1: MSBC
    #endif

    #if VOS_configUSE_OPTIM_OPUS
    /* initialize the audio encoder */
    audio_enc_init(0);
    #endif

}
//*****************************************************************************
//
// Audio codec encoder
//
//*****************************************************************************

void am_app_KWD_codec_encode(void *codecInstance, const void *p_InputBuf, size_t input_len,
			                void *p_OutputBuf, size_t output_len, ssize_t *p_CompressedLen)
{
    uint32_t ui32EncoderReturn;

    #if (VOS_configUSE_SBC_BLUEZ || VOS_configUSE_MSBC_BLUEZ)
        ui32EncoderReturn = sbc_encoder_encode((sbc_t*)codecInstance, p_InputBuf, input_len, 
                                                p_OutputBuf, output_len, (int32_t *)p_CompressedLen);
        configASSERT(ui32EncoderReturn == CODEC_IN_RING_BUFF_SIZE);
    #endif

    #if VOS_configUSE_OPTIM_OPUS
        ui32EncoderReturn = audio_enc_encode_frame((int16_t*)p_InputBuf, OPUS_IN_FRAME_SIZE, (unsigned char*)p_OutputBuf);
        *p_CompressedLen = (int32_t)ui32EncoderReturn;
//        g_ui32CodecDebugValue += *p_CompressedLen;
//        configASSERT(ui32EncoderReturn == CODEC_OUT_RING_BUFF_SIZE);
    #endif

}

#endif

