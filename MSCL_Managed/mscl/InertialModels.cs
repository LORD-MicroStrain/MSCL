//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.12
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace mscl {

public class InertialModels : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal InertialModels(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(InertialModels obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~InertialModels() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          msclPINVOKE.delete_InertialModels(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public InertialModels() : this(msclPINVOKE.new_InertialModels(), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public enum NodeModel {
    node_3dm = 6201,
    node_fasA = 6207,
    node_3dm_gx2 = 6215,
    node_3dm_dh3 = 6219,
    node_3dm_gx3_15 = 6227,
    node_3dm_gx3_25 = 6223,
    node_3dm_gx3_35 = 6225,
    node_3dm_gx3_45 = 6228,
    node_3dm_rq1_45 = 6232,
    node_3dm_gx4_15 = 6233,
    node_3dm_gx4_25 = 6234,
    node_3dm_gx4_45 = 6236,
    node_3dm_gx5_10 = 6255,
    node_3dm_gx5_15 = 6254,
    node_3dm_gx5_25 = 6253,
    node_3dm_gx5_35 = 6252,
    node_3dm_gx5_45 = 6251,
    node_3dm_cv5_10 = 6259,
    node_3dm_cv5_15 = 6258,
    node_3dm_cv5_25 = 6257,
    node_3dm_cv5_45 = 6256
  }

}

}
