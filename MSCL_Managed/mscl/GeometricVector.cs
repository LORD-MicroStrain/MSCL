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

public class GeometricVector : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GeometricVector(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(GeometricVector obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~GeometricVector() {
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
          msclPINVOKE.delete_GeometricVector(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
    }
  }

  public static GeometricVector VectorECEF(float x_init, float y_init, float z_init) {
    GeometricVector ret = new GeometricVector(msclPINVOKE.GeometricVector_VectorECEF(x_init, y_init, z_init), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static GeometricVector VectorNED(float north, float east, float down) {
    GeometricVector ret = new GeometricVector(msclPINVOKE.GeometricVector_VectorNED(north, east, down), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GeometricVector(float x_init, float y_init, float z_init, PositionVelocityReferenceFrame ref_) : this(msclPINVOKE.new_GeometricVector__SWIG_0(x_init, y_init, z_init, (int)ref_), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public GeometricVector(float x_init, float y_init, float z_init) : this(msclPINVOKE.new_GeometricVector__SWIG_1(x_init, y_init, z_init), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public GeometricVector() : this(msclPINVOKE.new_GeometricVector__SWIG_2(), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public void fromMipFieldValues(MipFieldValues data, byte offset, bool includesFrame) {
    msclPINVOKE.GeometricVector_fromMipFieldValues__SWIG_0(swigCPtr, MipFieldValues.getCPtr(data), offset, includesFrame);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public void fromMipFieldValues(MipFieldValues data, byte offset) {
    msclPINVOKE.GeometricVector_fromMipFieldValues__SWIG_1(swigCPtr, MipFieldValues.getCPtr(data), offset);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public void fromMipFieldValues(MipFieldValues data) {
    msclPINVOKE.GeometricVector_fromMipFieldValues__SWIG_2(swigCPtr, MipFieldValues.getCPtr(data));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public MipFieldValues asMipFieldValues(bool includeFrame) {
    MipFieldValues ret = new MipFieldValues(msclPINVOKE.GeometricVector_asMipFieldValues__SWIG_0(swigCPtr, includeFrame), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public MipFieldValues asMipFieldValues() {
    MipFieldValues ret = new MipFieldValues(msclPINVOKE.GeometricVector_asMipFieldValues__SWIG_1(swigCPtr), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void appendMipFieldValues(MipFieldValues appendTo, bool includeFrame) {
    msclPINVOKE.GeometricVector_appendMipFieldValues__SWIG_0(swigCPtr, MipFieldValues.getCPtr(appendTo), includeFrame);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public void appendMipFieldValues(MipFieldValues appendTo) {
    msclPINVOKE.GeometricVector_appendMipFieldValues__SWIG_1(swigCPtr, MipFieldValues.getCPtr(appendTo));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public PositionVelocityReferenceFrame referenceFrame {
    set {
      msclPINVOKE.GeometricVector_referenceFrame_set(swigCPtr, (int)value);
      if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      PositionVelocityReferenceFrame ret = (PositionVelocityReferenceFrame)msclPINVOKE.GeometricVector_referenceFrame_get(swigCPtr);
      if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public float x() {
    float ret = msclPINVOKE.GeometricVector_x__SWIG_0(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void x(float x) {
    msclPINVOKE.GeometricVector_x__SWIG_1(swigCPtr, x);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public float y() {
    float ret = msclPINVOKE.GeometricVector_y__SWIG_0(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void y(float y) {
    msclPINVOKE.GeometricVector_y__SWIG_1(swigCPtr, y);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public float z() {
    float ret = msclPINVOKE.GeometricVector_z__SWIG_0(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void z(float z) {
    msclPINVOKE.GeometricVector_z__SWIG_1(swigCPtr, z);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public float north() {
    float ret = msclPINVOKE.GeometricVector_north__SWIG_0(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void north(float north) {
    msclPINVOKE.GeometricVector_north__SWIG_1(swigCPtr, north);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public float east() {
    float ret = msclPINVOKE.GeometricVector_east__SWIG_0(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void east(float east) {
    msclPINVOKE.GeometricVector_east__SWIG_1(swigCPtr, east);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public float down() {
    float ret = msclPINVOKE.GeometricVector_down__SWIG_0(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void down(float down) {
    msclPINVOKE.GeometricVector_down__SWIG_1(swigCPtr, down);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
