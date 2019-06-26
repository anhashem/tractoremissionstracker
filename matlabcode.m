
% Miguel Salas Work
clear
close all
clc

[filename directory_name] = uigetfile('*.txt', 'Select a file');
fullname = fullfile(directory_name, filename);
Data1 = load(fullname);

[filename2 directory_name2] = uigetfile('*.txt', 'Select a file');
fullname2 = fullfile(directory_name2, filename2);
Data2 = load(fullname2);


PPM = Data1(:,1);
Temp=Data2(:,1);
x=[1:size(PPM)];
x2=[1:size(Temp)];

figure(1);

plot(x,PPM,'b')
hold on 
yline(150,'-r','unhealthy');
xlabel('Time (s)','FontSize',14,'FontWeight','bold','Color','k')
ylabel('Particulate (PPM)','fontsize',14,'FontWeight','bold')
yyaxis right
plot(x2,Temp)
ylabel('Temeperature (Celsius) ','fontsize',14,'FontWeight','bold')
title('Test 1: The Lighter','fontsize',18)
hold off

legend({'PPM Level','Unhealthy limit','Temperature'},'FontWeight','bold')
PPMAvg=mean(PPM)
TempAvg=mean(Temp)

if PPMAvg>=0 && PPMAvg>=150
    type='Good';
elseif PPMAvg>=51 && PPMAvg>=100
    type='Moderate';
elseif PPMAvg>=101 && PPMAvg>=200
    type='Unhealthy' ;
elseif PPMAvg>=201 && PPMAvg>=300
    type='VeryUnhealthy';
elseif PPMAvg>=301 && PPMAvg>=500
    type='Hazardous';  
end

X= ['The emmission released by the tractor is ' type];
disp(X)
