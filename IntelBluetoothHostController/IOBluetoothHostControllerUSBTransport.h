//
//  IOBluetoothHostControllerUSBTransport.h
//  IntelBluetoothHostController
//
//  Created by zxystd on 2021/2/23.
//

#ifndef IOBluetoothHostControllerUSBTransport_h
#define IOBluetoothHostControllerUSBTransport_h

#include <IOKit/usb/IOUSBHostInterface.h>
#include <IOKit/usb/IOUSBHostDevice.h>

#include "IOBluetoothHostControllerTransport.h"

class IOUSBHostIsochronousFrame;
class IOBluetoothMemoryDescriptorRetainer;
class IOBluetoothSCOMemoryDescriptorRetainer;

class IOBluetoothHostControllerUSBTransport : public IOBluetoothHostControllerTransport {
    OSDeclareAbstractStructors(IOBluetoothHostControllerUSBTransport)
    
public:
    virtual void free() override;
    virtual bool init( OSDictionary * dictionary = NULL ) override;
    virtual  IOService * probe( IOService *     provider, SInt32    *     score ) override;
    virtual bool start( IOService * provider ) override;
    virtual void stop( IOService * provider ) override;
    virtual unsigned long maxCapabilityForDomainState( IOPMPowerFlags domainState ) override;
    virtual unsigned long initialPowerStateForDomainState( IOPMPowerFlags domainState ) override;
    virtual IOReturn powerStateWillChangeTo(
        IOPMPowerFlags  capabilities,
        unsigned long   stateNumber,
        IOService *     whatDevice ) override;
    virtual void terminateWL(unsigned int) override;
    virtual bool InitializeTransportWL(IOService *) override;
    virtual IOReturn SetRemoteWakeUp(bool) override;
    virtual IOReturn DoDeviceReset(unsigned short) override;
    virtual void AbortPipesAndClose(bool,bool) override;
    virtual bool HostSupportsSleepOnUSB(void) override;
    virtual bool StartLMPLogging(void) override;
    virtual bool StartLMPLoggingBulkPipeRead(void) override;
    virtual bool StartInterruptPipeRead(void) override;
    virtual bool StopInterruptPipeRead(void) override;
    virtual bool StartBulkPipeRead(void) override;
    virtual bool StopBulkPipeRead(void) override;
    virtual bool TransportBulkOutWrite(void *) override;
    virtual bool TransportIsochOutWrite(void *,void *,int) override;
    virtual bool TransportLMPLoggingBulkOutWrite(unsigned char,unsigned char) override;
    virtual IOReturn SendHCIRequest(unsigned char *,unsigned long long) override;
    virtual bool UpdateSCOConnections(unsigned char,unsigned int) override;
    virtual IOReturn ToggleLMPLogging(unsigned char *) override;
    virtual bool ConfigurePM(IOService *) override;
    virtual IOReturn setPowerStateWL(unsigned long,IOService *) override;
    virtual bool RequestTransportPowerStateChange(IOBluetoothHCIControllerInternalPowerState,char *) override;
    virtual void CompletePowerStateChange(char *) override;
    virtual void ProcessPowerStateChangeAfterResumed(char *) override;
    virtual IOReturn powerStateWillChangeToWL(unsigned int,void *) override;
    virtual IOReturn systemWillShutdownWL(unsigned int,void *) override;
    virtual bool ControllerSupportWoBT(void) override;
    virtual UInt32 GetControllerVendorID(void) override;
    virtual UInt32 GetControllerProductID(void) override;
    virtual unsigned char GetRadioPowerState(void) override;
    virtual void SetRadioPowerState(unsigned char) override;
    virtual void ResetBluetoothDevice(void) override;
    virtual UInt64 GetInfo(void *) override;
    virtual void SetIdlePolicyValue(unsigned int) override;
    virtual bool TransportWillReEnumerate(void) override;
    virtual IOReturn SetupTransportSCOParameters(void) override;
    virtual void DestroyTransportSCOParameters(void) override;
    virtual IOReturn HardReset(void) override;
    
    virtual IOReturn HandleMessage(unsigned int,IOService *,void *,unsigned long);
    virtual bool ConfigureDevice(void);
    virtual int8_t GetInterfaceNumber(IOUSBHostInterface *);
    virtual IOUSBHostInterface *FindNextInterface(IOUSBHostInterface *,unsigned short,unsigned short,unsigned short,unsigned short);
    virtual IOUSBHostPipe *FindNextPipe(IOUSBHostInterface *,unsigned char,unsigned char,unsigned short *);
    virtual bool FindInterfaces(void);
    virtual bool StartIsochPipeRead(void);
    virtual bool StopIsochPipeRead(void);
    virtual void ResetIsocFrames(IOUSBHostIsochronousFrame *,unsigned int);
    virtual IOReturn StopAllPipes(void);
    virtual IOReturn StartAllPipes(void);
    virtual void WaitForAllIOsToBeAborted(void);
    virtual bool ReceiveInterruptData(void *,unsigned int,bool);
    virtual IOReturn BulkOutWrite(IOMemoryDescriptor *);
    virtual void HandleBulkOutWriteTimeout(IOBluetoothMemoryDescriptorRetainer *);
    virtual IOReturn HandleIsochData(void *,int,IOUSBHostIsochronousFrame *);
    virtual IOReturn IsochOutWrite(IOMemoryDescriptor *,IOBluetoothSCOMemoryDescriptorRetainer *,int);
    virtual void LogData(void *,unsigned long long,unsigned long long);
    virtual bool USBControllerSupportsSuspend(void);
    virtual bool SystemGoingToSleep(void);
    virtual bool PrepareControllerForSleep(void);
    virtual bool PrepareControllerWakeFromSleep(void);
    virtual bool PrepareControllerForPowerOff(bool);
    virtual bool PrepareControllerForPowerOn(void);
    virtual bool SystemWakeCausedByBluetooth(void);
    virtual IOReturn ProcessG3StandByWake(void);
    virtual IOReturn ReConfigure(void);
    virtual bool NeedToTurnOnUSBDebug(void);
    
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport,  0);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport,  1);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport,  2);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport,  3);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport,  4);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport,  5);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport,  6);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport,  7);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport,  8);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport,  9);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 10);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 11);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 12);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 13);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 14);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 15);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 16);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 17);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 18);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 19);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 20);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 21);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 22);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerUSBTransport, 23);
    
public:
    char data_IOBluetoothHostControllerUSBTransport[0x800];
};


#endif /* IOBluetoothHostControllerUSBTransport_h */
