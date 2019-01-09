//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.6
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace mscl {

public class Version : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal Version(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Version obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~Version() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          msclPINVOKE.delete_Version(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }
 
    public override bool Equals(object obj){Version other = obj as Version; return this.__eq__(other);}
    public override int GetHashCode(){ return (int)(majorPart() ^ minorPart() ^ patchPart()); }
    public static bool operator<(Version v1, Version v2){return v1.__lt__(v2);} 
    public static bool operator<=(Version v1, Version v2){return v1.__le__(v2);} 
    public static bool operator>(Version v1, Version v2){return v1.__gt__(v2);} 
    public static bool operator>=(Version v1, Version v2){return v1.__ge__(v2);} 

  public Version() : this(msclPINVOKE.new_Version__SWIG_0(), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public Version(uint major, uint minor, uint patch) : this(msclPINVOKE.new_Version__SWIG_1(major, minor, patch), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public Version(uint major, uint minor) : this(msclPINVOKE.new_Version__SWIG_2(major, minor), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public Version(Version other) : this(msclPINVOKE.new_Version__SWIG_3(Version.getCPtr(other)), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool __eq__(Version cmp) {
    bool ret = msclPINVOKE.Version___eq__(swigCPtr, Version.getCPtr(cmp));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool __ne__(Version cmp) {
    bool ret = msclPINVOKE.Version___ne__(swigCPtr, Version.getCPtr(cmp));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool __lt__(Version cmp) {
    bool ret = msclPINVOKE.Version___lt__(swigCPtr, Version.getCPtr(cmp));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool __le__(Version cmp) {
    bool ret = msclPINVOKE.Version___le__(swigCPtr, Version.getCPtr(cmp));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool __gt__(Version cmp) {
    bool ret = msclPINVOKE.Version___gt__(swigCPtr, Version.getCPtr(cmp));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool __ge__(Version cmp) {
    bool ret = msclPINVOKE.Version___ge__(swigCPtr, Version.getCPtr(cmp));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public override string ToString() {
    string ret = msclPINVOKE.Version_ToString(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool fromString(string strVersion) {
    bool ret = msclPINVOKE.Version_fromString(swigCPtr, strVersion);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint majorPart() {
    uint ret = msclPINVOKE.Version_majorPart(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint minorPart() {
    uint ret = msclPINVOKE.Version_minorPart(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint patchPart() {
    uint ret = msclPINVOKE.Version_patchPart(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
