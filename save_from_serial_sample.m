clear s
%freeports = serialportlist("available") % Shows available serial ports
%
%Choose which port to use for Arduino (proabably best to hardcode)
%
%ports = "/dev/ttyACM0";%freeports(2)

baudrate = 9600;

s = serialport("COM4",baudrate);

%initialize a timeout in case MATLAB cannot connect to the arduino
timeout = 0;
% main loop to read data from the Arduino, then display it%
while timeout < 100    %    % check if data was received    %    
    while s.NumBytesAvailable > 0
        %        
        % reset timeout        
        %        
        timeout = 0;        
        disp("Receive data");
        %        
        % data was received, convert it into array of integers        
        %        
        values = eval(strcat('[',readline(s),']'));        
        %        
        % if you want to store the integers in four variables        
        %        
        a = values(1);        
        b = values(2);        
        c = values(3);        
        d = values(4);        
        %        
        % print the results        
        %        
        disp(sprintf('a,b,c,d = %d,%d,%d,%d\n',[a,b,c,d]));    
    end
    pause(0.5);    
    timeout = timeout + 1
end