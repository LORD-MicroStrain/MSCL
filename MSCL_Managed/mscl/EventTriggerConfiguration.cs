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

public class EventTriggerConfiguration : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal EventTriggerConfiguration(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(EventTriggerConfiguration obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~EventTriggerConfiguration() {
    Dispose(false);
  }

  public void Dispose() {
    Dispose(true);
    global::System.GC.SuppressFinalize(this);
  }

  protected virtual void Dispose(bool disposing) {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          msclPINVOKE.delete_EventTriggerConfiguration(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
    }
  }

  public byte instance {
    set {
      msclPINVOKE.EventTriggerConfiguration_instance_set(swigCPtr, value);
      if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      byte ret = msclPINVOKE.EventTriggerConfiguration_instance_get(swigCPtr);
      if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public EventTriggerConfiguration.Type trigger {
    set {
      msclPINVOKE.EventTriggerConfiguration_trigger_set(swigCPtr, (int)value);
      if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      EventTriggerConfiguration.Type ret = (EventTriggerConfiguration.Type)msclPINVOKE.EventTriggerConfiguration_trigger_get(swigCPtr);
      if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public EventTriggerParameters parameters {
    set {
      msclPINVOKE.EventTriggerConfiguration_parameters_set(swigCPtr, EventTriggerParameters.getCPtr(value));
      if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      global::System.IntPtr cPtr = msclPINVOKE.EventTriggerConfiguration_parameters_get(swigCPtr);
      EventTriggerParameters ret = (cPtr == global::System.IntPtr.Zero) ? null : new EventTriggerParameters(cPtr, false);
      if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public EventTriggerConfiguration() : this(msclPINVOKE.new_EventTriggerConfiguration(), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public enum Type {
    NONE = 0x00,
    GPIO_TRIGGER = 0x01,
    THRESHOLD_TRIGGER = 0x02,
    COMBINATION_TRIGGER = 0x03
  }

}

}