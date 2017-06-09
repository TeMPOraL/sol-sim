Readme do projektu System: Sol V.1.0 Release, Copyleft 2004, TeMPOraL Software.
=================================

=================================
	Zawartoœæ Pakietu

Pakiet zawiera program Sol wraz z pe³nym kodem Ÿród³owym, kompilowalnym pod Visual C++ 6.0.
=================================

=================================
	U¿ytkowanie

Do uruchomienia programu wymagane s¹: akcelerator graficzny kompatybilny z OpenGL, oraz cierpliwoœæ,
jako ¿e program wczytuje ca³e 12 mb. tekstur.

Po uruchomieniu program wyœwietla model uk³adu s³onecznego. Rozmiary i nachylenie orbit s¹ zgodne z rzeczywistymi,
ale ich stosunek do rozmiarów planet ju¿ nie. W drugim trybie, w³¹czanym klawiszem L, wyœwietlona jest jedna
z planet Uk³adu S³onecznego, wraz z jej opisem.

W programie zachowane s¹ takie elementy, jak nachylenie orbit, nachylenie równika do tych¿e, czy odleg³oœci.
=================================

=================================
	Klawiszologia

[Globalne]
Alt + F4 - wyjœcie z programu

[Model Uk³adu S³onecznego]
Strza³ki w górê i w dó³ - zmiana k¹ta nachylenia kamery do ekliptyki
Strza³ki w lewo i prawo - zmiana k¹ta nachylenia do poziomej osi uk³adu (po prostu kamera obraca siê wokó³ S³oñca
A i Z - Przybli¿anie siê i oddalanie od S³oñca
P - zapauzowanie Uk³adu - wszystko przestaje siê ruszaæ
L - prze³¹czenie w tryb informacji o planetach

[Informacje o planetach]
Strza³ki - podobnie jak w trybie Modelu, obrót kamery wokó³ planety w pionie i w poziomie
A i Z - przybli¿anie siê i oddalanie od planety
1 ... 9 - wybór wyœwietlanej planety, zgodnie z rosn¹c¹ odleg³oœci¹ od S³oñca
S - powrót do trybu Modelu Uk³adu S³onecznego
=================================

=================================
	Trochê o implementacji

Taa, wiem, to S³oñce to tak œmiesznie wygl¹da; efekt tych dziwnych p³ywów by³ zamierzony, choæ nie
wyszed³ tak, jak mia³. Ten p³yw to proste operacje na macierzy tekstur OpenGL.

W tym programie nie uœwiadczy siê ³atwej zmiany wersji jêzykowej; wszystkie opisy planet s¹ "Hard Coded".
Spowodowane jest to dziwnym zjawiskiem - je¿eli któryœ wpis w tablicy stringów robi³ siê za d³ugi, to program
siê nie uruchamia³. Nie mam pojêcia, czym jest to spowodowane, ale jak ju¿ znajdê, to powstanie odpowiednia
nowa wersja programu.
=================================

=================================
	Credits

Fakt faktem, ¿e trochê nieswoich rzeczy w tym projekcie u¿y³em.
Wiêc po pierwsze - biblioteka wyœwietlaj¹ca tekst pochodzi z tomu pierwszego Pere³ek Programowania Gier,
(stworzona przez Dante Treglia II)
Po drugie - tablice tekstowe tworzone by³y (mam na myœli edytowanie plików) z u¿yciem programu TblPad,
stworzonego przez ShadowFlare.
Po trzecie - wszystkie tekstury poza t³em i pierœcieniami Saturna pochodz¹ albo ze strony 3D Cafe (link
gdzieœ na www.gamedev.net, albo od Jamesa Withington`a. Tekstura gwiazd pochodzi ze strony www.startrek.pl
(niestety ju¿ nie istnieje), a galaktyki na niej doklei³em w Paint`cie; pochodz¹ z gry SubSpace. Pierœcienie
Saturna namalowa³em sam.
=================================


=================================
	Kontakt

Mailto: temporal at poczta dot fm
www.temporal-software.prv.pl
=================================