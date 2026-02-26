## Uppgift
Koppla in OUT-pinnen från en analog temperatursensor till en analog input pin på en arduino, VCC till 5V, och GND till jord. Skriv ut värdet från den analoga input pinnen. Klicka på temp-sensorn när programmet körs och flytta på slidern för att se värdet skifta.

## Labb - Analog temperatursensor
Använd dig av analogRead, millis, och uart från avr_analog_input-repot, samt rad 37 från main (som omvandlar input till celsius). Försök skriva resten av koden för main själv, inklusive att dela upp flyttalet till heltalsdel och decimaldel för utskrift.

Använd en analog temperatursensor för att mäta temperaturen. Anslut en temperatursensor, en blå LED, en grön LED, och en röd LED (alla med motstånd förstås) till en arduino. 

Skriv sedan ett program som läser av temperaturen från sensorn och skriver ut temperaturen till en seriell monitor. Samtidigt ska den blåa LEDn lysa om temperaturen är under 10 grader, den röda LEDn lysa om temperaturen är över 30 grader, och den gröna LEDn lysa om temperaturen ligger mittemellan.


## Wokwi

https://wokwi.com/projects/456961801070147585


## Branches

Detta repo innehåller flera grenar för de olika situationer vi kommer titta på


## make kommandon

* ```make``` - kompilerar programmet till bin-mappen, användbart om man vill ladda upp hex-filen till wokwi
* ```make isp``` - kompilerar programmet och flashar det till en inkopplad Arduino, förutsatt att man har kopplat in en Arduino till sin dator och satt rätt port (se kommentarer i Makefile)
* ```make clean``` - rensar genom att ta bort obj-mappen
* ```make fresh``` - rensar genom att ta bort alla obj-mappen samt bin-mappen
