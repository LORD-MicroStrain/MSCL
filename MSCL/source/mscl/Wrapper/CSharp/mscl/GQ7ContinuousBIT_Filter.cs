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

public class GQ7ContinuousBIT_Filter : ContinuousBIT_Filter {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal GQ7ContinuousBIT_Filter(global::System.IntPtr cPtr, bool cMemoryOwn) : base(msclPINVOKE.GQ7ContinuousBIT_Filter_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(GQ7ContinuousBIT_Filter obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  protected override void Dispose(bool disposing) {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          msclPINVOKE.delete_GQ7ContinuousBIT_Filter(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      base.Dispose(disposing);
    }
  }

  public GQ7ContinuousBIT_Filter() : this(msclPINVOKE.new_GQ7ContinuousBIT_Filter__SWIG_0(), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public GQ7ContinuousBIT_Filter(uint bits) : this(msclPINVOKE.new_GQ7ContinuousBIT_Filter__SWIG_1(bits), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public GQ7ContinuousBIT_Filter_General general() {
    GQ7ContinuousBIT_Filter_General ret = new GQ7ContinuousBIT_Filter_General(msclPINVOKE.GQ7ContinuousBIT_Filter_general(swigCPtr), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
