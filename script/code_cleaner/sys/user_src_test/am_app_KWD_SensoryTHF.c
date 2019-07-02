#include "usr_include.h"

#include "SensoryLib.h"
#include "am_app_KWD_SensoryTHF.h"

#define  TESTDATA           HBG01_RAW           // array of shorts with test data
#define  TESTDATA_SAMPLES   HBG01_RAW_SAMPLES   // number of shorts in test data array

#define  CURRENT_GRAMMAR    dgs_grammarLabel  // in included/externed grammar file
#define  CURRENT_NET        dnn_netLabel // in included/externed net file

#define  CURRENT_SDET       SDET_NONE // SDET_NONE or SDET_LPSD 

#define  SV_THRESHOLD       4096  // 0.5,  for SV/SID grammars only

//***********************************************************************
// Global Sensory Instance
//***********************************************************************
appStruct_T appStruct;  
#if AUDIO_BUFFER_LEN > 0         
SAMPLE audioBuffer[AUDIO_BUFFER_LEN];
#endif    // AUDIO_BUFFER_LEN>0

#ifdef SENSORY_LOGGING
#define SENSORY_LOG_ITEMS 200
SENSORY_LOG_OBJ sensoryLog[SENSORY_LOG_ITEMS];
#endif    // defSENSORY_LOGGING

// configure t2siStruct with recognition parameters
// allocate memory for Sensory Persistent structure
// initialize audio buffer parameters
// initialized LPSD
// initialize recognizer via call to SensoryProcessInit

errors_t SensoryInitialize() 
{
    unsigned int size=0; // size of spp
    errors_t result;

    appStruct_T *ap = &appStruct;
    t2siStruct *t = &ap->_t;


    // Set up recognition control parameters in the t2siStruct.
    // NOTE: t->net, gram, maxResults and maxTokens affect the amount of memory needed
    // (which will be calculated by the call to SensoryAlloc).

    // Here we zero out appStruct including embedded t2siStruct.  
    // Warning: if you do this after the persistent structure is malloc'd you will 
    // overwrite the pointer without freeing the structure.

    memset(ap, 0, sizeof(*ap));

    t->net  = (u32)&CURRENT_NET;
    t->gram = (u32)&CURRENT_GRAMMAR;

    t->maxResults = MAX_RESULTS;
    t->maxTokens  = MAX_TOKENS;

    t->sdet_type = CURRENT_SDET; // SDET_NONE or SDET_LPSD 
    t->knob = T2SI_DEFAULT_KNOB;
    t->paramAOffset = 0;
    t->enableLogging = 0;   // default is enabling logging
   
    // find out how much persistent memory we need based on the grammar, maxResults, and maxTokens.
    // this could be allocated statically if you know the largest size needed for your set of grammars.
    
    SensoryAlloc (&appStruct, &size);
    //printf("spp size= %d\n", size);

    // allocate the persistent structure memory 
    t->spp = (void *)pvPortMalloc(size);
    if (!t->spp) return ERR_HEAP_FULL;

#ifdef SENSORY_LOGGING
	if (t->enableLogging) {
		SensoryLogInit(ap, sensoryLog, SENSORY_LOG_ITEMS);
		SensoryLog(t, SENSORY_LOG_RESET,0,0);
    }    
#endif    // defSENSORY_LOGGING
    

#if AUDIO_BUFFER_LEN > 0
    // initialize audio buffer items. Do this before calling SensoryLPSDInit.
    ap->audioBufferLen = AUDIO_BUFFER_LEN;
    // if not using malloc for the audio buffer, just point audioBufferStart to the statically
    // allocated audio buffer.

 
    ap->audioBufferStart = audioBuffer;
    ap->audioPutIndex = ap->audioGetIndex = ap->lpsdGetIndex = 0;
    ap->audioGetFrameCounter = 0;
    ap->audioFilledCount = 0;

    // Initialize Sound Detector (OK to do this even for SDET_NONE)
    // Do this after setting up the audio buffer items in appStruct.  You will want to
    // call SensoryProcessInit after this, before the next call to SensoryProcessData
    SensoryLPSDInit(ap); 
#endif    // AUDIO_BUFFER_LEN>0
    result = SensoryProcessInit(ap);
    return result;
}


// free the Sensory persistent structure 

errors_t SensoryTerminate() 
{
    appStruct_T *ap = &appStruct;
    t2siStruct *t = &ap->_t;

    if (t->spp) {
        free(t->spp);
        t->spp = NULL;
    }
    return 0;
}