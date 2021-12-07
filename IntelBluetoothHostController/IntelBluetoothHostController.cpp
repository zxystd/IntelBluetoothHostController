//
//  IOBluetoothHostControllerUSBTransport.h
//  IntelBluetoothHostController
//
//  Created by zxystd on 2021/2/23.
//

#include "IntelBluetoothHostController.hpp"

#define super IOBluetoothHostControllerUSBTransport
OSDefineMetaClassAndStructors(IntelBluetoothHostController, IOBluetoothHostControllerUSBTransport)

IOService * IntelBluetoothHostController::
probe( IOService *provider, SInt32    *score )
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    super::probe(provider, score);
    return this;
}

bool IntelBluetoothHostController::
init( OSDictionary * dictionary)
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    bool ret = super::init();
    if (!ret) {
        return false;
    }
    radioPowerState = 0;
    return ret;
}

void IntelBluetoothHostController::
free()
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    super::free();
    releaseAll();
    SET_THIS_POINTER_VALUE(UInt64, 0x148, 0);
}

bool IntelBluetoothHostController::
start( IOService * provider )
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    fUsbHostDevice = OSDynamicCast(IOUSBHostDevice, provider);
    if (!fUsbHostDevice) {
        return false;
    }
    fUsbHostDevice->retain();
    SET_THIS_POINTER_VALUE(UInt64, 0x148, (UInt64)fUsbHostDevice);
    SET_THIS_POINTER_VALUE(char, 0x6B2, 0);
    SET_THIS_POINTER_VALUE(char, 0x6AE, 1);
    if (!super::start(provider)) {
        return false;
    }
    setProperty("InterfaceMatched", false);
    setProperty("ActiveBluetoothControllerVendor", "OpenIntelWireless");
    SET_THIS_POINTER_VALUE(UInt16, 0xB0, 2);
    SET_THIS_POINTER_VALUE(char, 0x6BE, 1);
    fWorkLoop = IOWorkLoop::workLoop();
    if (!fWorkLoop) {
        super::stop(provider);
        releaseAll();
        return false;
    }
    fCommandGate = IOCommandGate::commandGate(this);
    if (!fWorkLoop) {
        super::stop(provider);
        releaseAll();
        return false;
    }
    fWorkLoop->addEventSource(fCommandGate);
    fWatchdogEventSource = IOTimerEventSource::timerEventSource(this, onWatchdogEvent);
    if (!fWatchdogEventSource) {
        super::stop(provider);
        releaseAll();
        return false;
    }
    fWorkLoop->addEventSource(fWatchdogEventSource);
    fWatchdogEventSource->setTimeoutMS(1000);
//    fWatchdogEventSource->enable();
    retain();
    registerService();
    return true;
}

void IntelBluetoothHostController::
onWatchdogEvent(OSObject *owner, IOTimerEventSource *sender)
{
//    IntelBluetoothHostController *controller = OSDynamicCast(IntelBluetoothHostController, owner);
//    IOLog("%s supportpoweroff=%d built-in=%d hwstatus=%d\n", __PRETTY_FUNCTION__, controller->GetSupportPowerOff(), controller->GetBuiltIn(), controller->GetHardwareStatus());
    sender->setTimeoutMS(1000);
}

void IntelBluetoothHostController::
stop( IOService * provider )
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    super::stop(provider);
    release();
}

bool IntelBluetoothHostController::
NeedToTurnOnUSBDebug()
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    return false;
}

bool IntelBluetoothHostController::
ControllerSupportWoBT()
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    SET_THIS_POINTER_VALUE(UInt8, 0xFA, 1);
    return true;
}

unsigned char IntelBluetoothHostController::
GetRadioPowerState()
{
//    IOLog("%s\n", __PRETTY_FUNCTION__);
    return radioPowerState;
}

void IntelBluetoothHostController::
SetRadioPowerState(unsigned char state)
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    radioPowerState = state;
}

bool IntelBluetoothHostController::
InitializeTransportWL(IOService *provider)
{
    bool ret = super::InitializeTransportWL(provider);
    IOLog("%s ret=%d\n", __PRETTY_FUNCTION__, ret);
    SET_THIS_POINTER_VALUE(char, 0xC0, 0);
    if (ret) {
        SetRemoteWakeUp(true);
        SET_THIS_POINTER_VALUE(char, 0xC0, 1);
    }
    return ret;
}

bool IntelBluetoothHostController::
PrepareControllerForSleep()
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    return super::PrepareControllerForSleep();
}

bool IntelBluetoothHostController::
PrepareControllerWakeFromSleep()
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    return super::PrepareControllerWakeFromSleep();
}

bool IntelBluetoothHostController::
PrepareControllerForPowerOff(bool off)
{
    IOLog("%s off=%d\n", __PRETTY_FUNCTION__, off);
    return super::PrepareControllerForPowerOff(off);
}

bool IntelBluetoothHostController::
PrepareControllerForPowerOn()
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    return super::PrepareControllerForPowerOn();
}

bool IntelBluetoothHostController::
ConfigurePM(IOService *provider)
{
    IOLog("%s\n", __PRETTY_FUNCTION__);
    bool ret = super::ConfigurePM(provider);
    radioPowerState = 4;
    return ret;
}

IOReturn IntelBluetoothHostController::
systemWillShutdownWL(unsigned int code, void *buf)
{
    IOReturn ret = super::systemWillShutdownWL(code, buf);
    IOLog("%s code=%d ret=%d\n", __PRETTY_FUNCTION__, code, ret);
    return ret;
}

IOReturn IntelBluetoothHostController::
SendHCIRequest(unsigned char *buf, unsigned long long len)
{
//    HciCommandHdr *hdr = (HciCommandHdr *)buf;
//    kprintf("%s opcode=0x%04x len=%lld\n", __PRETTY_FUNCTION__, hdr->opcode, len);
    bool ret = super::SendHCIRequest(buf, len);
    return ret;
}

bool IntelBluetoothHostController::
ReceiveInterruptData(void *buf, unsigned int len, bool unk)
{
//    HciResponse *response = (HciResponse *)buf;
//    kprintf("%s len=%d opcode=0x%04x status=%d evt=%x plen=%d numCommands=%d\n", __PRETTY_FUNCTION__, len, response->opcode, response->status, response->evt, response->plen, response->numCommands);
    bool ret = super::ReceiveInterruptData(buf, len, unk);
    return ret;
}

void IntelBluetoothHostController::
releaseAll()
{
    if (fCommandGate) {
        if (fWorkLoop) {
            fWorkLoop->removeEventSource(fCommandGate);
        }
        fCommandGate->release();
        fCommandGate = NULL;
    }
    if (fWatchdogEventSource) {
        if (fWorkLoop) {
            fWorkLoop->removeEventSource(fWatchdogEventSource);
        }
        fWatchdogEventSource->release();
        fWatchdogEventSource = NULL;
    }
    if (fWorkLoop) {
        fWorkLoop->release();
        fWorkLoop = NULL;
    }
}
