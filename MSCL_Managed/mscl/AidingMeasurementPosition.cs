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

public class AidingMeasurementPosition : AidingMeasurementInput {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal AidingMeasurementPosition(global::System.IntPtr cPtr, bool cMemoryOwn) : base(msclPINVOKE.AidingMeasurementPosition_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(AidingMeasurementPosition obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  protected override void Dispose(bool disposing) {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          msclPINVOKE.delete_AidingMeasurementPosition(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      base.Dispose(disposing);
    }
  }

  public AidingMeasurementPosition() : this(msclPINVOKE.new_AidingMeasurementPosition__SWIG_0(), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public AidingMeasurementPosition(PositionVelocityReferenceFrame referenceFrame, MipFieldValues values) : this(msclPINVOKE.new_AidingMeasurementPosition__SWIG_1((int)referenceFrame, MipFieldValues.getCPtr(values)), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public Position position() {
    Position ret = new Position(msclPINVOKE.AidingMeasurementPosition_position__SWIG_0(swigCPtr), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void position(Position pos) {
    msclPINVOKE.AidingMeasurementPosition_position__SWIG_1(swigCPtr, Position.getCPtr(pos));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public GeometricUncertainty uncertainty() {
    GeometricUncertainty ret = new GeometricUncertainty(msclPINVOKE.AidingMeasurementPosition_uncertainty__SWIG_0(swigCPtr), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void uncertainty(GeometricUncertainty uncertainty) {
    msclPINVOKE.AidingMeasurementPosition_uncertainty__SWIG_1(swigCPtr, GeometricUncertainty.getCPtr(uncertainty));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public PositionVelocityReferenceFrame referenceFrame() {
    PositionVelocityReferenceFrame ret = (PositionVelocityReferenceFrame)msclPINVOKE.AidingMeasurementPosition_referenceFrame__SWIG_0(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void referenceFrame(PositionVelocityReferenceFrame frame) {
    msclPINVOKE.AidingMeasurementPosition_referenceFrame__SWIG_1(swigCPtr, (int)frame);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool valid(AidingMeasurementPosition.ValidFlags val) {
    bool ret = msclPINVOKE.AidingMeasurementPosition_valid__SWIG_0(swigCPtr, (int)val);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void valid(AidingMeasurementPosition.ValidFlags val, bool valid) {
    msclPINVOKE.AidingMeasurementPosition_valid__SWIG_1(swigCPtr, (int)val, valid);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public enum ValidFlags {
    X = 1,
    LATITUDE = 1,
    Y = 2,
    LONGITUDE = 2,
    Z = 4,
    HEIGHT = 4,
    ALTITUDE = 4
  }

}

}
