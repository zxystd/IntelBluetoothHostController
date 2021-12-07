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

typedef struct __attribute__((packed))
{
    uint16_t opcode;    /* OCF & OGF */
    uint8_t plen;
    uint8_t pData[255];
} HciCommandHdr;

typedef struct __attribute__((packed))
{
    uint8_t evt;
    uint8_t plen;
} HciEventHdr;

struct __attribute__((packed)) HciResponse: HciEventHdr
{
    uint8_t numCommands;
    uint16_t opcode;
    uint8_t status;
};

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
    virtual IOReturn SendHCIRequest(unsigned char *,unsigned long long) override;
    virtual bool ReceiveInterruptData(void *,unsigned int,bool) override;
    
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
