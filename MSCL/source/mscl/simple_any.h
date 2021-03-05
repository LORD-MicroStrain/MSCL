/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

//Title: simple_any

/* 
 * File:   simple_any.h
 * Author: jonathan_herbst
 * Created on August 7, 2014, 3:51 PM
 * 
 * Idea and most of the code functionality from boost::spirit::hold_any.
 * Interface from boost::any.
 * 
 * A class to hold any type of data, but whose type does not rely on the the
 * type of data being stored.
 * 
 * Example Usage: a list containing many different types.
 * 
 * struct my_type {};
 * 
 * std::list<simple_any> any_list;
 * any_list.emplace_back('a');
 * any_list.emplace_back(std::string("a string"));
 * any_list.emplace_back(52);
 * any_list.emplace_back(my_type());
 * 
 * 
 * Why c-style function pointers are used:
 * The memory for the static function pointers is still allocated at program
 * termination (n3337 Section 3.7.1), but will be invalidated in the case of
 * c++11 style function objects and not c-style pointers because destructors
 * will get called before that point.  Example in function_object_failure.cpp.
 */

#pragma once

#include <typeinfo>
#include <algorithm>

#ifdef _MSC_VER
//MSVC defines type_info outside of the std namespace for some reason
typedef type_info TypeInfo;
#else
typedef std::type_info TypeInfo;
#endif

namespace detail {

/**
 * True and false types.
 */
template<bool Value> struct bool_ {};
typedef bool_<false> false_;
typedef bool_<true> true_;

/**
 * Contained by a default constructed simple_any_MSC_VER
 */
struct empty {};

/**
 * Class containing functions specific to the type.
 */
template<typename Small> struct any_fxns;

/**
 * Functions for types that are bigger than a void*
 */
template<>
struct any_fxns<false_>
{
    template<typename T>
    struct type_fxns
    {
        inline static const TypeInfo& type()
        {
            return typeid(T);
        }
        
        inline static void create(void** dest, const void* src)
        {
            *dest = new T(*reinterpret_cast<const T*>(src));
        }
        
        inline static void clone(void** dest, const void* const * src)
        {
            *dest = new T(*reinterpret_cast<const T*>(*src));
        }

        inline static void destroy(void** object)
        {
            delete reinterpret_cast<T*>(*object);
        }

        inline static void* get(void** object)
        {
            return *object;
        }

        inline static const void* const_get(const void* const * object)
        {
            return *object;
        }
    };
};

/**
 * Functions for types up to the size of a void*.
 * Much more efficient than the method for larger types.
 */
template<>
struct any_fxns<true_>
{
    template<typename T>
    struct type_fxns
    {
        inline static const TypeInfo& type()
        {
            return typeid(T);
        }
        
        inline static void create(void** dest, const void* src)
        {
            new(dest) T(*reinterpret_cast<const T*>(src));
        }
        
        inline static void clone(void** dest, const void* const * src)
        {
            new(dest) T(*reinterpret_cast<const T*>(src));
        }

        inline static void destroy(void** object)
        {
            reinterpret_cast<T*>(object)->~T();
        }

        inline static void* get(void** object)
        {
            return reinterpret_cast<void*>(object);
        }

        inline static const void* const_get(const void* const * object)
        {
            return reinterpret_cast<const void*>(object);
        }
    };
};

/**
 * Typeless binding for any functions.  (this allows simple_any to be typeless)
 * This class uses c-style function pointers rather than c++11 or boost function
 * objects on purpose.
 * 
 */
struct any_fxn
{
    const TypeInfo&(*type)();
    void(*create)(void**, const void*);
    void(*clone)(void**, const void* const *);
    void(*destroy)(void**);
    void*(*get)(void**);
    const void*(*const_get)(const void* const *);
};

template<typename T>
any_fxn* get_any_fxn()
{
    typedef bool_<sizeof(T) <= sizeof(void*)> is_small;
    
    static any_fxn fxns = {
        any_fxns<is_small>::template type_fxns<T>::type,
        any_fxns<is_small>::template type_fxns<T>::create,
        any_fxns<is_small>::template type_fxns<T>::clone,
        any_fxns<is_small>::template type_fxns<T>::destroy,
        any_fxns<is_small>::template type_fxns<T>::get,
        any_fxns<is_small>::template type_fxns<T>::const_get
    };
    
    return &fxns;
};

}

//Class: simple_any
//    A class that holds any type of variable in a type safe manner.
class simple_any
{
    template<typename T>
    friend const T& any_cast(const simple_any&);
    
    template<typename T>
    friend T& any_cast(simple_any&);
    
public:
    simple_any():
    m_fxns(detail::get_any_fxn<detail::empty>())
    {
        detail::empty v;
        m_fxns->create(&m_object, &v);
    }
    
    template<typename T>
    simple_any(const T& x) :
    m_fxns(detail::get_any_fxn<T>())
    {
        m_fxns->create(&m_object, &x);
    }
    
    simple_any(const simple_any& other) :
    m_fxns(other.m_fxns)
    {
        m_fxns->clone(&m_object, &other.m_object);
    }
    
    ~simple_any()
    {
        m_fxns->destroy(&m_object);
    }
    
    simple_any& operator=(const simple_any& other)
    {
        m_fxns->destroy(&m_object);
        m_fxns = other.m_fxns;
        m_fxns->clone(&m_object, &other.m_object);
        return *this;
    }
    
    template<typename T>
    simple_any& operator=(const T& v)
    {
        m_fxns->destroy(&m_object);
        m_fxns = detail::get_any_fxn<T>();
        m_fxns->create(&m_object, &v);
        return *this;
    }
    
    simple_any& swap(simple_any& other)
    {
        std::swap(m_fxns, other.m_fxns);
        std::swap(m_object, other.m_object);
        return *this;
    }
    
    const TypeInfo& type() const
    {
        return m_fxns->type();
    }
    
private:
    detail::any_fxn* m_fxns;
    void* m_object;
};


template<typename T>
const T& any_cast(const simple_any& any)
{
    if(any.type() != typeid(T))
    {
        throw std::bad_cast();
    }
    const void* ptr = any.m_fxns->const_get(&any.m_object);
    return *reinterpret_cast<const T*>(ptr);
}
    
template<typename T>
T& any_cast(simple_any& any)
{
    if(any.type() != typeid(T))
    {
        throw std::bad_cast();
    }
    void* ptr = any.m_fxns->get(&any.m_object);
    return *reinterpret_cast<T*>(ptr);
}
