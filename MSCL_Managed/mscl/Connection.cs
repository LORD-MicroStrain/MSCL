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

public class Connection : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal Connection(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Connection obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~Connection() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          msclPINVOKE.delete_Connection(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public Connection() : this(msclPINVOKE.new_Connection(), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public static Connection Serial(string port, uint baudRate) {
    Connection ret = new Connection(msclPINVOKE.Connection_Serial__SWIG_0(port, baudRate), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static Connection Serial(string port) {
    Connection ret = new Connection(msclPINVOKE.Connection_Serial__SWIG_1(port), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static Connection TcpIp(string serverAddress, ushort serverPort, string interfaceAddress) {
    Connection ret = new Connection(msclPINVOKE.Connection_TcpIp__SWIG_0(serverAddress, serverPort, interfaceAddress), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static Connection TcpIp(string serverAddress, ushort serverPort) {
    Connection ret = new Connection(msclPINVOKE.Connection_TcpIp__SWIG_1(serverAddress, serverPort), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static Connection WebSocket(string host, ushort port) {
    Connection ret = new Connection(msclPINVOKE.Connection_WebSocket(host, port), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static Connection Mock() {
    Connection ret = new Connection(msclPINVOKE.Connection_Mock(), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string description() {
    string ret = msclPINVOKE.Connection_description(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Connection.ConnectionType type() {
    Connection.ConnectionType ret = (Connection.ConnectionType)msclPINVOKE.Connection_type(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void disconnect() {
    msclPINVOKE.Connection_disconnect(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public void reconnect() {
    msclPINVOKE.Connection_reconnect(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public void write(Bytes bytes) {
    msclPINVOKE.Connection_write(swigCPtr, Bytes.getCPtr(bytes));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public void writeStr(string bytes) {
    msclPINVOKE.Connection_writeStr(swigCPtr, bytes);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public void clearBuffer() {
    msclPINVOKE.Connection_clearBuffer(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public uint byteReadPos() {
    uint ret = msclPINVOKE.Connection_byteReadPos(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint byteAppendPos() {
    uint ret = msclPINVOKE.Connection_byteAppendPos(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void rawByteMode(bool enable) {
    msclPINVOKE.Connection_rawByteMode__SWIG_0(swigCPtr, enable);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool rawByteMode() {
    bool ret = msclPINVOKE.Connection_rawByteMode__SWIG_1(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Bytes getRawBytes(uint timeout, uint maxBytes, uint minBytes) {
    Bytes ret = new Bytes(msclPINVOKE.Connection_getRawBytes__SWIG_0(swigCPtr, timeout, maxBytes, minBytes), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Bytes getRawBytes(uint timeout, uint maxBytes) {
    Bytes ret = new Bytes(msclPINVOKE.Connection_getRawBytes__SWIG_1(swigCPtr, timeout, maxBytes), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Bytes getRawBytes(uint timeout) {
    Bytes ret = new Bytes(msclPINVOKE.Connection_getRawBytes__SWIG_2(swigCPtr, timeout), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Bytes getRawBytes() {
    Bytes ret = new Bytes(msclPINVOKE.Connection_getRawBytes__SWIG_3(swigCPtr), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getRawBytesStr(uint timeout, uint maxBytes, uint minBytes) {
    string ret = msclPINVOKE.Connection_getRawBytesStr__SWIG_0(swigCPtr, timeout, maxBytes, minBytes);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getRawBytesStr(uint timeout, uint maxBytes) {
    string ret = msclPINVOKE.Connection_getRawBytesStr__SWIG_1(swigCPtr, timeout, maxBytes);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getRawBytesStr(uint timeout) {
    string ret = msclPINVOKE.Connection_getRawBytesStr__SWIG_2(swigCPtr, timeout);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getRawBytesStr() {
    string ret = msclPINVOKE.Connection_getRawBytesStr__SWIG_3(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Bytes getRawBytesWithPattern(Bytes pattern, uint timeout) {
    Bytes ret = new Bytes(msclPINVOKE.Connection_getRawBytesWithPattern__SWIG_0(swigCPtr, Bytes.getCPtr(pattern), timeout), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Bytes getRawBytesWithPattern(Bytes pattern) {
    Bytes ret = new Bytes(msclPINVOKE.Connection_getRawBytesWithPattern__SWIG_1(swigCPtr, Bytes.getCPtr(pattern)), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void debugMode(bool enable) {
    msclPINVOKE.Connection_debugMode__SWIG_0(swigCPtr, enable);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool debugMode() {
    bool ret = msclPINVOKE.Connection_debugMode__SWIG_1(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public ConnectionDebugDataVec getDebugData(uint timeout) {
    ConnectionDebugDataVec ret = new ConnectionDebugDataVec(msclPINVOKE.Connection_getDebugData__SWIG_0(swigCPtr, timeout), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public ConnectionDebugDataVec getDebugData() {
    ConnectionDebugDataVec ret = new ConnectionDebugDataVec(msclPINVOKE.Connection_getDebugData__SWIG_1(swigCPtr), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public enum ConnectionType {
    connectionType_serial = 0,
    connectionType_tcp = 1,
    connectionType_webSocket = 2,
    connectionType_unixSocket = 3
  }

}

}
