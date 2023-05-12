# verksmidja_lokaverk_laser_tag
laser_tag er með kóða fyrir sendara, led skjá, skot tejara og skinjara

lokaverkið er með viðtakara og sendir á net

lokaverk_net_1.py er netcodi


<h2>Verkefnalýsing</h2>

Við ákváðum að gera Lazer-Tag byssur með infared Transmitter/Reciever. Gerðar voru tvær byssur sem við 3d prentuðum fyrir fyrsta tímann. Á byssurnar tengdum við einn ESP32 og notuðum hleðslubanka sem orkugjafa. Á ESP32in tengdum við IR Reciever frá Keyestudio til að taka við signal þegar leikmaður er skotinn. Líf Leikmanna er svo hýst á vefsíðu með Raspberry pi, einnig tengdum við 3 LED perur til að sýna leikmanni hversu mörg líf hann ætti eftir. Á byssurnar tengdum við líka einn Arduino sem stjórnaði Infared Transmitter sem sendir signal til að skjóta andstæðing þegar ýtt er á takka. Arduinoinn notar 9V batterí sem orkugjafa og stjórnaði einnig OLED sem sýndi magn byssukúla sem þú átt eftir. Til að endurfylla byssuna tengdum við rfid við Arduinoinn þannig að þú getur haft hleðslustöð hvar sem er án kröfu um rafmagn.






<h2>vika 1</h2>

3d prentuðum lazertag byssa
![mind](https://user-images.githubusercontent.com/63102077/235329521-c8433173-eeb9-4f13-9ffa-13eac5214758.jpg)


gerðum skana og skoteljara
![mind](https://user-images.githubusercontent.com/63102077/235330336-ba438d47-d745-4091-befb-068961b51f2d.jpg)
setum up sendara og viðtakara og netsendara
![mind](https://user-images.githubusercontent.com/63102077/235330340-b18242d6-cde4-4053-9676-e37b72d659a6.jpg)

<h2>vika 2</h2>
1 lazertag bisa tilbúin nema að teingja esp32 við baterí 

![mind](https://user-images.githubusercontent.com/63102077/236629069-d13901eb-bc03-47a6-975d-a007f177931a.jpg)



<h2>vika 3</h2>
byssa tilbúin


![mind](https://github-production-user-asset-6210df.s3.amazonaws.com/63102077/238032265-aa68c90f-3246-4edb-bfa5-1d1023860ebb.jpg)





Hönnunar vandamál

Við lentum í vandamálum við að tengja batterí við ESP32, flest allar ESP32 útgáfur höfðu vin pinna til að tengja batterí en ekki okkar, við þurftum að nota rafbanka sem orkugjafa.

Svo lentum við í vandamálum með að Infared Transmitterinn senti signal sem hélt áfram að skoppa af borðum/gólfum og skjóta sig sjálfann.

Svo lentum við í vandamálum með það þegar við vorum að hýsa lífin á vefsíðu vegna þess að víst það má ekki breyta einhverju fyrir utan def með def, við löguðum þetta með global variable.
