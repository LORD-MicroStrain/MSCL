namespace mscl
{

    public class Error : System.ApplicationException
    {
        public Error(string message)
            : base(message)
        {
        }
    }

    public class Error_NotSupported : Error
    {
        public Error_NotSupported(string message)
            : base(message)
        {
        }
    }

    public class Error_NoData : Error
    {
        public Error_NoData(string message)
            : base(message)
        {
        }
    }

    public class Error_BadDataType : Error
    {
        public Error_BadDataType(string message)
            : base(message)
        {
        }
    }

    public class Error_UnknownSampleRate : Error
    {
        public Error_UnknownSampleRate(string message)
            : base(message)
        {
        }
    }

    public class Error_Timeout : Error
    {
        public Error_Timeout(string message)
            : base(message)
        {
        }
    }

    public class Error_Communication : Error
    {
        public Error_Communication(string message)
            : base(message)
        {
        }
    }

    public class Error_NodeCommunication : Error_Communication
    {
        public Error_NodeCommunication(string message, ushort nodeAddress)
            : base(message)
        {
            m_nodeAddress = nodeAddress;
        }

        public ushort nodeAddress()
        {
            return m_nodeAddress;
        }

        private ushort m_nodeAddress;
    }

    public class Error_Connection : Error
    {
        public Error_Connection(string message, int code)
            : base(message)
        {
            m_code = code;
        }

        public int code()
        {
            return m_code;
        }

        private int m_code;
    }

    public class Error_InvalidSerialPort : Error_Connection
    {
        public Error_InvalidSerialPort(string message, int code)
            : base(message, code)
        {
        }
    }

    public class Error_InvalidTcpServer : Error_Connection
    {
        public Error_InvalidTcpServer(string message, int code)
            : base(message, code)
        {
        }
    }

    public class Error_InvalidUnixSocket : Error_Connection
    {
        public Error_InvalidUnixSocket(string message, int code)
            : base(message, code)
        {
        }
    }

    public class Error_InertialCmdFailed : Error
    {
        public Error_InertialCmdFailed(string message, int code)
            : base(message)
        {
            m_code = code;
        }

        public int code()
        {
            return m_code;
        }

        private int m_code;
    }

    public class Error_InvalidConfig : Error
    {
        public Error_InvalidConfig(string message)
            : base(message)
        {
            m_issues = new ConfigIssues();
        }

        public Error_InvalidConfig(string message, ConfigIssues issues)
            : base(message)
        {
            m_issues = issues;
        }

        public ConfigIssues issues()
        {
            return m_issues;
        }

        private ConfigIssues m_issues;
    }

    public class Error_InvalidNodeConfig : Error_InvalidConfig
    {
        public Error_InvalidNodeConfig(string message, ushort nodeAddress)
            : base(message)
        {
            m_nodeAddress = nodeAddress;
        }

        public Error_InvalidNodeConfig(string message, ConfigIssues issues, ushort nodeAddress)
            : base(message, issues)
        {
            m_nodeAddress = nodeAddress;
        }

        public ushort nodeAddress()
        {
            return m_nodeAddress;
        }

        private ushort m_nodeAddress;
    }
}