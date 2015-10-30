#include "common_head.h"
#include "usblib.h"
#include "usbmsc.h"
#include "host/usbhost.h"
#include "host/usbhmsc.h"
#include "usb_stick.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

//*****************************************************************************
//
// The control table used by the uDMA controller.  This table must be aligned
// to a 1024 byte boundary.  In this application uDMA is only used for USB,
// so only the first 6 channels are needed.
//
//*****************************************************************************
#if defined(ewarm)
#pragma data_alignment=1024
tDMAControlTable g_sDMAControlTable[6];
#elif defined(ccs)
#pragma DATA_ALIGN(g_sDMAControlTable, 1024)
tDMAControlTable g_sDMAControlTable[6];
#else
tDMAControlTable g_sDMAControlTable[6] __attribute__ ((aligned(1024)));
#endif


static bool is_usb_host_ready = false;

//*****************************************************************************
//
// The global that holds all of the host drivers in use in the application.
// In this case, only the MSC class is loaded.
//
//*****************************************************************************
static tUSBHostClassDriver const * const g_ppHostClassDrivers[] =
{
    &g_sUSBHostMSCClassDriver
};

//*****************************************************************************
//
// This global holds the number of class drivers in the g_ppHostClassDrivers
// list.
//
//*****************************************************************************
#define NUM_CLASS_DRIVERS       (sizeof(g_ppHostClassDrivers) /               \
                                 sizeof(g_ppHostClassDrivers[0]))


//*****************************************************************************
//
// Hold the current state for the application.
//
//*****************************************************************************
volatile enum
{
    //
    // No device is present.
    //
    STATE_NO_DEVICE,

    //
    // Mass storage device is being enumerated.
    //
    STATE_DEVICE_ENUM,
}
g_eState;

//*****************************************************************************
//
// The instance data for the MSC driver.
//
//*****************************************************************************
tUSBHMSCInstance *g_psMSCInstance = 0;


//*****************************************************************************
//
// The size of the host controller's memory pool in bytes.
//
//*****************************************************************************
#define HCD_MEMORY_SIZE         128

//*****************************************************************************
//
// The memory pool to provide to the Host controller driver.
//
//*****************************************************************************
uint8_t g_pHCDPool[HCD_MEMORY_SIZE];

//*****************************************************************************
//
// This is the callback from the MSC driver.
//
// \param ui32Instance is the driver instance which is needed when communicating
// with the driver.
// \param ui32Event is one of the events defined by the driver.
// \param pvData is a pointer to data passed into the initial call to register
// the callback.
//
// This function handles callback events from the MSC driver.  The only events
// currently handled are the \b MSC_EVENT_OPEN and \b MSC_EVENT_CLOSE.  This
// allows the main routine to know when an MSC device has been detected and
// enumerated and when an MSC device has been removed from the system.
//
// \return Returns \e true on success or \e false on failure.
//
//*****************************************************************************
static void
MSCCallback(tUSBHMSCInstance *psMSCInstance, uint32_t ui32Event, void *pvData)
{
    //
    // Determine the event.
    //
    switch(ui32Event)
    {
        //
        // Called when the device driver has successfully enumerated an MSC
        // device.
        //
        case MSC_EVENT_OPEN:
        {
            //
            // Proceed to the enumeration state.
            //
            g_eState = STATE_DEVICE_ENUM;
					
					  usb_send_msg(USB_STICK_READY);
					
            break;
        }

        //
        // Called when the device driver has been unloaded due to error or
        // the device is no longer present.
        //
        case MSC_EVENT_CLOSE:
        {
            //
            // Go back to the "no device" state and wait for a new connection.
            //
            g_eState = STATE_NO_DEVICE;
            break;
        }

        default:
        {
            break;
        }
    }
}

//*****************************************************************************
//
// Configure the USB controller and power the bus.
//
// This function configures the USB controller for host operation.
// It is assumed that the main system clock has been configured at this point.
//
// \return None.
//
//*****************************************************************************
void ConfigureUSBInterface(void)
{
    //
    // Enable the uDMA controller and set up the control table base.
    // This is required by usblib.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    SysCtlDelay(80);
    uDMAEnable();
    uDMAControlBaseSet(g_sDMAControlTable);

    //
    // Enable the USB controller.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_USB0);

    //
    // Set the USB pins to be controlled by the USB controller.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinConfigure(GPIO_PD6_USB0EPEN);
    GPIOPinTypeUSBDigital(GPIO_PORTD_BASE, GPIO_PIN_6);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    GPIOPinTypeUSBAnalog(GPIO_PORTL_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    GPIOPinTypeUSBAnalog(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Register the host class driver
    //
    USBHCDRegisterDrivers(0, g_ppHostClassDrivers, NUM_CLASS_DRIVERS);

    //
    // Open an instance of the mass storage class driver.
    //
    g_psMSCInstance = USBHMSCDriveOpen(0, MSCCallback);

    //
    // Initialize the power configuration. This sets the power enable signal
    // to be active high and does not enable the power fault.
    //
    USBHCDPowerConfigInit(0, USBHCD_VBUS_AUTO_HIGH | USBHCD_VBUS_FILTER);

    //
    // Force the USB mode to host with no callback on mode changes since
    // there should not be any.
    //
    USBStackModeSet(0, eUSBModeForceHost, 0);

    //
    // Wait 10ms for the pin to go low.
    //
    SysCtlDelay(gSysClock/100);

    //
    // Initialize the host controller.
    //
    USBHCDInit(0, g_pHCDPool, HCD_MEMORY_SIZE);
}



//*****************************************************************************
//
// Read a sector from the USB mass storage device.
//
// \param ui32Sector is the sector to read from the connected USB mass storage
// device (memory stick)
// \param pui8Buf is a pointer to the buffer where the sector data should be
// stored
//
// This is the application-specific implementation of a function to read
// sectors from a storage device, in this case a USB mass storage device.
// This function is called from the \e simple_fs.c file when it needs to read
// data from the storage device.
//
// \return Non-zero if data was read from the device, 0 if no data was read.
//
//*****************************************************************************
uint32_t
SimpleFsReadMediaSector(uint32_t ui32Sector, uint8_t *pui8Buf)
{
    //
    // Return the requested sector from the connected USB mass storage
    // device.
    //
    return(USBHMSCBlockRead(g_psMSCInstance, ui32Sector, pui8Buf, 1));
}

static void usb_msg_handler(usb_msg_t *msg)
{
	
	switch(msg->msg){
		case USB_STICK_READY:
			
		   SYS_TRACE(USB_STICK_DEBUG, ("USB_STICK_READY\r\n"));
			break;
		
		case USB_HOST_READY:
			SYS_TRACE(USB_STICK_DEBUG, ("USB_HOST_READY\r\n"));
			is_usb_host_ready = true;
			break;
		
		case USB_INTERFACE_CONFIG:
			SYS_TRACE(USB_STICK_DEBUG, ("USB_INTERFACE_CONFIG\r\n"));
			ConfigureUSBInterface();
			break;
		
		default:
			break;
	}
	
}


xQueueHandle gUsbQueue;



void usb_stick_task(void *para)
{
	
	usb_msg_t msg;
	
	gUsbQueue = xQueueCreate(20, sizeof(usb_msg_t));
	
	OSAL_ASSERT(gUsbQueue != NULL);
	
	while(1){
		
		if(is_usb_host_ready == true){
			USBHCDMain();
		}

    if(xQueueReceive(gUsbQueue, &msg, 0)){
			usb_msg_handler(&msg);
		 }
		 
		vTaskDelay(50/portTICK_RATE_MS);
  }
}



void usb_send_msg(umsg_type type)
{
	 usb_msg_t msg;

   msg.msg = type;
	
	 xQueueSend(gUsbQueue, &msg, portMAX_DELAY);
}






