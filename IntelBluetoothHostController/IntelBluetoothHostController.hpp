//
//  IOBluetoothHostControllerUSBTransport.h
//  IntelBluetoothHostController
//
//  Created by zxystd on 2021/2/23.
//

#include "IOBluetoothHostControllerUSBTransport.h"
#include "BroadcomVSC.h"

#define SET_THIS_POINTER_VALUE(_type_, _offset_, _value_) \
*(_type_ *)((char *)this + _offset_) = _value_
//memset(((char *)this + _offset_), (_value_), sizeof(_type_))

class IntelBluetoothHostController : public IOBluetoothHostControllerUSBTransport {
    OSDeclareDefaultStructors(IntelBluetoothHostController)
    
public:
    virtual  IOService * probe( IOService *     provider, SInt32    *     score ) override;
    virtual bool init( OSDictionary * dictionary = NULL ) override;
    virtual bool start( IOService * provider ) override;
    virtual void stop( IOService * provider ) override;
    virtual void free() override;
    virtual bool NeedToTurnOnUSBDebug(void) override;
    virtual bool ControllerSupportWoBT(void) override;
    virtual unsigned char GetRadioPowerState(void) override;
    virtual void SetRadioPowerState(unsigned char) override;
    virtual bool InitializeTransportWL(IOService *) override;
    virtual bool PrepareControllerForSleep(void) override;
    virtual bool PrepareControllerWakeFromSleep(void) override;
    virtual bool PrepareControllerForPowerOff(bool) override;
    virtual bool PrepareControllerForPowerOn(void) override;
    virtual bool ConfigurePM(IOService *) override;
    virtual IOReturn systemWillShutdownWL(unsigned int,void *) override;
    
private:
    void releaseAll();
    
    static void onWatchdogEvent(OSObject *owner, IOTimerEventSource *sender);
    
private:
    IOWorkLoop *fWorkLoop;
    IOCommandGate *fCommandGate;
    IOTimerEventSource *fWatchdogEventSource;
    IOUSBHostDevice *fUsbHostDevice;
    unsigned char radioPowerState;
};
