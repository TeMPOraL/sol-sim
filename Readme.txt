Readme do projektu System: Sol V.1.0 Release, Copyleft 2004, TeMPOraL Software.
=================================

=================================
	Zawarto�� Pakietu

Pakiet zawiera program Sol wraz z pe�nym kodem �r�d�owym, kompilowalnym pod Visual C++ 6.0.
=================================

=================================
	U�ytkowanie

Do uruchomienia programu wymagane s�: akcelerator graficzny kompatybilny z OpenGL, oraz cierpliwo��,
jako �e program wczytuje ca�e 12 mb. tekstur.

Po uruchomieniu program wy�wietla model uk�adu s�onecznego. Rozmiary i nachylenie orbit s� zgodne z rzeczywistymi,
ale ich stosunek do rozmiar�w planet ju� nie. W drugim trybie, w��czanym klawiszem L, wy�wietlona jest jedna
z planet Uk�adu S�onecznego, wraz z jej opisem.

W programie zachowane s� takie elementy, jak nachylenie orbit, nachylenie r�wnika do tych�e, czy odleg�o�ci.
=================================

=================================
	Klawiszologia

[Globalne]
Alt + F4 - wyj�cie z programu

[Model Uk�adu S�onecznego]
Strza�ki w g�r� i w d� - zmiana k�ta nachylenia kamery do ekliptyki
Strza�ki w lewo i prawo - zmiana k�ta nachylenia do poziomej osi uk�adu (po prostu kamera obraca si� wok� S�o�ca
A i Z - Przybli�anie si� i oddalanie od S�o�ca
P - zapauzowanie Uk�adu - wszystko przestaje si� rusza�
L - prze��czenie w tryb informacji o planetach

[Informacje o planetach]
Strza�ki - podobnie jak w trybie Modelu, obr�t kamery wok� planety w pionie i w poziomie
A i Z - przybli�anie si� i oddalanie od planety
1 ... 9 - wyb�r wy�wietlanej planety, zgodnie z rosn�c� odleg�o�ci� od S�o�ca
S - powr�t do trybu Modelu Uk�adu S�onecznego
=================================

=================================
	Troch� o implementacji

Taa, wiem, to S�o�ce to tak �miesznie wygl�da; efekt tych dziwnych p�yw�w by� zamierzony, cho� nie
wyszed� tak, jak mia�. Ten p�yw to proste operacje na macierzy tekstur OpenGL.

W tym programie nie u�wiadczy si� �atwej zmiany wersji j�zykowej; wszystkie opisy planet s� "Hard Coded".
Spowodowane jest to dziwnym zjawiskiem - je�eli kt�ry� wpis w tablicy string�w robi� si� za d�ugi, to program
si� nie uruchamia�. Nie mam poj�cia, czym jest to spowodowane, ale jak ju� znajd�, to powstanie odpowiednia
nowa wersja programu.
=================================

=================================
	Credits

Fakt faktem, �e troch� nieswoich rzeczy w tym projekcie u�y�em.
Wi�c po pierwsze - biblioteka wy�wietlaj�ca tekst pochodzi z tomu pierwszego Pere�ek Programowania Gier,
(stworzona przez Dante Treglia II)
Po drugie - tablice tekstowe tworzone by�y (mam na my�li edytowanie plik�w) z u�yciem programu TblPad,
stworzonego przez ShadowFlare.
Po trzecie - wszystkie tekstury poza t�em i pier�cieniami Saturna pochodz� albo ze strony 3D Cafe (link
gdzie� na www.gamedev.net, albo od Jamesa Withington`a. Tekstura gwiazd pochodzi ze strony www.startrek.pl
(niestety ju� nie istnieje), a galaktyki na niej doklei�em w Paint`cie; pochodz� z gry SubSpace. Pier�cienie
Saturna namalowa�em sam.
=================================


=================================
	Kontakt

Mailto: temporal at poczta dot fm
www.temporal-software.prv.pl
=================================