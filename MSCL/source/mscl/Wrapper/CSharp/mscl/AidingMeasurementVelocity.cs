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

public class AidingMeasurementVelocity : AidingMeasurementInput {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal AidingMeasurementVelocity(global::System.IntPtr cPtr, bool cMemoryOwn) : base(msclPINVOKE.AidingMeasurementVelocity_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(AidingMeasurementVelocity obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  protected override void Dispose(bool disposing) {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          msclPINVOKE.delete_AidingMeasurementVelocity(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      base.Dispose(disposing);
    }
  }

  public AidingMeasurementVelocity() : this(msclPINVOKE.new_AidingMeasurementVelocity__SWIG_0(), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public AidingMeasurementVelocity(PositionVelocityReferenceFrame referenceFrame, MipFieldValues values) : this(msclPINVOKE.new_AidingMeasurementVelocity__SWIG_1((int)referenceFrame, MipFieldValues.getCPtr(values)), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public Velocity velocity() {
    Velocity ret = new Velocity(msclPINVOKE.AidingMeasurementVelocity_velocity__SWIG_0(swigCPtr), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void velocity(Velocity vel) {
    msclPINVOKE.AidingMeasurementVelocity_velocity__SWIG_1(swigCPtr, Velocity.getCPtr(vel));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public GeometricUncertainty uncertainty() {
    GeometricUncertainty ret = new GeometricUncertainty(msclPINVOKE.AidingMeasurementVelocity_uncertainty__SWIG_0(swigCPtr), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void uncertainty(GeometricUncertainty uncertainty) {
    msclPINVOKE.AidingMeasurementVelocity_uncertainty__SWIG_1(swigCPtr, GeometricUncertainty.getCPtr(uncertainty));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public PositionVelocityReferenceFrame referenceFrame() {
    PositionVelocityReferenceFrame ret = (PositionVelocityReferenceFrame)msclPINVOKE.AidingMeasurementVelocity_referenceFrame__SWIG_0(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void referenceFrame(PositionVelocityReferenceFrame frame) {
    msclPINVOKE.AidingMeasurementVelocity_referenceFrame__SWIG_1(swigCPtr, (int)frame);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool valid(AidingMeasurementVelocity.ValidFlags val) {
    bool ret = msclPINVOKE.AidingMeasurementVelocity_valid__SWIG_0(swigCPtr, (int)val);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void valid(AidingMeasurementVelocity.ValidFlags val, bool valid) {
    msclPINVOKE.AidingMeasurementVelocity_valid__SWIG_1(swigCPtr, (int)val, valid);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public enum ValidFlags {
    X = 1,
    NORTH = 1,
    Y = 2,
    EAST = 2,
    Z = 4,
    DOWN = 4
  }

}

}
