# ORM-2

Projekat iz predmeta ORM-2 radjen skolske 2020./2021.

Potrebno je pokrenuti kontroler na jednom raspberry pi uredjaju, koji ima na sebi WiFi adapter koji je pokrenut u rezimu pristupne tacke. Zatim je moguce pokrenuti uredjaje (senzore i aktuatore) na
drugom raspberry pi uredjaju ili na desktop masini. Oglasavanje mreze se odvija putem SSDP protokola (po uzoru na SSDP), a razmena poruka se odvija putem MQTT protokola, gde 
se uredjaji subskrajbuju na odgovarajuce teme, a takodje mogu i da vrse objave poruka na odredjene teme. Kontroler predstavlja spregu izmedju svih uredjaja u mrezi. 

Ukoliko pokrenete raspberry pi sa wifi adapterom u rezimu pristupne tacke, napravili ste lokalnu mrezu, samim tim vam prikljucivanje na internet mrezu putem ethernet kabla ili na 
drugi nacin nije potrebno. Ovakvom realizacijom je pokazano kako je moguce ostvariti lokalnu mrezu izmedju uredjaja, bez ovisnosti od nekog internet provajdera.

Ovaj projekat je moguce spregnuti sa projektom koji se radi na predmetu PNRS-1, cime se dobija kompletan sistem u kome mozete pomocu android aplikacije vrsiti kontrolu uredjaja
koji se nalaze na mrezi. Naravno, sve se odvija preko centralnog kontrolera, i sama aplikacija, odnosno korisnik ne moze da vidi direktno neki od uredjaja, takodje uredjaji se ne 
vide medjusobno, vec poruke razmenjuju samo putem kontrolera. 
