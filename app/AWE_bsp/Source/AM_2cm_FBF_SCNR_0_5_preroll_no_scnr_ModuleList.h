/*******************************************************************************
*
********************************************************************************
*     ModuleList.h  Created on 04-Apr-2019 11:34:01
********************************************************************************
*
*     Description:  Module list for the target
*
*     Copyright: (c) 2018 DSP Concepts, Inc. All rights reserved.
*                         3235 Kifer Road
*                         Santa Clara, CA 95054-1527
*
*******************************************************************************/
#include "Framework.h"

#define TOTALNUMBEROFCLASSES 16

extern const ModClassModule awe_modAdderClass;
extern const ModClassModule awe_modBiquadCascadeClass;
extern const ModClassModule awe_modButterworthFilterClass;
extern const ModClassModule awe_modComplexMultiplierClass;
extern const ModClassModule awe_modFftClass;
extern const ModClassModule awe_modIfftClass;
extern const ModClassModule awe_modMultiplexorV2Class;
extern const ModClassModule awe_modRepWinOverlapClass;
extern const ModClassModule awe_modRouterClass;
extern const ModClassModule awe_modSCNRv1Class;
extern const ModClassModule awe_modSetWirePropertiesClass;
extern const ModClassModule awe_modSinkFract32Class;
extern const ModClassModule awe_modSourceClass;
extern const ModClassModule awe_modTimeOutClass;
extern const ModClassModule awe_modTypeConversionClass;
extern const ModClassModule awe_modWindowAliasClass;


#define LISTOFCLASSOBJECTS \
&awe_modAdderClass, \
&awe_modBiquadCascadeClass, \
&awe_modButterworthFilterClass, \
&awe_modComplexMultiplierClass, \
&awe_modFftClass, \
&awe_modIfftClass, \
&awe_modMultiplexorV2Class, \
&awe_modRepWinOverlapClass, \
&awe_modRouterClass, \
&awe_modSCNRv1Class, \
&awe_modSetWirePropertiesClass, \
&awe_modSinkFract32Class, \
&awe_modSourceClass, \
&awe_modTimeOutClass, \
&awe_modTypeConversionClass, \
&awe_modWindowAliasClass
