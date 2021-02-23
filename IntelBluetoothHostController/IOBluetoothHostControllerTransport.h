//
//  IOBluetoothHostControllerTransport.h
//  IntelBluetoothHostController
//
//  Created by zxystd on 2021/2/23.
//

#ifndef IOBluetoothHostControllerTransport_h
#define IOBluetoothHostControllerTransport_h

#include <IOKit/IOWorkLoop.h>
#include <libkern/OSKextLib.h>
#include <libkern/c++/OSMetaClass.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>

#include <Availability.h>

enum IOBluetoothHCIControllerInternalPowerState {
    POWER_BT_OFF,
    POWER_BT_ON,
    POWER_BT_SLEEP,
    POWER_BT_IDLE,
};

class IOBluetoothHostControllerTransport : public IOService {
    OSDeclareAbstractStructors(IOBluetoothHostControllerTransport)
    
public:
    virtual void retain() const override;
    virtual void release() const override;
    virtual void free() override;
    virtual bool init( OSDictionary * dictionary = NULL ) override;
    virtual IOReturn setProperties(OSObject *) override;
    virtual void systemWillShutdown( IOOptionBits specifier ) override;
    virtual IOService * probe(  IOService *     provider,
        SInt32    *     score ) override;
    virtual bool start( IOService * provider ) override;
    virtual void stop( IOService * provider ) override;
    virtual bool terminate( IOOptionBits options = 0 ) override;
    virtual IOWorkLoop * getWorkLoop() const override;
    virtual IOReturn setAggressiveness(
        unsigned long type,
        unsigned long newLevel ) override;
    virtual IOReturn setPowerState(
        unsigned long powerStateOrdinal,
        IOService *   whatDevice ) override;
    virtual unsigned long maxCapabilityForDomainState( IOPMPowerFlags domainState ) override;
    virtual unsigned long initialPowerStateForDomainState( IOPMPowerFlags domainState ) override;
    virtual IOReturn powerStateWillChangeTo(
        IOPMPowerFlags  capabilities,
        unsigned long   stateNumber,
        IOService *     whatDevice ) override;
    virtual IOCommandGate *getCommandGate(void);
    virtual void setTransportWorkLoop(void *,IOWorkLoop *);
    virtual void terminateWL(unsigned int);
    virtual bool InitializeTransport(void);
    virtual bool InitializeTransportWL(IOService *);
    virtual UInt64 getPropertyFromTransport(OSSymbol const*);
    virtual UInt64 getPropertyFromTransport(OSString const*);
    virtual UInt64 getPropertyFromTransport(char const*);
    virtual IOReturn SetRemoteWakeUp(bool);
    virtual IOReturn DoDeviceReset(unsigned short);
    virtual void AbortPipesAndClose(bool,bool);
    virtual bool HostSupportsSleepOnUSB(void);
    virtual bool StartLMPLogging(void);
    virtual bool StartLMPLoggingBulkPipeRead(void);
    virtual bool StartInterruptPipeRead(void);
    virtual bool StopInterruptPipeRead(void);
    virtual bool StartBulkPipeRead(void);
    virtual bool StopBulkPipeRead(void);
    virtual bool TransportBulkOutWrite(void *);
    virtual bool TransportIsochOutWrite(void *,void *,int);
    virtual bool TransportSendSCOData(void *);
    virtual bool TransportLMPLoggingBulkOutWrite(unsigned char,unsigned char);
    virtual IOReturn SendHCIRequest(unsigned char *,unsigned long long);
    virtual bool UpdateSCOConnections(unsigned char,unsigned int);
    virtual IOReturn ToggleLMPLogging(unsigned char *);
    virtual IOReturn CallConfigPM(void);
    virtual bool ConfigurePM(IOService *);
    virtual IOReturn setPowerStateWL(unsigned long,IOService *);
    virtual bool RequestTransportPowerStateChange(IOBluetoothHCIControllerInternalPowerState,char *);
    virtual IOReturn WaitForControllerPowerState(IOBluetoothHCIControllerInternalPowerState,char *);
    virtual IOReturn WaitForControllerPowerStateWithTimeout(IOBluetoothHCIControllerInternalPowerState,unsigned int,char *,bool);
    virtual void CompletePowerStateChange(char *);
    virtual void ProcessPowerStateChangeAfterResumed(char *);
    virtual bool setAggressivenessWL(unsigned long,unsigned long);
    virtual IOReturn powerStateWillChangeToWL(unsigned int,void *);
    virtual IOReturn systemWillShutdownWL(unsigned int,void *);
    virtual UInt64 GetCurrentPowerState(void);
    virtual UInt64 GetPendingPowerState(void);
    virtual IOReturn ChangeTransportPowerStateFromIdleToOn(char *);
    virtual IOReturn ChangeTransportPowerState(unsigned long,bool,IOBluetoothHCIControllerInternalPowerState,char *);
    virtual IOReturn WaitForControllerPowerStateChange(IOBluetoothHCIControllerInternalPowerState,char *);
    virtual IOReturn WakeupSleepingPowerStateThread(void);
    virtual bool ControllerSupportWoBT(void);
    virtual UInt32 GetControllerVendorID(void);
    virtual UInt32 GetControllerProductID(void);
    virtual unsigned char GetRadioPowerState(void);
    virtual void SetRadioPowerState(unsigned char);
    virtual bool GetNVRAMSettingForSwitchBehavior(void);
    virtual UInt64 GetControllerLocationID(void);
    virtual bool GetBuiltIn(void);
    virtual bool GetSupportPowerOff(void);
    virtual bool IsHardwareInitialized(void);
    virtual UInt32 GetHardwareStatus(void);
    virtual void ResetHardwareStatus(void);
    virtual UInt32 ConvertAddressToUInt32(void *);
    virtual void SetActiveController(bool);
    virtual void ResetBluetoothDevice(void);
    virtual IOReturn TransportCommandSleep(void *,unsigned int,char *,bool);
    virtual IOReturn ReadyToGo(bool);
    virtual bool TerminateCalled(void);
    virtual UInt64 GetInfo(void *);
    virtual IOReturn CallPowerManagerChangePowerStateTo(unsigned long,char *);
    virtual UInt32 GetControllerTransportType(void);
    virtual bool SupportNewIdlePolicy(void);
    virtual IOReturn CheckACPIMethodsAvailabilities(void);
    virtual IOReturn SetBTRS(void);
    virtual IOReturn SetBTPU(void);
    virtual IOReturn SetBTPD(void);
    virtual IOReturn SetBTRB(bool);
    virtual IOReturn SetBTLP(bool);
    virtual void NewSCOConnection(void);
    virtual UInt64 RetainTransport(char *);
    virtual UInt64 ReleaseTransport(char *);
    virtual void SetIdlePolicyValue(unsigned int);
    virtual bool TransportWillReEnumerate(void);
    virtual void ConvertPowerFlagsToString(unsigned long,char *);
    virtual IOReturn SetupTransportSCOParameters(void);
    virtual void DestroyTransportSCOParameters(void);
    virtual IOReturn WaitForSystemReadyForSleep(char *);
    virtual IOReturn StartBluetoothSleepTimer(void);
    virtual void CancelBluetoothSleepTimer(void);
    virtual void *CreateOSLogObject(void);
    virtual IOReturn setPropertiesWL(OSObject *);
    virtual IOReturn HardReset(void);
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_11_0
    virtual void DumpTransportProviderState(void);
#endif
    
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport,  0);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport,  1);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport,  2);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport,  3);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport,  4);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport,  5);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport,  6);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport,  7);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport,  8);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport,  9);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 10);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 11);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 12);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 13);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 14);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 15);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 16);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 17);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 18);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 19);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 20);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 21);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 22);
    OSMetaClassDeclareReservedUnused( IOBluetoothHostControllerTransport, 23);
    
public:
    char data_IOBluetoothHostControllerTransport[0x700];
};


#endif /* IOBluetoothHostControllerTransport_h */
