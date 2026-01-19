## Proiect_PMP: Macara arduino cu control din telefon

O macara cu doua motoare care se poate controla dintr-un site.

## Componente folosite:
- "sasiu" - bucati de pal de prin casa
- 2 motoare DC TT galbene
- 1 breadbord (optional)
- 1 punte H hw-095
- 1 arduino UNO
- 1 esp32 DEVKIT 
- jumpere

## Descriere proiect

Macaraua este la baza, 2 motoare DC. La un motor DC, daca inversam polaritatea (pui + la - si - la +) - directia de invartire se schimba. 
Puntea H are 4 intrari digitale (IN1,IN2,IN3,IN4) si 4 iesiri (OUT1,OUT2,OUT3,OUT4). Conectam iesirile la motoare - si intrarile la arduino. Astfel, putem controla directia motoarelor. 
Ex: Daca IN1-1 si IN2-0 => Motorul 1 se invarte. Daca IN1-0 si In2-1, motorul se invarte invers !

Mai departe, conectam arduino la esp32 prin pinul 10 (RX). De asemenea cele doua trebuie sa aiba ground comun (deci legam orice ground de la arduino la orice ground de pe esp32). 
Comunicarea e uni directionala (esp32 -> arduino) deoarece esp32 functioneaza pe 3.3v si arduino pe 5v. Daca vroiam comunicare bidirectionala, trebuia sa adaugam un divizor de tensiune, ca sa nu ardem esp-ul.

De pe esp32 hostam un website, de unde utilizatorii pot controla macaraua. Cand un buton de pe site este apasat, se trimite un semnal specific la arduino prin comunicare serial. Arduino citeste messajul si trimite semnalul appropriate la puntea H, care la randul ei controleaza motoarele. 

## Cod "de pe internet":
- Pentru control motoare am refolosit o parte din codul meu, facut la alt proiect de acum un an: https://github.com/Tuchila-Adi-Bogdan/utcn-Density_Based_Solid_Waste_Sorting_System
- Pentru partea de back-end la site m-am folosit in mare parte de laboratorul 9 PMP, si de aceasta librarie de cod: https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi/examples/WiFiAccessPoint
- Pentru partea de front-end la site m-am folosit (nu integral !) de inteligenta artificiala, deoarece nu stapanesc partea de front-end. 

Am folosit libraria SoftwareSerial.h pentru comunicarea serial, si WiFi.h, WiFiAP.h, WiFiClient.h

## Schema electrica:
