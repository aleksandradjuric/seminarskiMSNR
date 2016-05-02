# Automatsko generisanje test primera Fuzz tehnikom
Projekat radjen na kursu Metodologija strucnog i naucnog rada. Ideja projekta je da prikaze nacine generisanja test primera Fuzz tehnikom. Test primeri se primenjuju na programe implementirane u C-u. Kao input je moguce zadati neke od osnovnih tipova podataka (int, float, char... ) i neke od karakteristicnih stringova koji se cesto unose (datum, putanja do nekog fajla, email adrese...). Ulaz mogu biti i nizovi koji imaju elemente tipa int, double ili float i alocirani su dinamicki ili staticki.

Tester je napravljen u QtCreator-u. Napisan je u programskom jeziku C++ uz upotrebu Qt biblioteka. Da bi se pokrenuo neophodno je da se folder Tests iskopira tamo gde se nalazi Makefile za tester. 

Folder Examples sadrzi neke jednostavne programe koji sluze za demonstraciju upotrebe ovog Fuzz testera.
