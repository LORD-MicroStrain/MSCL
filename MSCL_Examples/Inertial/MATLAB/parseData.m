function parseData_2016_01_19()

% MSCL Example: ParseData
%    This example shows how to parse incoming data from an Inertial Device.
%    This example does not start a Node sampling. To receive data, a Node
%    must be put into a sampling mode.


% import MSCL .NET library (make sure path is correct for your system)
msclInfo = NET.addAssembly('C:\Program Files\MATLAB\MSCL\MSCL_Managed.dll');


%TODO: change these constants to match your setup

COM_PORT = 'COM3';

try
    % create a Serial Connection with the specified COM Port, default baud rate of 921600
    connection = mscl.Connection.Serial(COM_PORT);
    
    % create an instance of MATLAB onCleanup class to gracefully disconnect from COM port when
    % this object is cleared, for instance if matlab encounters an error
    % before the connection is closed.
    cleanupConnection = onCleanup(@()connection.disconnect);
    
    % create an InertialNode with the connection
    node = mscl.InertialNode(connection);
    
    while true
        try
            % get all the data packets from the node, with a timeout of 500 milliseconds
            packets = node.getDataPackets(500);
            
            % iterate over all the data packets received
            for j = 1:packets.Count(),
            
              packet = packets.Item(j-1);
              % print out the data
              display('Packet received: ');
              
              % iterate over all the data points in the packet
              for i = 1:packet.data().Count(),
                  dataPoint = packet.data().Item(i-1);
                  display(['dataPoint: ',num2str(dataPoint.as_float)]) % display dataPoint value as string
              end
              
              %if the dataPoint is invalid
              if dataPoint.valid() == false,
                  display('Invalid data point')
              end
              
            end
            
        catch err
            display(err.message)
            clearvars cleanupConnnection % performs cleanup on connection
            break                        % exits while loop upon error
        end
    end
    
catch err
    display(err.message)
    clearvars cleanupConnnection % performs cleanup on connection
end

end


