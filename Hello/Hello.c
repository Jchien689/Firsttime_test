

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>		//Mdepkg/Include/Library

#include <Library/BaseLib.h>				//Mdepkg/Include/Library  AsmCpuid();
#include <Library/PrintLib.h>				//Mdepkg/Include/Library
#include <Library/IoLib.h>				//Mdepkg/Include/Library
#include <Library/PciExpressLib.h>			//Mdepkg/Include/Library
#include <Protocol/PciRootBridgeIo.h>			//Mdepkg/Include/Protocol
#include <Protocol/PciIo.h>				//Mdepkg/Include/Protocol
#include <Protocol/Print2.h>				//Mdepkg/Include/Protocol
#include <Protocol/SimpleTextOut.h>			//Mdepkg/Include/Protocol BOXDRAW_DOUBLE_HORIZONTAL
#include <Protocol/SimpleTextIn.h>			//Mdepkg/Include/Protocol
#include <Protocol/BlockIo.h>				//Mdepkg/Include/Protocol
#include <Protocol/Smbios.h>				//Mdepkg/Include/Protocol
#include <Protocol/AcpiTable.h>			        //Mdepkg/Include/Protocol EFI_ACPI_TABLE_PROTOCOL_GUID
#include <Protocol/AcpiSystemDescriptionTable.h>	//Mdepkg/Include/Protocol
#include <industrystandard/SmBios.h>			//Mdepkg/Include/industrystandard
#include <industrystandard/Acpi.h>	       		//Mdepkg/Include/industrystandard  
#include <Guid/Acpi.h>					//Mdepkg/Include/Guid     EFI_ACPI_TABLE_GUID
#include <Guid/VariableFormat.h>			//MdeModulePkg/Include/Guid
#include <Library/UefiShellLib/UefiShellLib.h>		//ShellPkg/Library/UefiShellLib

#define  In     		gST->ConIn

#define SCAN_CODE_ESC       0x17

EFI_STATUS                  Status;
EFI_INPUT_KEY        	    Key;
EFI_KEY_DATA 	     	    KeyData;	





//*Macro status*/
/**=============================================================================
  Copy from Frontpage.c
  Function waits for a given event to fire, or for an optional timeout to expire.

  @param   Event              The event to wait for
  @param   Timeout            An optional timeout value in 100 ns units.

  @retval  EFI_SUCCESS      Event fired before Timeout expired.
  @retval  EFI_TIME_OUT     Timout expired before Event fired..

================================================================================**/
EFI_STATUS
WaitForSingleEvent (
  IN EFI_EVENT                  Event,
  IN UINT64                     Timeout OPTIONAL
  )
{
  UINTN       Index;
  EFI_STATUS  Status;
  EFI_EVENT   TimerEvent;
  EFI_EVENT   WaitList[2];

//Debug #if 	Post_Code_En
//Debug    Post_code(0x0070,1);		
//Debug #endif //Post_Code_En

  if (Timeout != 0) {
    //
    // Create a timer event
    //
    Status = gBS->CreateEvent (EVT_TIMER, 0, NULL, NULL, &TimerEvent);
    if (!EFI_ERROR (Status)) {
      //
      // Set the timer event
      //
      gBS->SetTimer (
             TimerEvent,
             TimerRelative,
             Timeout
             );

      //
      // Wait for the original event or the timer
      //
      WaitList[0] = Event;
      WaitList[1] = TimerEvent;
      Status      = gBS->WaitForEvent (2, WaitList, &Index);
      gBS->CloseEvent (TimerEvent);

      //
      // If the timer expired, change the return to timed out
      //
      if (!EFI_ERROR (Status) && Index == 1) {
        Status = EFI_TIMEOUT;
      }
    }
  } else {
    //
    // No timeout... just wait on the event
    //
    Status = gBS->WaitForEvent (1, &Event, &Index);
    ASSERT (!EFI_ERROR (Status));
    ASSERT (Index == 0);
  }

  return Status;
}







////*main.c *////


EFI_STATUS
UefiMain (
          IN EFI_HANDLE        ImageHandle,
          IN EFI_SYSTEM_TABLE  *SystemTable
          )
{
	

// test program//
//    UINTN Index;
    
    //EFI_INPUT_KEY key;  
    
//    SystemTable->ConOut->OutputString(SystemTable->ConOut,L"Hello,World!\r\n");
//      SystemTable->ConOut->OutputString(SystemTable->ConOut,L"Press any key to continue...");
//    SystemTable->BootServices->WaitForEvent(1,&(SystemTable->ConIn->WaitForKey),&Index);


/* Get Key sample code*/

	
		while(Key.ScanCode != SCAN_CODE_ESC)
 		{

			WaitForSingleEvent (In->WaitForKey, 0);		//Waiting for KEY
	   		Status = In->ReadKeyStroke (In, &Key);
	 		Print (L"%x",Key.ScanCode); 
	  		Print (L"---%x\n",Key.UnicodeChar); 
	   		Print (L"---%x\n",KeyData.KeyState.KeyShiftState); 

/*
   		//WaitForSingleEvent (In->WaitForKey, 0);		//Waiting for KEY
   		WaitForSingleEvent(SystemTable->ConIn->WaitForKey,0); 		//Waiting for KEY
   		Status = SystemTable->ConIn->ReadKeyStroke (SystemTable->ConIn, &Key);

   		//Status = ST->ConIn->ReadKeyStroke(ST->ConIn, &key); 
   		//Status = In->ReadKeyStroke (In, &Key);
 		Print (L"%x",Key.ScanCode); 
   		Print (L"---%x\n",Key.UnicodeChar); 
   		Print (L"---%x\n",KeyData.KeyState.KeyShiftState); 
*/
   		}



/* 
   CHAR16 a;
   Printf(L"Please press any char:\n");
   scanf("%c",&a);
   Printf(L"Your Char is %c \n",a);

   //SystemTable -> ConOut-> OutputString(SystemTable -> ConOut, L"This is Hello\n"); 
   //Print(L"prinf test Ok.\n");
*/    
	   
   
   
   return EFI_SUCCESS;
}