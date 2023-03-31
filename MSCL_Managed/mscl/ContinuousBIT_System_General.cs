//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 4.0.0
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace mscl {

public class ContinuousBIT_System_General : Bitfield {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal ContinuousBIT_System_General(global::System.IntPtr cPtr, bool cMemoryOwn) : base(msclPINVOKE.ContinuousBIT_System_General_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(ContinuousBIT_System_General obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  protected override void Dispose(bool disposing) {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          msclPINVOKE.delete_ContinuousBIT_System_General(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      base.Dispose(disposing);
    }
  }

  public byte flags() {
    byte ret = msclPINVOKE.ContinuousBIT_System_General_flags(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool systemClockFailure() {
    bool ret = msclPINVOKE.ContinuousBIT_System_General_systemClockFailure(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool powerFault() {
    bool ret = msclPINVOKE.ContinuousBIT_System_General_powerFault(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool firmwareFault() {
    bool ret = msclPINVOKE.ContinuousBIT_System_General_firmwareFault(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool timingOverload() {
    bool ret = msclPINVOKE.ContinuousBIT_System_General_timingOverload(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool bufferOverrun() {
    bool ret = msclPINVOKE.ContinuousBIT_System_General_bufferOverrun(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static readonly byte SYSTEM_CLOCK_FAILURE = msclPINVOKE.ContinuousBIT_System_General_SYSTEM_CLOCK_FAILURE_get();
  public static readonly byte POWER_FAULT = msclPINVOKE.ContinuousBIT_System_General_POWER_FAULT_get();
  public static readonly byte FIRMWARE_FAULT = msclPINVOKE.ContinuousBIT_System_General_FIRMWARE_FAULT_get();
  public static readonly byte TIMING_OVERLOAD = msclPINVOKE.ContinuousBIT_System_General_TIMING_OVERLOAD_get();
  public static readonly byte BUFFER_OVERRUN = msclPINVOKE.ContinuousBIT_System_General_BUFFER_OVERRUN_get();
}

}
