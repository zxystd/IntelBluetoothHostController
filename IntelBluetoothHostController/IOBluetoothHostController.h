//
//  IOBluetoothHostController.h
//  IntelBluetoothHostController
//
//  Created by zxystd on 2021/2/23.
//

#ifndef IOBluetoothHostController_h
#define IOBluetoothHostController_h

#include <IOKit/IOWorkLoop.h>
#include <libkern/OSKextLib.h>
#include <libkern/c++/OSMetaClass.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>

class IOBluetoothHostControllerTransport;
class IOBluetoothHCIController;
class IOBluetoothDevice;
class BluetoothDeviceReporter;
class IOBluetoothHCIRequest;
class BluetoothHCIEventConnectionCompleteResults;
class BluetoothHCIEventLEConnectionCompleteResults;
class BluetoothHCIEventDisconnectionCompleteResults;
class BluetoothHCIEventFlushOccurredResults;
class IOBluetoothACLMemoryDescriptor;
class IOBluetoothSCOMemoryDescriptorRetainer;

enum IOBluetoothHCIControllerConfigState {
    
};

enum IOBluetoothHCIControllerInternalPowerState {
    
};
struct BluetoothDeviceAddress;

class IOBluetoothHostController : public IOService {
    OSDeclareAbstractStructors(IOBluetoothHostController)
    
public:
    virtual bool setProperty(const OSSymbol * aKey,
        OSObject * anObject) override;
    virtual bool setProperty(const OSString * aKey, OSObject * anObject) override;
    virtual bool setProperty(const char * aKey, OSObject * anObject) override;
    virtual bool setProperty(const char * aKey, const char * aString) override;
    virtual bool setProperty(const char * aKey, bool aBoolean) override;
    virtual bool setProperty( const char *       aKey,
        unsigned long long aValue,
        unsigned int       aNumberOfBits) override;
    virtual bool setProperty( const char *       aKey,
        void *             bytes,
        unsigned int       length) override;
    virtual IOReturn setProperties(OSObject *) override;
    virtual IOReturn configureReport(IOReportChannelList   *channels,
        IOReportConfigureAction action,
        void                  *result,
        void                  *destination) override;
    virtual IOReturn updateReport(IOReportChannelList      *channels,
        IOReportUpdateAction      action,
        void                     *result,
        void                     *destination) override;
    virtual bool start( IOService * provider ) override;
    virtual void stop( IOService * provider ) override;
    virtual bool terminate( IOOptionBits options = 0 ) override;
    virtual IOWorkLoop * getWorkLoop() const override;
    virtual IOReturn newUserClient( task_t owningTask, void * securityID,
        UInt32 type,
        LIBKERN_RETURNS_RETAINED IOUserClient ** handler ) override;
    
    virtual IOReturn AddUserClient(void *);
    virtual void DetachUserClients(void);
    virtual bool InitializeVariables(IOBluetoothHostControllerTransport *);
    virtual bool init(IOBluetoothHCIController *,IOBluetoothHostControllerTransport *);
    virtual bool SetVariables(void);
    virtual void Enable(IOBluetoothHostControllerTransport *);
    virtual void Disable(void);
    virtual void StopAndFreeVariables(void);
    virtual void stopWL(IOService *);
    virtual void terminateWL(unsigned int);
    virtual bool setPropertiesWL(OSObject *);
    virtual bool SetBluetoothControllerProperty(OSSymbol const*,OSObject *);
    virtual bool SetBluetoothControllerProperty(OSString const*,OSObject *);
    virtual bool SetBluetoothControllerProperty(char const*,OSObject *);
    virtual bool SetBluetoothControllerProperty(char const*,char const*);
    virtual bool SetBluetoothControllerProperty(char const*,bool);
    virtual bool SetBluetoothControllerProperty(char const*,unsigned long long,unsigned int);
    virtual bool SetBluetoothControllerProperty(char const*,void *,unsigned int);
    virtual IOCommandGate *getCommandGate(void);
    virtual void BroadcastEventNotification(unsigned int,unsigned char,int,unsigned char *,unsigned long long,unsigned short,bool,unsigned char);
    virtual void BroadcastNotification(unsigned int,IOBluetoothHCIControllerConfigState,IOBluetoothHCIControllerConfigState);
    virtual void WaitForBluetoothd(void);
    virtual bool FoundBluetoothd(void);
    virtual unsigned int GetControllerFeatureFlags(void);
    virtual void SetControllerFeatureFlags(unsigned int);
    virtual void setConfigState(IOBluetoothHCIControllerConfigState);
    virtual bool InitializeController(void);
    virtual bool SetupController(bool *);
    virtual bool SetupGeneralController(void);
    virtual bool SetupCommonHardware(void);
    virtual bool ControllerSetupIsComplete(void);
    virtual void ControllerSetupComplete(int);
    virtual bool BluetoothHostControllerSetupCompleted(void);
    virtual bool InitializeHostControllerVariables(bool);
    virtual IOReturn CallInitializeHostControllerVariables(void);
    virtual bool CompleteInitializeHostControllerVariables(void);
    virtual bool CreatePowerReporters(void);
    virtual uint32_t UpdatePowerReports(IOBluetoothHCIControllerInternalPowerState);
    virtual bool CallCreateDeviceReporter(IOBluetoothDevice *);
    virtual bool CreateDeviceReporter(IOBluetoothDevice *);
    virtual IOBluetoothDevice *FindDeviceReporter(BluetoothDeviceAddress const*);
    virtual IOReturn ConvertClassOfDeviceToDeviceType(unsigned int,bool,unsigned short *,char *,unsigned long long *,char *,unsigned char *);
    virtual bool AddDeviceReporter(BluetoothDeviceReporter *);
    virtual void RemoveDeviceReporter(IOBluetoothDevice *);
    virtual bool UpdateDeviceReporter(IOBluetoothDevice *,bool);
    virtual uint32_t GetDeviceCounterForName(unsigned short,char *,char *,unsigned char *);
    virtual void PrintDeviceReporterList(void);
    virtual bool UpdateLESetAdvertisingDataReporter(IOBluetoothHCIRequest *);
    virtual bool SetupPowerStateReporter(void);
    virtual void DesyncIncomingData(int (*)(IOBluetoothHostController*,unsigned char *,unsigned int,unsigned int),unsigned char *,unsigned int);
    virtual void SynchronizePacketSequence(unsigned int);
    virtual void SynchronizeSCOPacketSequence(unsigned int);
    virtual IOBluetoothDevice *FindDeviceWithHandle(unsigned short);
    virtual IOBluetoothDevice *FindDeviceWithSCOHandle(unsigned short);
    virtual IOBluetoothDevice *FindDeviceWithAddress(BluetoothDeviceAddress const*,bool);
    virtual IOBluetoothDevice *FindHearingDeviceWithAddress(BluetoothDeviceAddress const*);
    virtual IOReturn AddHearingDevice(IOBluetoothDevice *);
    virtual void RemoveHearingDevice(IOBluetoothDevice *,bool);
    virtual IOBluetoothDevice *FindLEDeviceWithConnectionHandle(unsigned short);
    virtual IOReturn AddLEDevice(unsigned short);
    virtual void RemoveLEDevice(unsigned short,bool);
    virtual IOReturn AddDevice(IOBluetoothDevice *);
    virtual IOReturn RemoveDevice(IOBluetoothDevice *);
    virtual void PrintDeviceList(void);
    virtual IOReturn SetDevicePublishNotificationState(BluetoothDeviceAddress const*,unsigned short);
    virtual unsigned short GetDevicePublishNotificationState(BluetoothDeviceAddress const*);
    virtual IOReturn CreateDeviceFromLEConnectionResults(BluetoothHCIEventLEConnectionCompleteResults *);
    virtual IOReturn CreateDeviceFromConnectionResults(BluetoothHCIEventConnectionCompleteResults *);
    virtual IOReturn CreateDeviceFromConnectionResults(BluetoothHCIEventConnectionCompleteResults *,bool);
    virtual void DestroyDeviceWithDisconnectionResults(BluetoothHCIEventDisconnectionCompleteResults *);
    virtual void DestroyDevice(IOBluetoothDevice *);
    virtual void DestroyAllDevices(void);
    virtual void terminateServiceNubs(void);
    virtual bool terminateServiceNubsComplete(void);
    virtual void FlushDeviceACLPackets(IOBluetoothDevice *);
    virtual bool SaveNumOutstandingACLPackets(void);
    virtual void DecrementIdleTimerActivityCount(unsigned short);
    virtual void IncrementIdleTimerActivityCount(void);
    virtual void DecrementOutstandingACLPackets(unsigned short,unsigned short,unsigned short,unsigned short,unsigned short,unsigned short);
    virtual IOReturn ProcessFlushOccurredEvent(BluetoothHCIEventFlushOccurredResults *);
    virtual IOReturn ProcessNumberOfCompletedPacketsEvent(unsigned char *);
    virtual IOReturn ProcessHCIControllerResetEvent(void);
    virtual IOReturn DispatchIncomingACLData(unsigned char *,unsigned int);
    virtual IOReturn DispatchIncomingSCOData(unsigned char *,unsigned int,unsigned int,unsigned long long);
    virtual IOReturn OpenDeviceConnection(BluetoothDeviceAddress const*);
    virtual IOReturn OpenDeviceConnectionWL(BluetoothDeviceAddress const*,unsigned short,bool);
    virtual IOReturn SendACLData(IOMemoryDescriptor *);
    virtual IOReturn SendACLPacket(IOBluetoothACLMemoryDescriptor *,IOBluetoothDevice *);
    virtual IOReturn TransferACLPacketToHW(IOMemoryDescriptor *);
    virtual void handleACLPacketTimeout(IOBluetoothACLMemoryDescriptor *);
    virtual IOReturn setUnackQueueCompletionCalled(void *);
    virtual IOReturn SetACLPacketCompletion(void *);
    virtual IOReturn EnqueuePacket(IOMemoryDescriptor *,IOBluetoothDevice *);
    virtual IOReturn DequeuePacket(unsigned short,unsigned short,unsigned short,unsigned short,unsigned short,unsigned short);
    virtual IOReturn RemovePacket(IOBluetoothACLMemoryDescriptor *);
    virtual IOReturn RemoveAllPacketsBelongingTo(IOBluetoothDevice *);
    virtual IOReturn AdjustACLQueuesLimits(IOBluetoothDevice *);
    virtual IOReturn AdjustACLQueuesAllowance(IOBluetoothDevice *,bool);
    virtual const char *CreateACLQueueDebugString(char *,unsigned short);
    virtual IOReturn SendSCOCompleted(IOBluetoothSCOMemoryDescriptorRetainer *,unsigned long long);
    virtual IOReturn SendSCOData(IOMemoryDescriptor *,IOBluetoothSCOMemoryDescriptorRetainer *,int);
    virtual IOReturn SendSCOData(IOMemoryDescriptor *);
    virtual void handleSCOPacketTimeout(IOBluetoothSCOMemoryDescriptorRetainer *);
    virtual void SetNumSCOConnections(unsigned char,unsigned int);
    virtual IOReturn ToggleSCOConnection(void);
    virtual IOReturn ToggleeSCOEV3Connection(void);
    virtual IOReturn ToggleeSCOEV4Connection(void);
    virtual IOReturn ToggleeSCOEV5Connection(void);
    virtual UInt64 getSynchronousConnectionPacketTypeProperty(void);
    virtual IOReturn NeedToSetupController(void);
    virtual bool FullWake(char *);
    
};

#endif /* IOBluetoothHostController_h */
