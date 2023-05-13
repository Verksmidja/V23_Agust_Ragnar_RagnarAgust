# verksmidja_lokaverk_laser_tag
laser-tag er með kóða fyrir IR Transmitter, OLED, RFID og IR reciever

lokaverkið er með viðtakara og sendir á net

lokaverk_net_1.py er netcodi


<h2>Verkefnalýsing</h2>

Við ákváðum að gera Lazer-Tag byssur með infared Transmitter/Reciever. Gerðar voru tvær byssur sem við 3d prentuðum fyrir fyrsta tímann. Á byssurnar tengdum við einn ESP32 og notuðum hleðslubanka sem orkugjafa. Á ESP32in tengdum við IR Reciever frá Keyestudio til að taka við signal þegar leikmaður er skotinn. Líf Leikmanna er svo hýst á vefsíðu með Raspberry pi, einnig tengdum við 3 LED perur til að sýna leikmanni hversu mörg líf hann ætti eftir. Á byssurnar tengdum við líka einn Arduino sem stjórnaði Infared Transmitter sem sendir signal til að skjóta andstæðing þegar ýtt er á takka. Arduinoinn notar 9V batterí sem orkugjafa og stjórnaði einnig OLED sem sýndi magn byssukúla sem þú átt eftir. Til að endurfylla byssuna tengdum við rfid við Arduinoinn þannig að þú getur haft hleðslustöð hvar sem er án kröfu um rafmagn.






<h2>vika 1</h2>

3d prentuðum lazer-tag byssur
![mind](https://user-images.githubusercontent.com/63102077/235329521-c8433173-eeb9-4f13-9ffa-13eac5214758.jpg)


gerðum OLED sem sýnir hversu mörg skot eru eftir og RFID til að endurhlaða byssurnar
![mind](https://user-images.githubusercontent.com/63102077/235330336-ba438d47-d745-4091-befb-068961b51f2d.jpg)
setum up sendara og viðtakara og netsendara
![mind](https://user-images.githubusercontent.com/63102077/235330340-b18242d6-cde4-4053-9676-e37b72d659a6.jpg)

<h2>vika 2</h2>
1 lazer-tag byssa nánast tilbúin nema þarf að tengja ESP32 við batterí 

![mind](https://user-images.githubusercontent.com/63102077/236629069-d13901eb-bc03-47a6-975d-a007f177931a.jpg)



<h2>vika 3</h2>
Byssurnar tilbúnar


![mind](https://github-production-user-asset-6210df.s3.amazonaws.com/63102077/238032265-aa68c90f-3246-4edb-bfa5-1d1023860ebb.jpg)





Hönnunar vandamál

Við lentum í vandamálum við að tengja batterí við ESP32, flest allar ESP32 útgáfur höfðu vin pinna til að tengja batterí en ekki okkar, við þurftum að nota rafbanka sem orkugjafa.

Svo lentum við í vandamálum með að Infared Transmitterinn senti signal sem hélt áfram að skoppa af borðum/gólfum og skjóta sig sjálfann.

Svo lentum við í vandamálum með það þegar við vorum að hýsa lífin á vefsíðu vegna þess að víst það má ekki breyta einhverju fyrir utan def með def, við löguðum þetta með global variable.

Annað vandamál sem við lentum í var þegar við ætluðum að nota laser transmitter en laserinn var ekki nógu sterkur og recieverinn átti erfitt með að fá skynjun, áváðum að skipta yfir í IR Transmitter


<h2>Heimildir:</h2>

Við notuðum aðallega gamla kóða sem við notuðum í verkefnum áfangans og sameinuðum þá

https://www.thegeekpub.com/wiki/sensor-wiki-ky-005-infrared-ir-transmitter/

https://www.thingiverse.com/thing:4207521

https://www.keyestudio.com/products/free-shipping-keyestudio-digital-ir-infrared-transmitter-transmit-module-for-arduino


https://user-images.githubusercontent.com/63102077/238042465-c2b0df4c-e7b6-40fe-a491-3c5dc8f46c96.png

https://wiki.keyestudio.com/Ks0027_keyestudio_Digital_IR_Transmitter_Module

<h2>kerfisskýringarmynd</h2>

![mind](https://user-images.githubusercontent.com/63102077/238042465-c2b0df4c-e7b6-40fe-a491-3c5dc8f46c96.png)



<h1>video</h1>



https://youtube.com/shorts/ZI9RjLVNbVE

https://youtube.com/shorts/TegnResYUGM

<h2>Efnislisti</h2>

•    2 Arduino
•    Raspberry pi
•    2 ESP32
•    2 RFID-RC522
•    2 Keyestudio Infared Transmitter
•    2 Keyestudio Infared Reciever
•    2 Lazer-Tag byssur
•    2 9V batterí
•    2 Hleðslubankar
•    2 Takkar
•    2 On/Off Takkar
•    4 Mini brauðbretti
•    Vírar
•    6 LED perur 




