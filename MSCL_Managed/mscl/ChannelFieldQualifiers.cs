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

public class ChannelFieldQualifiers : global::System.IDisposable 
    , global::System.Collections.Generic.IDictionary<MipTypes.ChannelField, ChannelIndices>
 {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal ChannelFieldQualifiers(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(ChannelFieldQualifiers obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~ChannelFieldQualifiers() {
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
          msclPINVOKE.delete_ChannelFieldQualifiers(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
    }
  }


  public ChannelIndices this[MipTypes.ChannelField key] {
    get {
      return getitem(key);
    }

    set {
      setitem(key, value);
    }
  }

  public bool TryGetValue(MipTypes.ChannelField key, out ChannelIndices value) {
    if (this.ContainsKey(key)) {
      value = this[key];
      return true;
    }
    value = default(ChannelIndices);
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

  public global::System.Collections.Generic.ICollection<MipTypes.ChannelField> Keys {
    get {
      global::System.Collections.Generic.ICollection<MipTypes.ChannelField> keys = new global::System.Collections.Generic.List<MipTypes.ChannelField>();
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

  public global::System.Collections.Generic.ICollection<ChannelIndices> Values {
    get {
      global::System.Collections.Generic.ICollection<ChannelIndices> vals = new global::System.Collections.Generic.List<ChannelIndices>();
      foreach (global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices> pair in this) {
        vals.Add(pair.Value);
      }
      return vals;
    }
  }

  public void Add(global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices> item) {
    Add(item.Key, item.Value);
  }

  public bool Remove(global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices> item) {
    if (Contains(item)) {
      return Remove(item.Key);
    } else {
      return false;
    }
  }

  public bool Contains(global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices> item) {
    if (this[item.Key] == item.Value) {
      return true;
    } else {
      return false;
    }
  }

  public void CopyTo(global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices>[] array) {
    CopyTo(array, 0);
  }

  public void CopyTo(global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices>[] array, int arrayIndex) {
    if (array == null)
      throw new global::System.ArgumentNullException("array");
    if (arrayIndex < 0)
      throw new global::System.ArgumentOutOfRangeException("arrayIndex", "Value is less than zero");
    if (array.Rank > 1)
      throw new global::System.ArgumentException("Multi dimensional array.", "array");
    if (arrayIndex+this.Count > array.Length)
      throw new global::System.ArgumentException("Number of elements to copy is too large.");

    global::System.Collections.Generic.IList<MipTypes.ChannelField> keyList = new global::System.Collections.Generic.List<MipTypes.ChannelField>(this.Keys);
    for (int i = 0; i < keyList.Count; i++) {
      MipTypes.ChannelField currentKey = keyList[i];
      array.SetValue(new global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices>(currentKey, this[currentKey]), arrayIndex+i);
    }
  }

  global::System.Collections.Generic.IEnumerator<global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices>> global::System.Collections.Generic.IEnumerable<global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices>>.GetEnumerator() {
    return new ChannelFieldQualifiersEnumerator(this);
  }

  global::System.Collections.IEnumerator global::System.Collections.IEnumerable.GetEnumerator() {
    return new ChannelFieldQualifiersEnumerator(this);
  }

  public ChannelFieldQualifiersEnumerator GetEnumerator() {
    return new ChannelFieldQualifiersEnumerator(this);
  }

  // Type-safe enumerator
  /// Note that the IEnumerator documentation requires an InvalidOperationException to be thrown
  /// whenever the collection is modified. This has been done for changes in the size of the
  /// collection but not when one of the elements of the collection is modified as it is a bit
  /// tricky to detect unmanaged code that modifies the collection under our feet.
  public sealed class ChannelFieldQualifiersEnumerator : global::System.Collections.IEnumerator,
      global::System.Collections.Generic.IEnumerator<global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices>>
  {
    private ChannelFieldQualifiers collectionRef;
    private global::System.Collections.Generic.IList<MipTypes.ChannelField> keyCollection;
    private int currentIndex;
    private object currentObject;
    private int currentSize;

    public ChannelFieldQualifiersEnumerator(ChannelFieldQualifiers collection) {
      collectionRef = collection;
      keyCollection = new global::System.Collections.Generic.List<MipTypes.ChannelField>(collection.Keys);
      currentIndex = -1;
      currentObject = null;
      currentSize = collectionRef.Count;
    }

    // Type-safe iterator Current
    public global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices> Current {
      get {
        if (currentIndex == -1)
          throw new global::System.InvalidOperationException("Enumeration not started.");
        if (currentIndex > currentSize - 1)
          throw new global::System.InvalidOperationException("Enumeration finished.");
        if (currentObject == null)
          throw new global::System.InvalidOperationException("Collection modified.");
        return (global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices>)currentObject;
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
        MipTypes.ChannelField currentKey = keyCollection[currentIndex];
        currentObject = new global::System.Collections.Generic.KeyValuePair<MipTypes.ChannelField, ChannelIndices>(currentKey, collectionRef[currentKey]);
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


  public ChannelFieldQualifiers() : this(msclPINVOKE.new_ChannelFieldQualifiers__SWIG_0(), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public ChannelFieldQualifiers(ChannelFieldQualifiers other) : this(msclPINVOKE.new_ChannelFieldQualifiers__SWIG_1(ChannelFieldQualifiers.getCPtr(other)), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  private uint size() {
    uint ret = msclPINVOKE.ChannelFieldQualifiers_size(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool empty() {
    bool ret = msclPINVOKE.ChannelFieldQualifiers_empty(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Clear() {
    msclPINVOKE.ChannelFieldQualifiers_Clear(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  private ChannelIndices getitem(MipTypes.ChannelField key) {
    ChannelIndices ret = new ChannelIndices(msclPINVOKE.ChannelFieldQualifiers_getitem(swigCPtr, (int)key), false);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void setitem(MipTypes.ChannelField key, ChannelIndices x) {
    msclPINVOKE.ChannelFieldQualifiers_setitem(swigCPtr, (int)key, ChannelIndices.getCPtr(x));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool ContainsKey(MipTypes.ChannelField key) {
    bool ret = msclPINVOKE.ChannelFieldQualifiers_ContainsKey(swigCPtr, (int)key);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Add(MipTypes.ChannelField key, ChannelIndices value) {
    msclPINVOKE.ChannelFieldQualifiers_Add(swigCPtr, (int)key, ChannelIndices.getCPtr(value));
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool Remove(MipTypes.ChannelField key) {
    bool ret = msclPINVOKE.ChannelFieldQualifiers_Remove(swigCPtr, (int)key);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private global::System.IntPtr create_iterator_begin() {
    global::System.IntPtr ret = msclPINVOKE.ChannelFieldQualifiers_create_iterator_begin(swigCPtr);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private MipTypes.ChannelField get_next_key(global::System.IntPtr swigiterator) {
    MipTypes.ChannelField ret = (MipTypes.ChannelField)msclPINVOKE.ChannelFieldQualifiers_get_next_key(swigCPtr, swigiterator);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void destroy_iterator(global::System.IntPtr swigiterator) {
    msclPINVOKE.ChannelFieldQualifiers_destroy_iterator(swigCPtr, swigiterator);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
