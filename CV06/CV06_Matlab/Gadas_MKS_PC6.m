


clear
close all

ntc = csvread('ntc.csv');
t = ntc(:,1);
ad = ntc(:,2);
ad = 1024.*(ad./(ad+10));

p = polyfit(ad, t, 10);
ad2 = 0:1023;
t2 = round(polyval(p, ad2), 1);

figure(1)
plot(ad, t,'bo');
hold on
plot(ad2, t2, 'r')

dlmwrite('data.dlm', t2*10, ',');


