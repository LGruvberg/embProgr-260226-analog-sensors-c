## Uppgift

Koppla in wipern på en potentiometer till en analog input pin på en arduino, ena terminalen till 5V, och andra terminalen till jord.
Skriv ut värdet från den analoga input pinnen och vrid på potentiometern för att se det skifta.

## Wokwi
https://wokwi.com/projects/456958487475223553

## Branches
Detta repo innehåller en branch för varje labbuppgift

## make kommandon

* ```make``` - kompilerar programmet till bin-mappen, användbart om man vill ladda upp hex-filen till wokwi
* ```make isp``` - kompilerar programmet och flashar det till en inkopplad Arduino, förutsatt att man har kopplat in en Arduino till sin dator och satt rätt port (se kommentarer i Makefile)
* ```make clean``` - rensar genom att ta bort obj-mappen
* ```make fresh``` - rensar genom att ta bort alla obj-mappen samt bin-mappen
