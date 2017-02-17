1.Ongelma on ratkaistu käyttäen hashtaulukoita. 

Jokaiseen fraasiin liittyvät fraasit talletetaan hashtauluun arvona.
Jokaisen fraasin esiintymä määrä tallennetaan myös erilliseen hashtauluun arvona.


Jotta järjestämiseen ei kulu liikaa aikaa luodaan tilapäinen tiedosto johon valitaan noin 100 eniten esiintynyttä fraasia esiintymiskertojen perusteella. Lopuksi tulostetaan top 100 fraasia järjestyksessä tiedostoon esiintymismäärän kera.


2.
Mittaukset

Nimi        Rivejä   Aika(s)    rivejä/s
---------------------------------------
small.txt    32k     0.5 	64k
medium.txt  146k     3.5 	42k
big.txt     1.7M     100.0	17k

Algoritmin suoritusaika kasvaa lineaarisesti suhteessa syötteen kokoon.
Eniten aikaa kuluu syötetiedoston rivien läpikäyntiin organize metodissa.








