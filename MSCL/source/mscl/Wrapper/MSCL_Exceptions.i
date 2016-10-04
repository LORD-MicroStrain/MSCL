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
    //                                EXCEPTION: Error_InertialCmdFailed
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
            SWIGPendingException.Set(new mscl.Error(message));
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
            SWIGPendingException.Set(new mscl.Error_Communication(message));
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
            SWIGPendingException.Set(new mscl.Error_NodeCommunication(message, code));
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
            SWIGPendingException.Set(new mscl.Error_Connection(message, code));
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
            SWIGPendingException.Set(new mscl.Error_InvalidSerialPort(message, code));
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
            SWIGPendingException.Set(new mscl.Error_InvalidTcpServer(message, code));
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
            SWIGPendingException.Set(new mscl.Error_InvalidUnixSocket(message, code));
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
            SWIGPendingException.Set(new mscl.Error_NoData(message));
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
            SWIGPendingException.Set(new mscl.Error_BadDataType(message));
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
            SWIGPendingException.Set(new mscl.Error_UnknownSampleRate(message));
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
            SWIGPendingException.Set(new mscl.Error_NotSupported(message));
        }

        static Exception_Helper__MSCL_Not_Supported()
        {
            ExceptionRegisterCallback__MSCL_Not_Supported(customDelegate__MSCL_Not_Supported);
        }
    }

    static Exception_Helper__MSCL_Not_Supported exceptionHelper_Not_Supported = new Exception_Helper__MSCL_Not_Supported();
    //===================================================================================================

    //===================================================================================================
    //                                EXCEPTION: Error_InertialCmdFailed
    class Exception_Helper__MSCL_InertialCmdFailed
    {
        // C# delegate for the C/C++ exceptionCallback_MSCL_
        public delegate void exception_Delegate(string message, int code);

        static exception_Delegate customDelegate__MSCL_InertialCmdFailed = new exception_Delegate(SetPendingCustomException__MSCL_InertialCmdFailed);

        [global::System.Runtime.InteropServices.DllImport("$dllimport", EntryPoint = "ExceptionRegisterCallback__MSCL_InertialCmdFailed")]
        public static extern void ExceptionRegisterCallback__MSCL_InertialCmdFailed(exception_Delegate customCallback);

        static void SetPendingCustomException__MSCL_InertialCmdFailed(string message, int code)
        {
            SWIGPendingException.Set(new mscl.Error_InertialCmdFailed(message, code));
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
            SWIGPendingException.Set(new mscl.Error_InvalidConfig(message));
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
            SWIGPendingException.Set(new mscl.Error_InvalidNodeConfig(message, code));
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

//Exception: Error_InertialCmdFailed
%typemap(throws, canthrow = 1) mscl::Error_InertialCmdFailed
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
%catches(mscl::Error_InvalidUnixSocket, mscl::Error_Connection, mscl::Error)                                                                mscl::Connection::UnixSocket(const std::string& path);
%catches(mscl::Error_Connection, mscl::Error)                                                                                               mscl::Connection::write(const Bytes& bytes);
%catches(mscl::Error_Connection, mscl::Error)                                                                                               mscl::Connection::writeStr(const std::string& bytes);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytes(uint32 timeout, uint32 maxBytes);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytes(uint32 timeout);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytes();
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytesStr(uint32 timeout, uint32 maxBytes);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytesStr(uint32 timeout);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getRawBytesStr();
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::rawByteMode(bool enable);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getDebugData(uint32 timeout);
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::getDebugData();
%catches(mscl::Error_Connection)                                                                                                            mscl::Connection::debugMode(bool enable);
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
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                  mscl::BaseStation::startRfSweepMode(uint32 minFreq, uint32 maxFreq, uint32 interval);
%catches(mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                                            mscl::BaseStation::cyclePower();
%catches(mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                                            mscl::BaseStation::resetRadio();
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication, mscl::Error)                  mscl::BaseStation::changeFrequency(WirelessTypes::Frequency frequency);
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::verifyConfig(const BaseStationConfig& config, ConfigIssues& outIssues) const;
%catches(mscl::Error_NotSupported, mscl::Error_InvalidConfig, mscl::Error_Communication, mscl::Error_Connection)    mscl::BaseStation::applyConfig(const BaseStationConfig& config);
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::frequency() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::firmwareVersion() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::model() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::serial() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::name() const;
%catches(mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error_Communication)                               mscl::BaseStation::microcontroller() const;
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
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::gaugeFactor(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::filterSettlingTime(const ChannelMask& mask) const;
%catches(mscl::Error_NoData)            mscl::WirelessNodeConfig::thermocoupleType(const ChannelMask& mask) const;
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

//WirelessNode
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::features() const;
%catches(mscl::Error_NoData)                                                                                                mscl::WirelessNode::lastCommunicationTime() const;
%catches(mscl::Error_Connection, mscl::Error_Communication)                                                                 mscl::WirelessNode::quickPing();
%catches(mscl::Error_Connection)                                                                                            mscl::WirelessNode::ping();
%catches(mscl::Error_Connection)                                                                                            mscl::WirelessNode::sleep();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::readEeprom(uint16 location) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::writeEeprom(uint16 location, uint16 value);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getDiagnosticInfo();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::cyclePower();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::resetRadio();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::changeFrequency(WirelessTypes::Frequency frequency);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::frequency() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::firmwareVersion() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::model() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::serial() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::microcontroller() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::radioFeatures() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::dataStorageSize() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::regionCode() const;
%catches(mscl::Error_Connection)                                                                                            mscl::WirelessNode::setToIdle();
%catches(mscl::Error_NodeCommunication, mscl::Error_Connection)                                                             mscl::WirelessNode::erase();
%catches(mscl::Error_InvalidNodeConfig, mscl::Error_Connection)                                                             mscl::WirelessNode::startNonSyncSampling();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::clearHistogram();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::autoBalance(const ChannelMask& mask, float targetPercent);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::autoCal_shmLink();
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::autoShuntCal(const ChannelMask& mask, const ShuntCalCmdInfo& commandInfo);
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
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getGaugeFactor(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getFilterSettlingTime(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getThermocoupleType(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getLinearEquation(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getUnit(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getEquation(const ChannelMask& mask) const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getFatigueOptions() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getHistogramOptions() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getActivitySense() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getEventTriggerOptions() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getDiagnosticInterval() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getStorageLimitMode() const;
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                   mscl::WirelessNode::getSensorDelay() const;

//NodeFeatures
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::channelType(uint8 channelNumber) const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::minSensorDelay() const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::maxSensorDelay() const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::normalizeSensorDelay(uint32 delay) const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod) const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::maxSampleRate(WirelessTypes::SamplingMode samplingMode, const ChannelMask& channels, WirelessTypes::DataCollectionMethod dataCollectionMethod) const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::maxSampleRateForSettlingTime(WirelessTypes::SettlingTime filterSettlingTime, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod) const;
%catches(mscl::Error_NotSupported)      mscl::NodeFeatures::maxFilterSettlingTime(const SampleRate& rate) const;

//InertialNode
%catches(mscl::Error_Communication, mscl::Error_Connection, mscl::Error)                                                                mscl::InertialNode::InertialNode(Connection connection);
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error)       mscl::InertialNode::supportedSampleRates(InertialTypes::ChannelField channelId);
%catches(mscl::Error_Connection, mscl::Error)                                                                                           mscl::InertialNode::getDataPackets();
%catches(mscl::Error_Connection, mscl::Error)                                                                                           mscl::InertialNode::getDataPackets(uint32 maxPackets);
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_Connection, mscl::Error)                                 mscl::InertialNode::info();
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_Connection, mscl::Error_NotSupported, mscl::Error)       mscl::InertialNode::features();
%catches(mscl::Error_NoData)                                                                                                            mscl::InertialNode::lastCommunicationTime();
%catches(mscl::Error_Connection)                                                                                                        mscl::InertialNode::ping();
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::getDataRateBase(InertialTypes::InertialCategory category);
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::getActiveChannelFields(InertialTypes::InertialCategory category);
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection, mscl::Error)       mscl::InertialNode::setActiveChannelFields(InertialTypes::InertialCategory category, const InertialChannels& channels);
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::getCommunicationMode();
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_Connection)                                              mscl::InertialNode::setCommunicationMode(uint8 communicationMode);
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::enableDataStream(InertialTypes::InertialCategory category);
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::enableDataStream(InertialTypes::InertialCategory category, bool enable);
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::resetFilter();
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::getAutoInitialization();
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::setAutoInitialization();
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::setInitialAttitude(const EulerAngles& attitude);
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::setInitialHeading(float heading);
%catches(mscl::Error_Communication, mscl::Error_InertialCmdFailed, mscl::Error_Connection)                                              mscl::InertialNode::setToIdle();
%catches(mscl::Error_Communication, mscl::Error_InertialCmdFailed, mscl::Error_Connection)                                              mscl::InertialNode::resume();
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::getSensorToVehicleTransformation();
%catches(mscl::Error_InertialCmdFailed, mscl::Error_Communication, mscl::Error_NotSupported, mscl::Error_Connection)                    mscl::InertialNode::setSensorToVehicleTransformation(const EulerAngles& angles);


//Value
%catches(mscl::Error_BadDataType)                    mscl::Value::as_float() const;
%catches(mscl::Error_BadDataType)                    mscl::Value::as_double() const;
%catches(mscl::Error_BadDataType)                    mscl::Value::as_uint8() const;
%catches(mscl::Error_BadDataType)                    mscl::Value::as_uint16() const;
%catches(mscl::Error_BadDataType)                    mscl::Value::as_uint32() const;
%catches(mscl::Error_BadDataType)                    mscl::Value::as_int16() const;
%catches(mscl::Error_BadDataType)                    mscl::Value::as_int32() const;
%catches(mscl::Error_BadDataType)                    mscl::Value::as_bool() const;
%catches(mscl::Error_BadDataType)                    mscl::Value::as_string() const;

//DataPoint
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_float() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_double() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_uint8() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_uint16() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_uint32() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_int16() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_int32() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_bool() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_string() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_Vector() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_Matrix() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_Timestamp() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_Bytes() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_StructuralHealth() const;
%catches(mscl::Error_BadDataType)                    mscl::DataPoint::as_RfSweep() const;

//Vector / Matrix
%catches(std::out_of_range)                            mscl::Vector::as_floatAt(uint16 index) const;
%catches(std::out_of_range)                            mscl::Vector::as_uint16At(uint16 index)const;
%catches(std::out_of_range)                            mscl::Vector::as_uint8At(uint16 index)const;
%catches(std::out_of_range)                            mscl::Matrix::as_floatAt(uint16 row, uint16 column) const;
%catches(std::out_of_range)                            mscl::Matrix::as_uint16At(uint16 row, uint16 column) const;
%catches(std::out_of_range)                            mscl::Matrix::as_uint8At(uint16 row, uint16 column) const;

//SyncSamplingNetwork
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_InvalidNodeConfig, mscl::Error_Connection, mscl::Error_UnknownSampleRate, mscl::Error)    mscl::SyncSamplingNetwork::addNode(WirelessNode& node);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_InvalidNodeConfig, mscl::Error_Connection, mscl::Error_UnknownSampleRate, mscl::Error)    mscl::SyncSamplingNetwork::addNode(WirelessNode& node, const WirelessNodeConfig& pendingConfig);
%catches(mscl::Error_NodeCommunication, mscl::Error_Connection, mscl::Error)                                                                                            mscl::SyncSamplingNetwork::removeNode(uint16 nodeAddress);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection, mscl::Error_UnknownSampleRate)                                                mscl::SyncSamplingNetwork::lossless(bool enable);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection, mscl::Error_UnknownSampleRate)                                                mscl::SyncSamplingNetwork::highCapacity(bool enable);
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
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_Connection)                                mscl::DatalogDownloader::DatalogDownloader(const WirelessNode& node);
%catches(mscl::Error_NotSupported, mscl::Error_NodeCommunication, mscl::Error_NoData, mscl::Error_Connection)            mscl::DatalogDownloader::getNextData();

//SampleRate
%catches(mscl::Error_UnknownSampleRate)                                                        mscl::SampleRate::FromWirelessEepromValue(WirelessTypes::SampleRate eepromValue);

//SetToIdleStatus
%catches(mscl::Error_Connection)                                    mscl::SetToIdleStatus::cancel();

//FatigueOptions
%catches(mscl::Error_NoData)            mscl::FatigueOptions::snCurveSegment(uint8 segmentId) const;

//EventTriggerOptions
%catches(mscl::Error_NoData)            mscl::EventTriggerOptions::trigger(uint8 triggerIndex) const;

%catches(mscl::Error_NotSupported)      mscl::ChannelGroup::eepromLocation(WirelessTypes::ChannelGroupSetting setting) const;


//=========================================================================================================================================================