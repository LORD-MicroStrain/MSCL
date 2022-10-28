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

public class GnssSignalConfigOptions : global::System.IDisposable 
    , global::System.Collections.Generic.IDictionary<MipChannelIdentifier.GnssConstellationIds, Bytes>
 {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnssSignalConfigOptions(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(GnssSignalConfigOptions obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnssSignalConfigOptions() {
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
          msclPINVOKE.delete_GnssSignalConfigOptions(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
    }
  }


  public Bytes this[MipChannelIdentifier.GnssConstellationIds key] {
    get {
      return getitem(key);
    }

    set {
      setitem(key, value);
    }
  }

  public bool TryGetValue(MipChannelIdentifier.GnssConstellationIds key, out Bytes value) {
    if (this.ContainsKey(key)) {
      value = this[key];
      return true;
    }
    value = default(Bytes);
    return false;
  }

  public int Count {
    get {
      return (int)size();
    }
  }

  public bool IsReadOnly {
    get {
      return false;
    }
  }

  public global::System.Collections.Generic.ICollection<MipChannelIdentifier.GnssConstellationIds> Keys {
    get {
      global::System.Collections.Generic.ICollection<MipChannelIdentifier.GnssConstellationIds> keys = new global::System.Collections.Generic.List<MipChannelIdentifier.GnssConstellationIds>();
      int size = this.Count;
      if (size > 0) {
        global::System.IntPtr iter = create_iterator_begin();
        for (int i = 0; i < size; i++) {
          keys.Add(get_next_key(iter));
        }
        destroy_iterator(iter);
      }
      return keys;
    }
  }

  public global::System.Collections.Generic.ICollection<Bytes> Values {
    get {
      global::System.Collections.Generic.ICollection<Bytes> vals = new global::System.Collections.Generic.List<Bytes>();
      foreach (global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes> pair in this) {
        vals.Add(pair.Value);
      }
      return vals;
    }
  }

  public void Add(global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes> item) {
    Add(item.Key, item.Value);
  }

  public bool Remove(global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes> item) {
    if (Contains(item)) {
      return Remove(item.Key);
    } else {
      return false;
    }
  }

  public bool Contains(global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes> item) {
    if (this[item.Key] == item.Value) {
      return true;
    } else {
      return false;
    }
  }

  public void CopyTo(global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes>[] array) {
    CopyTo(array, 0);
  }

  public void CopyTo(global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes>[] array, int arrayIndex) {
    if (array == null)
      throw new global::System.ArgumentNullException("array");
    if (arrayIndex < 0)
      throw new global::System.ArgumentOutOfRangeException("arrayIndex", "Value is less than zero");
    if (array.Rank > 1)
      throw new global::System.ArgumentException("Multi dimensional array.", "array");
    if (arrayIndex+this.Count > array.Length)
      throw new global::System.ArgumentException("Number of elements to copy is too large.");

    global::System.Collections.Generic.IList<MipChannelIdentifier.GnssConstellationIds> keyList = new global::System.Collections.Generic.List<MipChannelIdentifier.GnssConstellationIds>(this.Keys);
    for (int i = 0; i < keyList.Count; i++) {
      MipChannelIdentifier.GnssConstellationIds currentKey = keyList[i];
      array.SetValue(new global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes>(currentKey, this[currentKey]), arrayIndex+i);
    }
  }

  global::System.Collections.Generic.IEnumerator<global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes>> global::System.Collections.Generic.IEnumerable<global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes>>.GetEnumerator() {
    return new GnssSignalConfigOptionsEnumerator(this);
  }

  global::System.Collections.IEnumerator global::System.Collections.IEnumerable.GetEnumerator() {
    return new GnssSignalConfigOptionsEnumerator(this);
  }

  public GnssSignalConfigOptionsEnumerator GetEnumerator() {
    return new GnssSignalConfigOptionsEnumerator(this);
  }

  // Type-safe enumerator
  /// Note that the IEnumerator documentation requires an InvalidOperationException to be thrown
  /// whenever the collection is modified. This has been done for changes in the size of the
  /// collection but not when one of the elements of the collection is modified as it is a bit
  /// tricky to detect unmanaged code that modifies the collection under our feet.
  public sealed class GnssSignalConfigOptionsEnumerator : global::System.Collections.IEnumerator,
      global::System.Collections.Generic.IEnumerator<global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes>>
  {
    private GnssSignalConfigOptions collectionRef;
    private global::System.Collections.Generic.IList<MipChannelIdentifier.GnssConstellationIds> keyCollection;
    private int currentIndex;
    private object currentObject;
    private int currentSize;

    public GnssSignalConfigOptionsEnumerator(GnssSignalConfigOptions collection) {
      collectionRef = collection;
      keyCollection = new global::System.Collections.Generic.List<MipChannelIdentifier.GnssConstellationIds>(collection.Keys);
      currentIndex = -1;
      currentObject = null;
      currentSize = collectionRef.Count;
    }

    // Type-safe iterator Current
    public global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes> Current {
      get {
        if (currentIndex == -1)
          throw new global::System.InvalidOperationException("Enumeration not started.");
        if (currentIndex > currentSize - 1)
          throw new global::System.InvalidOperationException("Enumeration finished.");
        if (currentObject == null)
          throw new global::System.InvalidOperationException("Collection modified.");
        return (global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes>)currentObject;
      }
    }

    // Type-unsafe IEnumerator.Current
    object global::System.Collections.IEnumerator.Current {
      get {
        return Current;
      }
    }

    public bool MoveNext() {
      int size = collectionRef.Count;
      bool moveOkay = (currentIndex+1 < size) && (size == currentSize);
      if (moveOkay) {
        currentIndex++;
        MipChannelIdentifier.GnssConstellationIds currentKey = keyCollection[currentIndex];
        currentObject = new global::System.Collections.Generic.KeyValuePair<MipChannelIdentifier.GnssConstellationIds, Bytes>(currentKey, collectionRef[currentKey]);
      } else {
        currentObject = null;
      }
      return moveOkay;
    }

    public void Reset() {
      currentIndex = -1;
      currentObject = null;
      if (collectionRef.Count != currentSize) {
        throw new global::System.InvalidOperationException("Collection modified.");
      }
    }

    public void Dispose() {
      currentIndex = -1;
      currentObject = null;
    }
  }


  public GnssSignalConfigOptions() : this(msclPINVOKE.new_GnssSignalConfigOptions__SWIG_0(), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnssSignalConfigOptions(GnssSignalConfigOptions other) : this(msclPINVOKE.new_GnssSignalConfigOptions__SWIG_1(GnssSignalConfigOptions.getCPtr(other)), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  private uint size() {
    uint ret = msclPINVOKE.GnssSignalConfigOptions_size(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool empty() {
    bool ret = msclPINVOKE.GnssSignalConfigOptions_empty(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Clear() {
    msclPINVOKE.GnssSignalConfigOptions_Clear(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  private Bytes getitem(MipChannelIdentifier.GnssConstellationIds key) {
    Bytes ret = new Bytes(msclPINVOKE.GnssSignalConfigOptions_getitem(swigCPtr, (int)key), false);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void setitem(MipChannelIdentifier.GnssConstellationIds key, Bytes x) {
    msclPINVOKE.GnssSignalConfigOptions_setitem(swigCPtr, (int)key, Bytes.getCPtr(x));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool ContainsKey(MipChannelIdentifier.GnssConstellationIds key) {
    bool ret = msclPINVOKE.GnssSignalConfigOptions_ContainsKey(swigCPtr, (int)key);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Add(MipChannelIdentifier.GnssConstellationIds key, Bytes value) {
    msclPINVOKE.GnssSignalConfigOptions_Add(swigCPtr, (int)key, Bytes.getCPtr(value));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool Remove(MipChannelIdentifier.GnssConstellationIds key) {
    bool ret = msclPINVOKE.GnssSignalConfigOptions_Remove(swigCPtr, (int)key);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private global::System.IntPtr create_iterator_begin() {
    global::System.IntPtr ret = msclPINVOKE.GnssSignalConfigOptions_create_iterator_begin(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private MipChannelIdentifier.GnssConstellationIds get_next_key(global::System.IntPtr swigiterator) {
    MipChannelIdentifier.GnssConstellationIds ret = (MipChannelIdentifier.GnssConstellationIds)msclPINVOKE.GnssSignalConfigOptions_get_next_key(swigCPtr, swigiterator);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void destroy_iterator(global::System.IntPtr swigiterator) {
    msclPINVOKE.GnssSignalConfigOptions_destroy_iterator(swigCPtr, swigiterator);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

}

}