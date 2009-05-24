#include "HvCoreAPIs.h"
#include "hvm.h"
#include "traps.h"

//+++++++++++++++++++++Global Variables Definition+++++++++++++++
PMadDog_Control g_HvmControl;		//Global handlers, include how to setep VMCB etc.
//BOOLEAN bCurrentMachineState = CURRENT_STATE_GUEST; 	//true means it is in guest OS now, otherwise in hypervisor


/**
 * effects: Install HelloWorld VMM hypervisor.
 */
NTSTATUS NTAPI MadDog_InstallHypervisor(PMadDog_Control mdCtl)
{
	g_HvmControl = mdCtl;
	return HvmSwallowBluepill();
}

/**
 * effects: Uninstall HelloWorld VMM Hypervisor
 */
NTSTATUS NTAPI MadDog_UninstallHypervisor()
{
	return HvmSpitOutBluepill();
}

/**
 * effects: Check if this cpu supports Intel VT Technology. Initialize
 */
NTSTATUS NTAPI MadDog_HypervisorInit()
{
	BOOLEAN ArchIsOK = FALSE;
	ArchIsOK = HvmSupport();
	if (!ArchIsOK) {
		Print(("HvmInit(): Your Intel CPU doesn't either support VT Technology or isn't an Intel CPU at all.\n"));
		return STATUS_NOT_SUPPORTED;
	} else {
		Print(("HvmInit(): Your Intel CPU supports VT Technology.\n"));
	}
	return HvmInit();
}

/**
 * effects:Build and Initialize General Trap struct (which is also a Trap struct).
 */
NTSTATUS NTAPI MadDog_InitializeGeneralTrap (
  PCPU Cpu,
  ULONG TrappedVmExit,
  UCHAR RipDelta,
  NBP_TRAP_CALLBACK TrapCallback,
  PNBP_TRAP *pInitializedTrap,
  ULONG uDebugTag //Pool Debug Tag
)
{
	return TrInitializeGeneralTrap(Cpu,TrappedVmExit,RipDelta,TrapCallback,pInitializedTrap,uDebugTag);
}

/**
 * effects: Register trap struct.
 */
NTSTATUS NTAPI MadDog_RegisterTrap (
  PCPU Cpu,
  PNBP_TRAP Trap
)
{
	return TrRegisterTrap(Cpu, Trap);
}