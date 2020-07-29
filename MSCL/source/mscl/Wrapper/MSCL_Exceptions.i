%include "exception.i"
%include "std_except.i"

%allowexception;

//============================================================
//Catch-All exception handler for any exceptions that we
//don't want to actually expose to the user

%exception
{
    try
    {
        $action
    }
    catch(const std::exception& ex)
    {
        SWIG_exception(SWIG_RuntimeError, ex.what());
    }
}
//============================================================

//only define the ugly C# exception code below 
//when running SWIG with the C# compiler option
#ifdef SWIGCSHARP

%insert(runtime)
%{
#include "../MicroStrain/Wireless/Configuration/ConfigIssue.h"

    // Code to handle throwing of C# exception from C/C++ code.
    typedef void (SWIGSTDCALL* CSharpExceptionCallback_t)(const char *);
    typedef void (SWIGSTDCALL* CSharpExceptionWithCodeCallback_t)(const char *, int);
    typedef void (SWIGSTDCALL* CSharpExceptionCallbackConfig_t)(const char *);//std::vector<mscl::ConfigIssue>&);


    //===================================================================================================
    //                                  EXCEPTION: Error
    CSharpExceptionCallback_t exceptionCallback__MSCL_Default = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_Default(CSharpExceptionCallback_t customCallback)
    {
        exceptionCallback__MSCL_Default = customCallback;
    }

    // Note that SWIG detects any method calls named starting with
    // SWIG_CSharpSetPendingException for warning 845
    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_Default(const char *msg)
    {
        exceptionCallback__MSCL_Default(msg);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_Communication
    CSharpExceptionCallback_t exceptionCallback__MSCL_Communication = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_Communication(CSharpExceptionCallback_t customCallback)
    {
        exceptionCallback__MSCL_Communication = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_Communication(const char *msg)
    {
        exceptionCallback__MSCL_Communication(msg);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_NodeCommunication
    CSharpExceptionWithCodeCallback_t exceptionCallback__MSCL_NodeCommunication = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_NodeCommunication(CSharpExceptionWithCodeCallback_t customCallback)
    {
        exceptionCallback__MSCL_NodeCommunication = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_NodeCommunication(const char *msg, unsigned int code)
    {
        exceptionCallback__MSCL_NodeCommunication(msg, code);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_Connection
    CSharpExceptionWithCodeCallback_t exceptionCallback__MSCL_Connection = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_Connection(CSharpExceptionWithCodeCallback_t customCallback)
    {
        exceptionCallback__MSCL_Connection = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_Connection(const char *msg, int code)
    {
        exceptionCallback__MSCL_Connection(msg, code);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_InvalidSerialPort
    CSharpExceptionWithCodeCallback_t exceptionCallback__MSCL_Inv_Com_Port = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_Inv_Com_Port(CSharpExceptionWithCodeCallback_t customCallback)
    {
        exceptionCallback__MSCL_Inv_Com_Port = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_Inv_Com_Port(const char *msg, int code)
    {
        exceptionCallback__MSCL_Inv_Com_Port(msg, code);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_InvalidTcpServer
    CSharpExceptionWithCodeCallback_t exceptionCallback__MSCL_Inv_Tcp_Server = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_Inv_Tcp_Server(CSharpExceptionWithCodeCallback_t customCallback)
    {
        exceptionCallback__MSCL_Inv_Tcp_Server = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_Inv_Tcp_Server(const char *msg, int code)
    {
        exceptionCallback__MSCL_Inv_Tcp_Server(msg, code);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_InvalidUnixSocket
    CSharpExceptionWithCodeCallback_t exceptionCallback__MSCL_Inv_Unix_Socket = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_Inv_Unix_Socket(CSharpExceptionWithCodeCallback_t customCallback)
    {
        exceptionCallback__MSCL_Inv_Unix_Socket = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_Inv_Unix_Socket(const char *msg, int code)
    {
        exceptionCallback__MSCL_Inv_Unix_Socket(msg, code);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_NoData
    CSharpExceptionCallback_t exceptionCallback__MSCL_No_Data = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_No_Data(CSharpExceptionCallback_t customCallback)
    {
        exceptionCallback__MSCL_No_Data = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_No_Data(const char *msg)
    {
        exceptionCallback__MSCL_No_Data(msg);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_BadDataType
    CSharpExceptionCallback_t exceptionCallback__MSCL_Bad_Data_Type = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_Bad_Data_Type(CSharpExceptionCallback_t customCallback)
    {
        exceptionCallback__MSCL_Bad_Data_Type = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_Bad_Data_Type(const char *msg)
    {
        exceptionCallback__MSCL_Bad_Data_Type(msg);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_UnknownSampleRate
    CSharpExceptionCallback_t exceptionCallback__MSCL_Unknown_Sample_Rate = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_Unknown_Sample_Rate(CSharpExceptionCallback_t customCallback)
    {
        exceptionCallback__MSCL_Unknown_Sample_Rate = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_Unknown_Sample_Rate(const char *msg)
    {
        exceptionCallback__MSCL_Unknown_Sample_Rate(msg);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_NotSupported
    CSharpExceptionCallback_t exceptionCallback__MSCL_Not_Supported = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_Not_Supported(CSharpExceptionCallback_t customCallback)
    {
        exceptionCallback__MSCL_Not_Supported = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_Not_Supported(const char *msg)
    {
        exceptionCallback__MSCL_Not_Supported(msg);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_MipCmdFailed
    CSharpExceptionWithCodeCallback_t exceptionCallback__MSCL_InertialCmdFailed = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_InertialCmdFailed(CSharpExceptionWithCodeCallback_t customCallback)
    {
        exceptionCallback__MSCL_InertialCmdFailed = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_InertialCmdFailed(const char *msg, int code)
    {
        exceptionCallback__MSCL_InertialCmdFailed(msg, code);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_InvalidConfig
    CSharpExceptionCallbackConfig_t exceptionCallback__MSCL_InvalidConfig = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_InvalidConfig(CSharpExceptionCallbackConfig_t customCallback)
    {
        exceptionCallback__MSCL_InvalidConfig = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_InvalidConfig(const char *msg)
    {
        exceptionCallback__MSCL_InvalidConfig(msg);
    }
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_InvalidNodeConfig
    CSharpExceptionWithCodeCallback_t exceptionCallback__MSCL_InvalidNodeConfig = NULL;

    extern "C" SWIGEXPORT
        void SWIGSTDCALL ExceptionRegisterCallback__MSCL_InvalidNodeConfig(CSharpExceptionWithCodeCallback_t customCallback)
    {
        exceptionCallback__MSCL_InvalidNodeConfig = customCallback;
    }

    static void SWIG_CSharpSetPendingExceptionCustom__MSCL_InvalidNodeConfig(const char *msg, unsigned int code)
    {
        exceptionCallback__MSCL_InvalidNodeConfig(msg, code);
    }
    //===================================================================================================
%}





%pragma(csharp) imclasscode =
%{
    //===================================================================================================
    //                                  EXCEPTION: Error
    class Exception_Helper__MSCL_Default
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message);

        static exception_Delegate customDelegate__MSCL_Default = new exception_Delegate(SetPendingCustomException___MSCL_Default);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_Default")]
        public static extern void ExceptionRegisterCallback__MSCL_Default(exception_Delegate customCallback);

        static void SetPendingCustomException___MSCL_Default(string message)
        {
            SWIGPendingException.Set(new Error(message));
        }

        static Exception_Helper__MSCL_Default()
        {
            ExceptionRegisterCallback__MSCL_Default(customDelegate__MSCL_Default);
        }
    }

    static Exception_Helper__MSCL_Default exceptionHelper_default = new Exception_Helper__MSCL_Default();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_Communication
    class Exception_Helper__MSCL_Communication
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message);

        static exception_Delegate customDelegate__MSCL_Communication = new exception_Delegate(SetPendingCustomException__MSCL_Communication);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_Communication")]
        public static extern void ExceptionRegisterCallback__MSCL_Communication(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_Communication(string message)
        {
            SWIGPendingException.Set(new Error_Communication(message));
        }

        static Exception_Helper__MSCL_Communication()
        {
            ExceptionRegisterCallback__MSCL_Communication(customDelegate__MSCL_Communication);
        }
    }

    static Exception_Helper__MSCL_Communication exceptionHelper_Communication = new Exception_Helper__MSCL_Communication();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_NodeCommunication
    class Exception_Helper__MSCL_NodeCommunication
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message, ushort code);

        static exception_Delegate customDelegate__MSCL_NodeCommunication = new exception_Delegate(SetPendingCustomException__MSCL_NodeCommunication);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_NodeCommunication")]
        public static extern void ExceptionRegisterCallback__MSCL_NodeCommunication(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_NodeCommunication(string message, ushort code)
        {
            SWIGPendingException.Set(new Error_NodeCommunication(message, code));
        }

        static Exception_Helper__MSCL_NodeCommunication()
        {
            ExceptionRegisterCallback__MSCL_NodeCommunication(customDelegate__MSCL_NodeCommunication);
        }
    }

    static Exception_Helper__MSCL_NodeCommunication exceptionHelper_NodeCommunication = new Exception_Helper__MSCL_NodeCommunication();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_Connection
    class Exception_Helper__MSCL_Connection
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message, int code);

        static exception_Delegate customDelegate__MSCL_Connection = new exception_Delegate(SetPendingCustomException__MSCL_Connection);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_Connection")]
        public static extern void ExceptionRegisterCallback__MSCL_Connection(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_Connection(string message, int code)
        {
            SWIGPendingException.Set(new Error_Connection(message, code));
        }

        static Exception_Helper__MSCL_Connection()
        {
            ExceptionRegisterCallback__MSCL_Connection(customDelegate__MSCL_Connection);
        }
    }

    static Exception_Helper__MSCL_Connection exceptionHelper_Connection = new Exception_Helper__MSCL_Connection();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_InvalidSerialPort
    class Exception_Helper__MSCL_Inv_Com_Port
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message, int code);

        static exception_Delegate customDelegate__MSCL_Inv_Com_Port = new exception_Delegate(SetPendingCustomException__MSCL_Inv_Com_Port);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_Inv_Com_Port")]
        public static extern void ExceptionRegisterCallback__MSCL_Inv_Com_Port(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_Inv_Com_Port(string message, int code)
        {
            SWIGPendingException.Set(new Error_InvalidSerialPort(message, code));
        }

        static Exception_Helper__MSCL_Inv_Com_Port()
        {
            ExceptionRegisterCallback__MSCL_Inv_Com_Port(customDelegate__MSCL_Inv_Com_Port);
        }
    }

    static Exception_Helper__MSCL_Inv_Com_Port exceptionHelper_Inv_Com_Port = new Exception_Helper__MSCL_Inv_Com_Port();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_InvalidTcpServer
    class Exception_Helper__MSCL_Inv_Tcp_Server
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message, int code);

        static exception_Delegate customDelegate__MSCL_Inv_Tcp_Server = new exception_Delegate(SetPendingCustomException__MSCL_Inv_Tcp_Server);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_Inv_Tcp_Server")]
        public static extern void ExceptionRegisterCallback__MSCL_Inv_Tcp_Server(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_Inv_Tcp_Server(string message, int code)
        {
            SWIGPendingException.Set(new Error_InvalidTcpServer(message, code));
        }

        static Exception_Helper__MSCL_Inv_Tcp_Server()
        {
            ExceptionRegisterCallback__MSCL_Inv_Tcp_Server(customDelegate__MSCL_Inv_Tcp_Server);
        }
    }

    static Exception_Helper__MSCL_Inv_Tcp_Server exceptionHelper_Inv_Tcp_Server = new Exception_Helper__MSCL_Inv_Tcp_Server();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_InvalidUnixSocket
    class Exception_Helper__MSCL_Inv_Unix_Socket
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message, int code);

        static exception_Delegate customDelegate__MSCL_Inv_Unix_Socket = new exception_Delegate(SetPendingCustomException__MSCL_Inv_Unix_Socket);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_Inv_Unix_Socket")]
        public static extern void ExceptionRegisterCallback__MSCL_Inv_Unix_Socket(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_Inv_Unix_Socket(string message, int code)
        {
            SWIGPendingException.Set(new Error_InvalidUnixSocket(message, code));
        }

        static Exception_Helper__MSCL_Inv_Unix_Socket()
        {
            ExceptionRegisterCallback__MSCL_Inv_Unix_Socket(customDelegate__MSCL_Inv_Unix_Socket);
        }
    }

    static Exception_Helper__MSCL_Inv_Unix_Socket exceptionHelper_Inv_Unix_Socket = new Exception_Helper__MSCL_Inv_Unix_Socket();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_NoData
    class Exception_Helper__MSCL_No_Data
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message);

        static exception_Delegate customDelegate__MSCL_No_Data = new exception_Delegate(SetPendingCustomException__MSCL_No_Data);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_No_Data")]
        public static extern void ExceptionRegisterCallback__MSCL_No_Data(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_No_Data(string message)
        {
            SWIGPendingException.Set(new Error_NoData(message));
        }

        static Exception_Helper__MSCL_No_Data()
        {
            ExceptionRegisterCallback__MSCL_No_Data(customDelegate__MSCL_No_Data);
        }
    }

    static Exception_Helper__MSCL_No_Data exceptionHelper_No_Data = new Exception_Helper__MSCL_No_Data();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_BadDataType
    class Exception_Helper__MSCL_Bad_Data_Type
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message);

        static exception_Delegate customDelegate__MSCL_Bad_Data_Type = new exception_Delegate(SetPendingCustomException__MSCL_Bad_Data_Type);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_Bad_Data_Type")]
        public static extern void ExceptionRegisterCallback__MSCL_Bad_Data_Type(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_Bad_Data_Type(string message)
        {
            SWIGPendingException.Set(new Error_BadDataType(message));
        }

        static Exception_Helper__MSCL_Bad_Data_Type()
        {
            ExceptionRegisterCallback__MSCL_Bad_Data_Type(customDelegate__MSCL_Bad_Data_Type);
        }
    }

    static Exception_Helper__MSCL_Bad_Data_Type exceptionHelper_Bad_Data_Type = new Exception_Helper__MSCL_Bad_Data_Type();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_UnknownSampleRate
    class Exception_Helper__MSCL_Unknown_Sample_Rate
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message);

        static exception_Delegate customDelegate__MSCL_Unknown_Sample_Rate = new exception_Delegate(SetPendingCustomException__MSCL_Unknown_Sample_Rate);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_Unknown_Sample_Rate")]
        public static extern void ExceptionRegisterCallback__MSCL_Unknown_Sample_Rate(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_Unknown_Sample_Rate(string message)
        {
            SWIGPendingException.Set(new Error_UnknownSampleRate(message));
        }

        static Exception_Helper__MSCL_Unknown_Sample_Rate()
        {
            ExceptionRegisterCallback__MSCL_Unknown_Sample_Rate(customDelegate__MSCL_Unknown_Sample_Rate);
        }
    }

    static Exception_Helper__MSCL_Unknown_Sample_Rate exceptionHelper_Unknown_Sample_Rate = new Exception_Helper__MSCL_Unknown_Sample_Rate();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_NotSupported
    class Exception_Helper__MSCL_Not_Supported
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message);

        static exception_Delegate customDelegate__MSCL_Not_Supported = new exception_Delegate(SetPendingCustomException__MSCL_Not_Supported);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_Not_Supported")]
        public static extern void ExceptionRegisterCallback__MSCL_Not_Supported(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_Not_Supported(string message)
        {
            SWIGPendingException.Set(new Error_NotSupported(message));
        }

        static Exception_Helper__MSCL_Not_Supported()
        {
            ExceptionRegisterCallback__MSCL_Not_Supported(customDelegate__MSCL_Not_Supported);
        }
    }

    static Exception_Helper__MSCL_Not_Supported exceptionHelper_Not_Supported = new Exception_Helper__MSCL_Not_Supported();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_MipCmdFailed
    class Exception_Helper__MSCL_InertialCmdFailed
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message, int code);

        static exception_Delegate customDelegate__MSCL_InertialCmdFailed = new exception_Delegate(SetPendingCustomException__MSCL_InertialCmdFailed);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_InertialCmdFailed")]
        public static extern void ExceptionRegisterCallback__MSCL_InertialCmdFailed(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_InertialCmdFailed(string message, int code)
        {
            SWIGPendingException.Set(new Error_MipCmdFailed(message, code));
        }

        static Exception_Helper__MSCL_InertialCmdFailed()
        {
            ExceptionRegisterCallback__MSCL_InertialCmdFailed(customDelegate__MSCL_InertialCmdFailed);
        }
    }

    static Exception_Helper__MSCL_InertialCmdFailed exceptionHelper_InertialCmdFailed = new Exception_Helper__MSCL_InertialCmdFailed();
    //===================================================================================================


    //===================================================================================================
    //                                EXCEPTION: Error_InvalidConfig
    class Exception_Helper__MSCL_InvalidConfig
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message);

        static exception_Delegate customDelegate__MSCL_InvalidConfig = new exception_Delegate(SetPendingCustomException__MSCL_InvalidConfig);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_InvalidConfig")]
        public static extern void ExceptionRegisterCallback__MSCL_InvalidConfig(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_InvalidConfig(string message)
        {
            SWIGPendingException.Set(new Error_InvalidConfig(message));
        }

        static Exception_Helper__MSCL_InvalidConfig()
        {
            ExceptionRegisterCallback__MSCL_InvalidConfig(customDelegate__MSCL_InvalidConfig);
        }
    }

    static Exception_Helper__MSCL_InvalidConfig exceptionHelper_InvalidConfig = new Exception_Helper__MSCL_InvalidConfig();
    //===================================================================================================



    //===================================================================================================
    //                                EXCEPTION: Error_InvalidNodeConfig
    class Exception_Helper__MSCL_InvalidNodeConfig
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message, ushort code);

        static exception_Delegate customDelegate__MSCL_InvalidNodeConfig = new exception_Delegate(SetPendingCustomException__MSCL_InvalidNodeConfig);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_InvalidNodeConfig")]
        public static extern void ExceptionRegisterCallback__MSCL_InvalidNodeConfig(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_InvalidNodeConfig(string message, ushort code)
        {
            SWIGPendingException.Set(new Error_InvalidNodeConfig(message, code));
        }

        static Exception_Helper__MSCL_InvalidNodeConfig()
        {
            ExceptionRegisterCallback__MSCL_InvalidNodeConfig(customDelegate__MSCL_InvalidNodeConfig);
        }
    }

    static Exception_Helper__MSCL_InvalidNodeConfig exceptionHelper_InvalidNodeConfig = new Exception_Helper__MSCL_InvalidNodeConfig();
    //===================================================================================================
%}


//Exception: Error (Base Exception)
%typemap(throws, canthrow = 1) mscl::Error
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_Default($1.what());
    return $null;
}

//Exception: Error_Communication
%typemap(throws, canthrow = 1) mscl::Error_Communication
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_Communication($1.what());
    return $null;
}

//Exception: Error_NodeCommunication
%typemap(throws, canthrow = 1) mscl::Error_NodeCommunication
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_NodeCommunication($1.what(), $1.nodeAddress());
    return $null;
}

//Exception: Error_Connection
%typemap(throws, canthrow = 1) mscl::Error_Connection
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_Connection($1.what(), $1.code());
    return $null;
}

//Exception: Error_InvalidSerialPort
%typemap(throws, canthrow = 1) mscl::Error_InvalidSerialPort
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_Inv_Com_Port($1.what(), $1.code());
    return $null;
}

//Exception: Error_InvalidTcpServer
%typemap(throws, canthrow = 1) mscl::Error_InvalidTcpServer
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_Inv_Tcp_Server($1.what(), $1.code());
    return $null;
}

//Exception: Error_InvalidUnixSocket
%typemap(throws, canthrow = 1) mscl::Error_InvalidUnixSocket
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_Inv_Unix_Socket($1.what(), $1.code());
    return $null;
}

//Exception: Error_NoData
%typemap(throws, canthrow = 1) mscl::Error_NoData
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_No_Data($1.what());
    return $null;
}

//Exception: Error_BadDataType
%typemap(throws, canthrow = 1) mscl::Error_BadDataType
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_Bad_Data_Type($1.what());
    return $null;
}

//Exception: Error_UnknownSampleRate
%typemap(throws, canthrow = 1) mscl::Error_UnknownSampleRate
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_Unknown_Sample_Rate($1.what());
    return $null;
}

//Exception: Error_NotSupported
%typemap(throws, canthrow = 1) mscl::Error_NotSupported
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_Not_Supported($1.what());
    return $null;
}

//Exception: Error_MipCmdFailed
%typemap(throws, canthrow = 1) mscl::Error_MipCmdFailed
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_InertialCmdFailed($1.what(), $1.code());
    return $null;
}

//Exception: Error_InvalidConfig
%typemap(throws, canthrow = 1) mscl::Error_InvalidConfig
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_InvalidConfig($1.issues().at(0).description().c_str()); //can't get the ConfigIssues vector to go across the pInvoke boundary correctly.
    return $null;
}

//Exception: Error_InvalidNodeConfig
%typemap(throws, canthrow = 1) mscl::Error_InvalidNodeConfig
{
    SWIG_CSharpSetPendingExceptionCustom__MSCL_InvalidNodeConfig($1.issues().at(0).description().c_str(), $1.nodeAddress()); //can't get the ConfigIssues vector to go across the pInvoke boundary correctly.
    return $null;
}

#endif







//=========================================================================================================================================================
//Each function that throws one of our generated exceptions (and that we are exposing), needs to tell SWIG which exceptions it can throw
//Note: functions with default parameters must have ALL forms of the function listed here, SWIG will not split them itself.

//Connection
%catches(mscl::Error_InvalidSerialPort, mscl::Error_Connection, mscl::Error)                                                                mscl::Connection::Serial(const std::string& port, int baudRate);
%catches(mscl::Error_InvalidSerialPort, mscl::Error_Connection, mscl::Error)                                                                mscl::Connection::Serial(const std::string& port);
%catches(mscl::Error_InvalidTcpServer, mscl::Error_Connection, mscl::Error)                                                                 mscl::Connection::TcpIp(const std::string& serverAddress, uint16 serverPort);
%catches(mscl::Error_InvalidTcpServer, mscl::Error_Connection, mscl::Error)                                                                 mscl::Connection::TcpIp(const std::string& serverAddress, uint16 serverPort, const std::string& interfaceAddress);
%catches(mscl::Error_InvalidUnixSocket, mscl::Error_Connection, mscl::Error)                                                                mscl::Connection::UnixSocket(const std::string& path);
%catches(mscl::Error_Connection, mscl::Error)                                                                                               mscl::Connection::write(const Bytes& bytes);
%catches(mscl::Error_Connection, mscl::Error)                                                                                               mscl::Connection::writeStr(const std::string& bytes);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytes(uint32 timeout, uint32 maxBytes);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytes(uint32 timeout);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytes();
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytesStr(uint32 timeout, uint32 maxBytes);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytesStr(uint32 timeout);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytesStr();
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytesWithPattern(const Bytes& pattern);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytesWithPattern(const Bytes& pattern, uint32 timeout);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::rawByteMode(bool enable);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getDebugData(uint32 timeout);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getDebugData();
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::debugMode(bool enable);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::updateBaudRate(uint32 baudRate);
%catches(mscl::Error_InvalidSerialPort, mscl::Error_InvalidTcpServer, mscl::Error_InvalidUnixSocket, mscl::Error_Connection, mscl::Error)   mscl::Connection::reconnect();

//BaseStation
%catches(mscl::Error_Connection)                                                                                    mscl::BaseStation::BaseStation(Connection& connection);
%catches(mscl::Error_Connection)                                                                                    mscl::BaseStation::BaseStation(Connection& connection, uint64 baseTimeout);
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::features() const;
%catches(mscl::Error_NoData)                                                                                        mscl::BaseStation::lastCommunicationTime() const;
%catches(mscl::Error_Connection)                                                                                    mscl::BaseStation::ping();
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::readEeprom(uint16 eepromAddress) const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::writeEeprom(uint16 eepromAddress, uint16 value);
%catches(mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                                            mscl::BaseStation::enableBeacon();
%catches(mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                                            mscl::BaseStation::enableBeacon(uint32 utcTime);
%catches(mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                                            mscl::BaseStation::disableBeacon();
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                  mscl::BaseStation::beaconStatus();
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                  mscl::BaseStation::startRfSweepMode();
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                  mscl::BaseStation::startRfSweepMode(uint32 minFreq, uint32 maxFreq, uint32 interval);
%catches(mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                                            mscl::BaseStation::cyclePower();
%catches(mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                                            mscl::BaseStation::cyclePower(bool checkComm);
%catches(mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                                            mscl::BaseStation::resetRadio();
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                  mscl::BaseStation::changeFrequency(WirelessTypes::Frequency frequency);
%catches(mscl::Error_Connection)                                                                                    mscl::BaseStation::broadcastSetToIdle();
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::verifyConfig(const BaseStationConfig& config, ConfigIssues& outIssues) const;
%catches(mscl::Error_NotSupported, mscl::Error_InvalidConfig, mscl::Error_Communication, mscl::Error_Connection)    mscl::BaseStation::applyConfig(const BaseStationConfig& config);
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::frequency() const;
%catches(mscl::Error_Connection, mscl::Error_Communication)                                                         mscl::BaseStation::communicationProtocol() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::firmwareVersion() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::model() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::serial() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::name() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::microcontroller() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::regionCode() const;
%catches(mscl::Error_Connection)                                                                                    mscl::BaseStation::getData();
%catches(mscl::Error_Connection)                                                                                    mscl::BaseStation::getData(uint32 timeout);
%catches(mscl::Error_Connection)                                                                                    mscl::BaseStation::getData(uint32 timeout, uint32 maxSweeps);
%catches(mscl::Error_Connection)                                                                                    mscl::BaseStation::getNodeDiscoveries();
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::getTransmitPower() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::getButtonLongPress(uint8 buttonNumber) const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::getButtonShortPress(uint8 buttonNumber) const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::getAnalogPairingEnabled() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::getAnalogTimeoutTime() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::getAnalogTimeoutVoltage() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::getAnalogExceedanceEnabled() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::getAnalogPair(uint8 portNumber) const;

//BaseStationConfig
%catches(mscl::Error_NoData)            mscl::BaseStationConfig::transmitPower() const;
%catches(mscl::Error_NoData)            mscl::BaseStationConfig::buttonLongPress(uint8 buttonNumber) const;
%catches(mscl::Error_NoData)            mscl::BaseStationConfig::buttonShortPress(uint8 buttonNumber) const;
%catches(mscl::Error_NoData)            mscl::BaseStationConfig::analogPairingEnable() const;
%catches(mscl::Error_NoData)            mscl::BaseStationConfig::analogTimeoutTime() const;
%catches(mscl::Error_NoData)            mscl::BaseStationConfig::analogTimeoutVoltage() const;
%catches(mscl::Error_NoData)            mscl::BaseStationConfig::analogExceedanceEnable() const;
%catches(mscl::Error_NoData)            mscl::BaseStationConfig::analogPairing(uint8 portNumber, const BaseStationAnalogPair& pair);

//WirelessNodeConfig
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::defaultMode() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::inactivityTimeout() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::checkRadioInterval() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::transmitPower() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::samplingMode() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::sampleRate() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::activeChannels() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::numSweeps() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::unlimitedDuration() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::dataFormat() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::dataCollectionMethod() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::timeBetweenBursts() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::lostBeaconTimeout() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::inputRange(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::hardwareOffset(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::antiAliasingFilter(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::cfcFilterConfig() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::lowPassFilter(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::highPassFilter(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::gaugeFactor(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::gaugeResistance() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::excitationVoltage() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::filterSettlingTime(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::thermocoupleType(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::tempSensorOptions(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::debounceFilter(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::pullUpResistor(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::linearEquation(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::unit(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::equation(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::fatigueOptions() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::histogramOptions() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::activitySense() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::eventTriggerOptions() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::diagnosticInterval() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::storageLimitMode() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::sensorDelay() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::dataMode() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::derivedDataRate() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::derivedVelocityUnit() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::derivedChannelMask(WirelessTypes::DerivedCategory category) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::communicationProtocol() const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::sensorOutputMode() const;

//WirelessNode
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::features() const;
%catches(mscl::Error_NoData)                                                                                                mscl::WirelessNode::lastCommunicationTime() const;
%catches(mscl::Error_Connection)                                                                                            mscl::WirelessNode::ping();
%catches(mscl::Error_Connection)                                                                                            mscl::WirelessNode::sleep();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::readEeprom(uint16 location) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::writeEeprom(uint16 location, uint16 value);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getDiagnosticInfo();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::cyclePower();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::resetRadio();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::changeFrequency(WirelessTypes::Frequency frequency);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::frequency() const;
%catches(mscl::Error_NodeCommunication, mscl::Error_Connection)                                                             mscl::WirelessNode::communicationProtocol() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::firmwareVersion() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::model() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::serial() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::microcontroller() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::radioFeatures() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::dataStorageSize() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::percentFull() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::regionCode() const;
%catches(mscl::Error_Communication, mscl::Error_Connection)                                                                 mscl::WirelessNode::setToIdle();
%catches(mscl::Error_NodeCommunication, mscl::Error_Connection)                                                             mscl::WirelessNode::erase();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_InvalidNodeConfig, mscl::Error_Connection)    mscl::WirelessNode::startNonSyncSampling();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_InvalidNodeConfig, mscl::Error_Connection)    mscl::WirelessNode::resendStartSyncSampling();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::clearHistogram();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::autoBalance(const ChannelMask& mask, float targetPercent);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::autoCal_shmLink();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::autoCal_shmLink201();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::autoShuntCal(const ChannelMask& mask, const ShuntCalCmdInfo& commandInfo);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::poll(const ChannelMask& mask);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::testCommunicationProtocol(WirelessTypes::CommProtocol protocol);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::verifyConfig(const WirelessNodeConfig& config, ConfigIssues& outIssues) const;
%catches(mscl::Error_NotSupported, mscl::Error_InvalidNodeConfig, mscl::Error_NodeCommunication, mscl::Error_Connection)    mscl::WirelessNode::applyConfig(const WirelessNodeConfig& config);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getNumDatalogSessions() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getDefaultMode() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getInactivityTimeout() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getCheckRadioInterval() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getTransmitPower() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getSamplingMode() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getActiveChannels() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getSampleRate() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getNumSweeps() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getUnlimitedDuration() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getDataFormat() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getDataCollectionMethod() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getTimeBetweenBursts() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getLostBeaconTimeout() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getInputRange(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getHardwareOffset(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getAntiAliasingFilter(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getCfcFilterConfiguration() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getLowPassFilter(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getHighPassFilter(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getDebounceFilter(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getPullUpResistor(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getSensorOutputMode() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getGaugeFactor(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getExcitationVoltage() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getAdcVoltageRef() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getGainAmplifierVoltageRef() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getGaugeResistance() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getNumActiveGauges() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getLowBatteryThreshold() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getFilterSettlingTime(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getThermocoupleType(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getTempSensorOptions(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getLinearEquation(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getUnit(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getEquationType(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getFactoryCalibrationLinearEq(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getFactoryCalibrationUnit(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getFactoryCalibrationEqType(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getFatigueOptions() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getHistogramOptions() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getActivitySense() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getEventTriggerOptions() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getDiagnosticInterval() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getStorageLimitMode() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getSensorDelay() const;
%catches(mscl::Error_NodeCommunication, mscl::Error_Connection)                                                             mscl::WirelessNode::getDataMode() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getDerivedDataRate() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getDerivedChannelMask(WirelessTypes::DerivedCategory category) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getDerivedVelocityUnit() const;

//NodeFeatures
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::channelType(uint8 channelNumber) const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::minSensorDelay() const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::maxSensorDelay() const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::normalizeSensorDelay(uint32 delay) const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod) const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::maxSampleRate(WirelessTypes::SamplingMode samplingMode, const ChannelMask& channels, WirelessTypes::DataCollectionMethod dataCollectionMethod) const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::maxSampleRateForSettlingTime(WirelessTypes::SettlingTime filterSettlingTime, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::maxFilterSettlingTime(const SampleRate& rate) const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const;

//DisplacementNode
%catches(mscl::Error_Communication, mscl::Error_Connection, mscl::Error)                                                            mscl::DisplacementNode::DisplacementNode(Connection connection);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::DisplacementNode::doCommand(uint8 descriptorSet, uint8 cmdDescriptor, const Bytes& fieldData, bool ackNackResponse, bool dataResponse, uint8 responseDataDescriptor) const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::DisplacementNode::doCommand(uint8 descriptorSet, uint8 cmdDescriptor, const Bytes& fieldData, bool ackNackResponse, bool dataResponse) const;
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::DisplacementNode::getDataPackets();
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::DisplacementNode::getDataPackets(uint32 timeout);
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::DisplacementNode::getDataPackets(uint32 maxPackets);
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::DisplacementNode::getDataPackets(uint32 timeout, uint32 maxPackets);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection, mscl::Error_NotSupported, mscl::Error)        mscl::DisplacementNode::features();
%catches(mscl::Error_NoData)                                                                                                        mscl::DisplacementNode::lastCommunicationTime();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::DisplacementNode::firmwareVersion() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::DisplacementNode::model() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::DisplacementNode::modelName() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::DisplacementNode::modelNumber() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::DisplacementNode::serialNumber() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::DisplacementNode::lotNumber() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::DisplacementNode::deviceOptions() const;
%catches(mscl::Error_Connection)                                                                                                    mscl::DisplacementNode::ping();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::DisplacementNode::setToIdle();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::DisplacementNode::cyclePower();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::DisplacementNode::resume();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::DisplacementNode::getDisplacementOutputDataRate() const;
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::DisplacementNode::getAnalogToDisplacementCal() const;
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::DisplacementNode::setDeviceTime();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::DisplacementNode::setDeviceTime(uint64 nanoseconds);

//RTKNode
%catches(mscl::Error_Communication, mscl::Error_Connection, mscl::Error)                                                            mscl::RTKNode::RTKNode(Connection connection);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::RTKNode::doCommand(uint8 descriptorSet, uint8 cmdDescriptor, const Bytes& fieldData, bool ackNackResponse, bool dataResponse, uint8 responseDataDescriptor) const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::RTKNode::doCommand(uint8 descriptorSet, uint8 cmdDescriptor, const Bytes& fieldData, bool ackNackResponse, bool dataResponse) const;
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::RTKNode::getDataPackets();
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::RTKNode::getDataPackets(uint32 timeout);
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::RTKNode::getDataPackets(uint32 maxPackets);
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::RTKNode::getDataPackets(uint32 timeout, uint32 maxPackets);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection, mscl::Error_NotSupported, mscl::Error)        mscl::RTKNode::features();
%catches(mscl::Error_NoData)                                                                                                        mscl::RTKNode::lastCommunicationTime();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::RTKNode::firmwareVersion() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::RTKNode::model() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::RTKNode::modelName() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::RTKNode::modelNumber() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::RTKNode::serialNumber() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::RTKNode::lotNumber() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::RTKNode::deviceOptions() const;
%catches(mscl::Error_Connection)                                                                                                    mscl::RTKNode::ping();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::RTKNode::setToIdle();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::RTKNode::cyclePower();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::RTKNode::resume();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::RTKNode::getRTKOutputDataRate() const;
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::RTKNode::getDeviceStatusFlags() const;

//InertialNode
%catches(mscl::Error_Communication, mscl::Error_Connection, mscl::Error)                                                            mscl::InertialNode::InertialNode(Connection connection);
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::InertialNode::getDataPackets();
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::InertialNode::getDataPackets(uint32 timeout);
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::InertialNode::getDataPackets(uint32 maxPackets);
%catches(mscl::Error_Connection, mscl::Error)                                                                                       mscl::InertialNode::getDataPackets(uint32 timeout, uint32 maxPackets);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection, mscl::Error_NotSupported, mscl::Error)        mscl::InertialNode::features();
%catches(mscl::Error_NoData)                                                                                                        mscl::InertialNode::lastCommunicationTime();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::InertialNode::firmwareVersion() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::InertialNode::model() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::InertialNode::modelName() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::InertialNode::modelNumber() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::InertialNode::serialNumber() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::InertialNode::lotNumber() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::InertialNode::deviceOptions() const;
%catches(mscl::Error_Connection)                                                                                                    mscl::InertialNode::ping();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getDataRateBase(MipTypes::DataClass dataClass);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getActiveChannelFields(MipTypes::DataClass dataClass);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error)        mscl::InertialNode::setActiveChannelFields(MipTypes::DataClass dataClass, const MipChannels& channels);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::saveActiveChannelFields(MipTypes::DataClass dataClass);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setFactoryStreamingChannels(InertialTypes::FactoryStreamingOption option);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getCommunicationMode();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                               mscl::InertialNode::setCommunicationMode(uint8 communicationMode);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::enableDataStream(MipTypes::DataClass dataClass);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::enableDataStream(MipTypes::DataClass dataClass, bool enable);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::resetFilter();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getAutoInitialization();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setAutoInitialization(bool enable);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getAltitudeAid();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setAltitudeAid(bool enable);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getPitchRollAid();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setPitchRollAid(bool enable);

%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setVelocityZUPT(const ZUPTSettingsData& ZUPTSettings);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getVelocityZUPT();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setVelocityZUPT(const ZUPTSettingsData& ZUPTSettings);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getVelocityZUPT();

%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::tareOrientation(const TareAxisValues& axisValue);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::cmdedVelZUPT();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::cmdedAngRateZUPT();

%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setInitialAttitude(const EulerAngles& attitude);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setInitialHeading(float heading);
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::InertialNode::setToIdle();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::InertialNode::cyclePower();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::InertialNode::resume();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::InertialNode::saveSettingsAsStartup(MipTypes::MipCommands cmdIds);
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::InertialNode::saveSettingsAsStartup();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::InertialNode::loadStartupSettings();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_Connection)                                               mscl::InertialNode::loadFactoryDefaultSettings();
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::pollData(MipTypes::DataClass dataClass, const MipTypes::MipChannelFields& fields);
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::pollData(MipTypes::DataClass dataClass);
%catches(mscl::Error_Communication, mscl::Error_MipCmdFailed, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getConfigCommandBytes();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getInitialFilterConfiguration();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setInitialFilterConfiguration(FilterInitializationValues filterConfig);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getSensorToVehicleRotation_eulerAngles();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setSensorToVehicleRotation_eulerAngles(const EulerAngles& angles);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getSensorToVehicleRotation_matrix();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setSensorToVehicleRotation_matrix(const Matrix_3x3& dcm);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getSensorToVehicleRotation_quaternion();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setSensorToVehicleRotation_quaternion(const Quaternion& rotation);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getGNSSAssistedFixControl();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setGNSSAssistedFixControl(bool enableAssistedFix);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getGNSSAssistTimeUpdate();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setGNSSAssistTimeUpdate(const TimeUpdate& timeUpdate);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getGPSTimeUpdate(MipTypes::TimeFrame timeFrame);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setGPSTimeUpdate(MipTypes::TimeFrame, mscl::uint32 timeData);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getSBASSettings();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setSBASSettings(const SBASSettingsData& dataToUse);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getConstellationSettings();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setConstellationSettings(const ConstellationSettingsData& dataToUse);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getAccelerometerBias();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setAccelerometerBias(const GeometricVector& biasVector);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getGyroBias();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setGyroBias(const GeometricVector& biasVector);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::captureGyroBias(const uint16& samplingTime);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::findMagnetometerCaptureAutoCalibration();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::saveMagnetometerCaptureAutoCalibration();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setMagnetometerSoftIronMatrix(const Matrix_3x3& matrix);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getMagnetometerSoftIronMatrix();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setMagnetometerHardIronOffset(const GeometricVector& offsetVector);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getMagnetometerHardIronOffset();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setConingAndScullingEnable(bool enable);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getConingAndScullingEnable();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setUARTBaudRate(uint32 baudRate);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getUARTBaudRate();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setAdvancedLowPassFilterSettings(const AdvancedLowPassFilterConfig& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getAdvancedLowPassFilterSettings(const MipTypes::MipChannelFields& dataDescriptors);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setComplementaryFilterSettings(const ComplementaryFilterData& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getComplementaryFilterSettings();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getBasicDeviceStatus();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getDiagnosticDeviceStatus();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::sendRawRTCM_2_3Message(const RTCMMessage& theMessage);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setVehicleDynamicsMode(const VehicleModeType& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getVehicleDynamicsMode();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setEstimationControlFlags(const EstimationControlOptions& flags);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getEstimationControlFlags();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setInclinationSource(const GeographicSourceOptions& options);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getInclinationSource();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setDeclinationSource(const GeographicSourceOptions& options);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getDeclinationSource();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setMagneticFieldMagnitudeSource(const GeographicSourceOptions& options);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getMagneticFieldMagnitudeSource();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setGNSS_SourceControl(const GNSS_Source& gnssSource);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getGNSS_SourceControl();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::sendExternalGNSSUpdate(const ExternalGNSSUpdateData& gnssUpdateData);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setHeadingUpdateControl(const HeadingUpdateOptions& headingUpdateOptions);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getHeadingUpdateControl();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setGravityErrorAdaptiveMeasurement(const AdaptiveMeasurementData& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getGravityErrorAdaptiveMeasurement();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setMagnetometerErrorAdaptiveMeasurement(const AdaptiveMeasurementData& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getMagnetometerErrorAdaptiveMeasurement();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setMagDipAngleErrorAdaptiveMeasurement(const AdaptiveMeasurementData& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getMagDipAngleErrorAdaptiveMeasurement();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setMagNoiseStandardDeviation(const GeometricVector& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getMagNoiseStandardDeviation();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setGravNoiseStandardDeviation(const GeometricVector& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getGravNoiseStandardDeviation();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setAccelNoiseStandardDeviation(const GeometricVector& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getAccelNoiseStandardDeviation();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setGyroNoiseStandardDeviation(const GeometricVector& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getGyroNoiseStandardDeviation();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setPressureAltNoiseStandardDeviation(const float& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getPressureAltNoiseStandardDeviation();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setHardIronOffsetProcessNoise(const GeometricVector& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getHardIronOffsetProcessNoise();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setAccelBiasModelParams(const GeometricVectors& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getAccelBiasModelParams();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setGyroBiasModelParams(const GeometricVectors& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getGyroBiasModelParams();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setSoftIronMatrixProcessNoise(const Matrix_3x3& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getSoftIronMatrixProcessNoise();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setFixedReferencePosition(const FixedReferencePositionData& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getFixedReferencePosition();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setGPSDynamicsMode(const InertialTypes::GPSDynamicsMode& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getGPSDynamicsMode();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setDevicePowerState(const InertialTypes::PowerState& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getDevicePowerState();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setDeviceStreamFormat(const InertialTypes::StreamFormat& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getDeviceStreamFormat();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setSignalConditioningSettings(const SignalConditioningValues& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getSignalConditioningSettings();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setEnableDisableMeasurements(const EnableDisableMeasurements& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getEnableDisableMeasurements();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setGravityNoiseMinimum(const GeometricVectors& data);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getGravityNoiseMinimum();
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::sendExternalHeadingUpdate(const HeadingData& headingData);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::sendExternalHeadingUpdate(const HeadingData& headingData, const TimeUpdate& timestamp);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::aidingMeasurementEnabled(InertialTypes::AidingMeasurementSource aidingSource) const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::enableDisableAidingMeasurement(InertialTypes::AidingMeasurementSource aidingSource, bool enable);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getKinematicConstraints() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setKinematicConstraints(KinematicConstraints constraintOptions);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getAdaptiveFilterOptions() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setAdaptiveFilterOptions(AutoAdaptiveFilterOptions options);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getMultiAntennaOffset(uint8 receiverId) const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setMultiAntennaOffset(uint8 receiverId, mscl::PositionOffset offset);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getPpsSource() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setPpsSource(InertialTypes::PpsInputOutput ppsSource);
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::getPpsOutput() const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                     mscl::InertialNode::setPpsOutput(InertialTypes::PpsInputOutput ppsOutput);

// Inertial DeviceStatusData
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::systemState();
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::gnssPowerStateOn() const;
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::gnss1PpsPulseInfo();
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::imuStreamInfo();
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::gnssStreamInfo();
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::estimationFilterStreamInfo();
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::imuMessageInfo();
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::gnssMessageInfo();
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::comPortInfo();
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::usbPortInfo();
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::hasMagnetometer() const;
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::magnetometerInitializationFailed() const;
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::hasPressure() const;
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::pressureInitializationFailed() const;
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::gnssReceiverInitializationFailed() const;
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::coldStartOnPowerOn() const;
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::temperatureInfo();
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::powerState() const;
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::gyroRange() const;
%catches(mscl::Error_NoData)            mscl::DeviceStatusData::accelRange() const;


//MipNodeFeatures
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)         mscl::MipNodeFeatures::supportedChannelFields(MipTypes::DataClass dataClass) const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)         mscl::MipNodeFeatures::supportedSampleRates(MipTypes::DataClass dataClass) const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                   mscl::MipNodeFeatures::supportsCategory(MipTypes::DataClass dataClass) const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                   mscl::MipNodeFeatures::supportsCommand(MipTypes::Command commandId) const;
%catches(mscl::Error_MipCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                   mscl::MipNodeFeatures::supportedCommands() const;

//Value
%catches(mscl::Error_BadDataType)                   mscl::Value::as_float() const;
%catches(mscl::Error_BadDataType)                   mscl::Value::as_double() const;
%catches(mscl::Error_BadDataType)                   mscl::Value::as_uint8() const;
%catches(mscl::Error_BadDataType)                   mscl::Value::as_uint16() const;
%catches(mscl::Error_BadDataType)                   mscl::Value::as_uint32() const;
%catches(mscl::Error_BadDataType)                   mscl::Value::as_int16() const;
%catches(mscl::Error_BadDataType)                   mscl::Value::as_int32() const;
%catches(mscl::Error_BadDataType)                   mscl::Value::as_bool() const;
%catches(mscl::Error_BadDataType)                   mscl::Value::as_ChannelMask() const;
%catches(mscl::Error_BadDataType)                   mscl::Value::as_string() const;

//DataPoint
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_float() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_double() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_uint8() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_uint16() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_uint32() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_int16() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_int32() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_bool() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_string() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_Vector() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_Matrix() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_Timestamp() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_Bytes() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_StructuralHealth() const;
%catches(mscl::Error_BadDataType)                   mscl::DataPoint::as_RfSweep() const;

//WirelessDataPoint
%catches(mscl::Error_NotSupported)                  mscl::WirelessDataPoint::channelProperty() const;

//Vector / Matrix
%catches(std::out_of_range)                         mscl::Vector::as_floatAt(uint16 index) const;
%catches(std::out_of_range)                         mscl::Vector::as_uint16At(uint16 index)const;
%catches(std::out_of_range)                         mscl::Vector::as_uint8At(uint16 index)const;
%catches(std::out_of_range)                         mscl::Matrix::as_floatAt(uint16 row, uint16 column) const;
%catches(std::out_of_range)                         mscl::Matrix::as_uint16At(uint16 row, uint16 column) const;
%catches(std::out_of_range)                         mscl::Matrix::as_uint8At(uint16 row, uint16 column) const;

//SyncSamplingNetwork
%catches(mscl::Error_Communication, mscl::Error_Connection)                                                                                                             mscl::SyncSamplingNetwork::SyncSamplingNetwork(const BaseStation& networkBaseStation);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_InvalidNodeConfig, mscl::Error_Connection, mscl::Error_UnknownSampleRate, mscl::Error)    mscl::SyncSamplingNetwork::addNode(WirelessNode& node);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_InvalidNodeConfig, mscl::Error_Connection, mscl::Error_UnknownSampleRate, mscl::Error)    mscl::SyncSamplingNetwork::addNode(WirelessNode& node, const WirelessNodeConfig& pendingConfig);
%catches(mscl::Error_NodeCommunication, mscl::Error_Connection, mscl::Error)                                                                                            mscl::SyncSamplingNetwork::removeNode(uint16 nodeAddress);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection, mscl::Error_UnknownSampleRate)                                                mscl::SyncSamplingNetwork::lossless(bool enable);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection, mscl::Error_UnknownSampleRate)                                                mscl::SyncSamplingNetwork::communicationProtocol(WirelessTypes::CommProtocol protocol);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection, mscl::Error)                                                                  mscl::SyncSamplingNetwork::applyConfiguration();
%catches(mscl::Error_Communication, mscl::Error_Connection, mscl::Error)                                                                                                mscl::SyncSamplingNetwork::startSampling();
%catches(mscl::Error_Communication, mscl::Error_Connection, mscl::Error)                                                                                                mscl::SyncSamplingNetwork::startSampling(Timestamp startTime);
%catches(mscl::Error_Communication, mscl::Error_Connection, mscl::Error)                                                                                                mscl::SyncSamplingNetwork::startSampling_noBeacon();
%catches(mscl::Error)                                                                                                                                                   mscl::SyncSamplingNetwork::getNodeNetworkInfo(uint16 nodeAddress);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection, mscl::Error_UnknownSampleRate)                                                mscl::SyncSamplingNetwork::refresh();

//ArmedDataloggingNetwork
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_InvalidNodeConfig, mscl::Error_Connection, mscl::Error)               mscl::ArmedDataloggingNetwork::addNode(const WirelessNode& node, const std::string& message);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_InvalidNodeConfig, mscl::Error_Connection, mscl::Error)               mscl::ArmedDataloggingNetwork::addNode(const WirelessNode& node);
%catches(mscl::Error_NodeCommunication, mscl::Error_Connection, mscl::Error)                                                                        mscl::ArmedDataloggingNetwork::startSampling();

//DatalogDownloader
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection, mscl::Error)                                mscl::DatalogDownloader::DatalogDownloader(const WirelessNode& node);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection, mscl::Error)                                mscl::DatalogDownloader::DatalogDownloader(const WirelessNode& node, uint16 startAddress, uint32 size);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_NoData, mscl::Error_Connection, mscl::Error)            mscl::DatalogDownloader::getNextData();

//SampleRate
%catches(mscl::Error_UnknownSampleRate) mscl::SampleRate::FromWirelessEepromValue(WirelessTypes::SampleRate eepromValue);

//SetToIdleStatus
%catches(mscl::Error_Connection)        mscl::SetToIdleStatus::cancel();

//FatigueOptions
%catches(mscl::Error_NoData)            mscl::FatigueOptions::snCurveSegment(uint8 segmentId) const;

//EventTriggerOptions
%catches(mscl::Error_NoData)            mscl::EventTriggerOptions::trigger(uint8 triggerIndex) const;

%catches(mscl::Error_NotSupported)      mscl::ChannelGroup::eepromLocation(WirelessTypes::ChannelGroupSetting setting) const;

%catches(mscl::Error)                   mscl::WsdaFinder::WsdaFinder();


//================================================================================================================================================Running Swig: ========