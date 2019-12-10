/** @example singleinstance_simple.c
 * A very simple example of a single instance integration without real-time audio on Linux. Ethernet tuning interface. 
 * Examples */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "AWECore.h"
#include "ProxyIDs.h"
#include "AWECoreUtils.h"
#include "TargetInfo.h"



AWEInstance g_AWEInstance;

static IOPinDescriptor g_InputPin[1];
static IOPinDescriptor g_OutputPin[1];

const void* g_module_descriptor_table[] =
{
	LISTOFCLASSOBJECTS
};

/* ----------------------------------------------------------------------
** Specify the size in 32-bit words of each of the heaps on this target
** ------------------------------------------------------------------- */
#define MASTER_HEAP_SIZE		(1024*1024)
#define FASTB_HEAP_SIZE			(1024*1024)
#define SLOW_HEAP_SIZE			(1024*1024)

UINT32 g_FastHeapA[MASTER_HEAP_SIZE];
UINT32 g_SlowHeap[MASTER_HEAP_SIZE];
UINT32 g_FastHeapB[MASTER_HEAP_SIZE];

//global packet buffers
UINT32 AWE_Packet_Buffer[264];
UINT32 AWE_Packet_Buffer_Reply[264];

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void *tuningPacketRxThread(void*)
{
	/*
		Tuning packets can be recieved and processed here. Another implementation 
		may choose to process the packet in another thread.
	*/
     int sockfd, newsockfd;
     socklen_t clilen;
     unsigned char buffer[264];
     struct sockaddr_in serv_addr, cli_addr;
	 int n;
	 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{
		error("ERROR opening socket");
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(15098);
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			  sizeof(serv_addr)) < 0) 
			  {
				  error("ERROR on binding");
			  }
			  
	listen(sockfd,5);

	 clilen = sizeof(cli_addr);
	 newsockfd = accept(sockfd, 
				 (struct sockaddr *) &cli_addr, 
				 &clilen);

	 if (newsockfd < 0) 
		  error("ERROR on accept");
	  int i=1;
	  
/* Enter a tuning loop. This will be in a separate thread */
	 printf( "entering loop ...\n");
	 while(1)
	 {
		 bzero(AWE_Packet_Buffer,264);
		 
		n = read(newsockfd,AWE_Packet_Buffer,264*sizeof(AWE_Packet_Buffer[0]));
		if (n < 0) error("ERROR reading from socket");
		 
		volatile INT32 opcode = PACKET_OPCODE(AWE_Packet_Buffer);
		volatile UINT32 packetCoreID = PACKET_INSTANCEID(AWE_Packet_Buffer); //snoop the coreID off of the packet
		
		awe_packetProcess(&g_AWEInstance);		 
		unsigned int plen = AWE_Packet_Buffer[0]>>16;
		n = write(newsockfd,AWE_Packet_Buffer,plen*sizeof(AWE_Packet_Buffer[0]));
		
		if (n < 0) error("ERROR writing to socket");
	 }
	close(newsockfd);
	close(sockfd);
}



void InitializeAWEInstance()
{
	int ret = 0;

	//set memory for awe instance and initialize to 0's
	memset(&g_AWEInstance, 0, sizeof(AWEInstance));

	g_AWEInstance.instanceId = 0;
	
	g_AWEInstance.pInputPin = g_InputPin;
	g_AWEInstance.pOutputPin = g_OutputPin;

	g_AWEInstance.pPacketBuffer = AWE_Packet_Buffer;
	g_AWEInstance.pReplyBuffer = AWE_Packet_Buffer;
	
	g_AWEInstance.packetBufferSize = 264;
	
	g_AWEInstance.pModuleDescriptorTable = g_module_descriptor_table;

	UINT32 module_descriptor_table_size = sizeof(g_module_descriptor_table) / sizeof(g_module_descriptor_table[0]); 
	g_AWEInstance.numModules = module_descriptor_table_size;

	g_AWEInstance.numThreads = 1;
	g_AWEInstance.sampleRate = 48000.f;
	g_AWEInstance.fundamentalBlockSize = 32;
	g_AWEInstance.pFlashFileSystem = 0;

	g_AWEInstance.fastHeapASize = MASTER_HEAP_SIZE;
	g_AWEInstance.slowHeapSize = SLOW_HEAP_SIZE;
	g_AWEInstance.fastHeapBSize = FASTB_HEAP_SIZE;

	g_AWEInstance.pFastHeapA = g_FastHeapA;
	g_AWEInstance.pSlowHeap = g_SlowHeap;
	g_AWEInstance.pFastHeapB = g_FastHeapB;
	
	g_AWEInstance.coreSpeed = 10e6f;
	g_AWEInstance.profileSpeed = 10e6f;
	g_AWEInstance.pName = TARGET_NAME;
	

	ret = awe_initPin(g_InputPin, INPUT_CHANNEL_COUNT, NULL);
	if (ret != 0)
	{
		printf("awe_initPin inputPin failed\n");
	}
	ret = awe_initPin(g_OutputPin, OUTPUT_CHANNEL_COUNT, NULL);
	if (ret != 0)
	{
		printf("awe_initPin outputPin failed\n");
	}

	ret = awe_init(&g_AWEInstance);
	if (ret != 0) 
	{
		printf("awe_init instance 1 failed\n");
	}
}

int main( int argc, const char* argv[] )
{
	pthread_t rxthread_id;
	pthread_t processthread_id;
	InitializeAWEInstance();
	pthread_create(&rxthread_id, NULL, tuningPacketRxThread, NULL); 
	pthread_join(rxthread_id, NULL);
	
	while(1) 
	{
		//printf("main idle loop")
	}	
}