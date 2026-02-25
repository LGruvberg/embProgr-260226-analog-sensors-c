## Uppgift

Koppla in OUT-pinnen från en analog temperatursensor till en analog input pin på en arduino, VCC till 5V, och GND till jord. Skriv ut värdet från den analoga input pinnen. Klicka på temp-sensorn när programmet körs och flytta på slidern för att se värdet skifta.

## Wokwi

https://wokwi.com/projects/456961801070147585


## Branches

Detta repo innehåller flera grenar för de olika situationer vi kommer titta på


## make kommandon

* ```make``` - kompilerar programmet till bin-mappen, användbart om man vill ladda upp hex-filen till wokwi
* ```make isp``` - kompilerar programmet och flashar det till en inkopplad Arduino, förutsatt att man har kopplat in en Arduino till sin dator och satt rätt port (se kommentarer i Makefile)
* ```make clean``` - rensar genom att ta bort obj-mappen
* ```make fresh``` - rensar genom att ta bort alla obj-mappen samt bin-mappen
