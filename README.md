# smart_home_modell
Smart Home modell

Igazából még soha nem írtam fejlesztői dokumentációt, de megpróbálok valamit kihozni belőle. Egyedül dolgoztam a projekten és az ötlet onnan jött, hogy manapság minden az IoT (Dolgok Internete) körül forog, akkor próbálkozzunk meg egy lakásnak az „okosításával”. Ehhez az Arduino rendszerét választottam, amit egy c/c++ klónon (fejlesztői IDE) keresztül lehetett programozni. Ez okozott néha kellemetlenséget, mert nem „tiszta” fejlesztői környezetként a c++-ban megismert eszközök nem mindig és nem olyan módon működnek, mint ahogyan egy PC fejlesztői környezetében. A másik sok fejtörést okozó dolgok voltak a működésbe bevont header fájlok sokszor hiányos leírása-forráskódja, aminek tesztelése (vagy működésükről információ felkutatása) rendkívül időrabló tudott lenni. Bár a feladatot nem sikerült maradéktalanul olyan szinten befejezni, ahogy szerettem volna, de majd vizsgaidőszak végeztével még biztosan folytatni fogom az ötlet megvalósítását és még további fejlesztését. Erről később majd bővebben is írnék majd. 
A projekthez vásárolt eddigi eszközök, szenzorok:

•	Arduino Mega 2560

 ![alt test](pictures/Mega2560.png)

•	Arduino KP-4X3/MEM tasztatúra billentyűzet

 ![alt test](pictures/tastat.png)

•	Szalagkábelek
•	Arduino KC-1602-BB LCD kék-fehér kijelző

 ![alt test](pictures/LCD.png)

•	Arduino LCD-I2C-IF interfész adapter az LCD kijelzőhöz

 ![alt test](pictures/I2C.png)

•	Arduino MS/SG90 micro servo

 ![alt test](pictures/servo.png)

•	Különféle méretű és színű led lámpák (egyszerű programozásuk miatt csak később kerülnek majd beépítésre)
•	HanRun HR911105A W5500 típusú SPI ethernet modull

 ![alt test](pictures/W5500.png)


•	Arduino DHT11-M hőmérséklet és páratartalom érzékelő

 ![alt test](pictures/DHT11.png)

•	Arduino GY-30 környezeti fényérzékelő

 ![alt test](pictures/GY30_fény.png)

•	Arduino D096-12864-SPI6 OLED kijelző

 ![at test](pictures/OLED.png)

•	PIR mozgásérzékelő szenzor
•	Breadboard
•	Kapcsoló + tápegység külön a breadboardhoz
•	Mágneses nyitásérzékelő szenzor
•	Ellenállások a led lámpákhoz

Tervezett még a projekthez vásárolni:
•	Arduino MHC-05/4 bluetooth modul

![alt test](pictures/bluetooth.png) 

•	Arduino MICROSD-M microsd kártya kezelő modul
•	Illetve ide kapcsolódik még, hogy összekapcsolni az itthon QNAP szerverrel (kipróbálásra került és sikeres volt, de mivel még van mit rajt csiszolni nem került bele a vizsgaanyagba)
A fenti felsorolásból a vizsgaanyagba beépítésre kerültek, aminek a működése „majdnem” tökéletes:
	Arduino Mega 2560
	Arduino KP-4X3/MEM tasztatúra billentyűzet
	Szalagkábelek
	Arduino KC-1602-BB LCD kék-fehér kijelző
	Arduino LCD-I2C-IF interfész adapter az LCD kijelzőhöz
	Arduino MS/SG90 micro servo
	Arduino DHT11-M hőmérséklet és páratartalom érzékelő
	Arduino D096-12864-SPI6 OLED kijelző
	Breadboard
	Kapcsoló + tápegység külön a breadboardhoz
	Illetve felhasználásra került a belső EEPROM , mint adatbázis tárolási helye, mely a jövőben átkerül majd SD kártyára, illetve majd a NAS-ra (is)– bár  az EEPROM is közel  100000 írási ciklust ki kellne, hogy bírjon a leírások alapján

A projekt első részében bár nem kerültek „commitba”, de olyan feladatok kerültek elvégzésre, mint a szenzorok tesztelése („serial”-ra „) íratása. A következő lépésben forrasztópáka beszerzése után az I2C beforrasztása volt az LCD kijelző kivezetéseire. Ezt azért gondoltam szükségesnek, mert így kevesebb „port”-ra van szükség a kommunikáció megvalósítására. A mega2560-on (a feszültség és a földelés mellett) az adatcsere az I2C buszon keresztül – természetesen megcímezve – a 20-as SDA és a 21-es SCL portokon valósult meg. 

A kommunikációhoz szükséges cím megszerzése egy segédprogrammal valósult meg, amelyet szintén a rövidsége miatt nem részletezném. 
Külön segédprogrammal volt tesztelve a szervo motor működése, amelyet egy reteszzárt tud modellezni. Tengelyállástól (0-180) függően bezár – eltolva a reteszeket – vagy kinyit. 

A következő lépést a tasztatúra felprogramozása és tesztelése – LCD-re való kiíratása volt. 
Eredetileg nem a 22-28 –as „pin”-en működött, csak később került áthelyezésre, hogy más szenzoroknak és esetleges vezérléseknek több hely legyen. 

A koncepció az volt ebben az első részben, hogy a program a tasztatúráról bekér néhány számot – mint egy jelszót – megvizsgálja, hogy a megadott szám megegyezik-e a programban eltárolt számmal. Ha egyezés van, akkor képernyőre írja, hogy „correct” és a tengely állásától függően mozgatja a szervónak a motorját és tájékoztatást ír az LCD-re, hogy a reteszzár állapotáról. Ha nem egyezik, akkor újraindul a ciklus.

Mindezek a dolgok szerepelnek az első commit-ban (fájlnév: tastat_v2_2.ino) 
Hátránya ennek a résznek, hogy a beforrasztott I2C busz-on található kontrasztot állító potméter rendkívül szűk tartományban képes működni. 






