%Inisialisasi Serial dan Grafik
serialPort = 'COM4';
judulGrafik = 'Grafik Sensor';
xLabel = 'Waktu (detik)';
yLabel = 'Data';
plotGrid = 'on';
min = 0;
max = 100;
lebarScroll = 10;
delay = 0.01;

%Inisialisasi variabel
waktu = 0;
data = 0;
cacah = 0;

%Persiapkan Grafik
plotGraph = plot(waktu, data,'-b*','LineWidth',1.5,'MarkerEdgeColor','r','MarkerFaceColor','r');
title(judulGrafik,'FontSize',15);
xlabel (xLabel,'FontSize',12);
ylabel (yLabel,'FontSize',12);
axis([0 10 min max]);
grid(plotGrid);
s = serial (serialPort,'BaudRate', 115200);
fopen(s)
%fprintf(s,'%s', char(1));
tic
while ishandle (plotGraph)
    nilaiInput = fscanf(s,'%f');
    if(~isempty(nilaiInput) && isfloat(nilaiInput));
        cacah = cacah + 1;
        waktu(cacah) = toc;
        data(cacah) = nilaiInput(1);
        
        if(lebarScroll > 0)
            set(plotGraph,'XData',waktu(waktu > waktu(cacah)-lebarScroll),'YData',data(waktu > waktu(cacah)-lebarScroll));
            axis([waktu(cacah)-lebarScroll waktu(cacah) min max]);
        else
            set(plotGraph,'XData', waktu, 'YData',data);
            axis([0 waktu(cacah) min max]);
        end
    end
end

