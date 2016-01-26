# veslefrikk

Programmet er basert på en interrupt rutine som teller sekunder
og setter flagg når det skal samples eller sendes data.
Alt annet blir utført i main loop. 

veslefrikk_library:

sensor.h: Her kan innganger til de ulike sensorene settes. Inneholder også alle tidsintervaller for sampling og sending av data.

sensor.cpp: her kan spesifikk kode for lesing av sensorer skrives.

Setup.cpp: inneholder setup rutiner for timer og modem. pincode og ipaddresser settes her.

dsp.cpp: Her kan funksjoner for signalbehandling defineres.

Baatvaktbibliotek:

Inneholder kode skrevet av de som hadde sommerjobb og inneholder kode for å styre modemet. 
		

Ting som mangler:

-Ingen form for tidssynkronisering med server.
-Må prøve å komme frem til en slags oversikt over hvor ofte vi skal sample hva, hvor ofte vi skal utføre signalprossesering, hvor ofte vi skal sende +++.
-Robusthet når overføringer henger.
-Sensorkode.
-Grenseverdier for sms varsling.
-System for data i pakken som sendes.
-+++…

