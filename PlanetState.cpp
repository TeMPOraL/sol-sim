/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 05.06.2004
Last Revised:	05.06.2004

This is an Implementation File:

Notes:
	
*/

/*

*/

#include "AppState.h"
#include "SolarSystem.h"
#include "StringTable.h"
#include "PlanetState.h"

#include "Strings_stat_txt.h"

#include "GPG//TEXT.h"

namespace Sol
{

	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 05.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CPlanetState::CPlanetState()
	{
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 05.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CPlanetState::~CPlanetState()
	{

	}

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 05.06.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes App State
	//=============================================
	bool CPlanetState::Init()
	{
		log <<"CPlanetState::Init() - Initializing Planet App State\n";

		cameraRotationX = 0.0f;
		cameraRotationY = 0.0f;
		cameraDistance = -25.0f;

		COLOR textColor = {0x11, 0xFF, 0x11, 0xFF};
		descriptionText = new TextBox(640/2, 630, 0, 470);
		descriptionText->SetMode(TEXT_DRAW_SPACES | TEXT_WRAP_SPACES);
		descriptionText->SetColor(textColor);

		planet = NULL;
		moon = NULL;

		stat_txt.Init("stat_txt.tbl");

		starfieldHandle = CApplication::GetSingleton().textureManager.LoadTexture("tex\\starfield.bmp");

		//the idea is simple - pressing a key 1 to 0 in solar mode will deinitialize it
		//and initialize planet mode, but leave key pressed, so that now we can choose
		//whitch planet will be created

		if(CApplication::GetSingleton().window.keys['1'])
		{
			SetPlanet(PLID_MERCURY);
			CApplication::GetSingleton().window.keys['1'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['2'])
		{
			SetPlanet(PLID_VENUS);
			CApplication::GetSingleton().window.keys['2'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['3'])
		{
			SetPlanet(PLID_EARTH);
			CApplication::GetSingleton().window.keys['3'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['4'])
		{
			SetPlanet(PLID_MARS);
			CApplication::GetSingleton().window.keys['4'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['5'])
		{
			SetPlanet(PLID_JUPITER);
			CApplication::GetSingleton().window.keys['5'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['6'])
		{
			SetPlanet(PLID_SATURN);
			CApplication::GetSingleton().window.keys['6'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['7'])
		{
			SetPlanet(PLID_URANUS);
			CApplication::GetSingleton().window.keys['7'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['8'])
		{
			SetPlanet(PLID_NEPTUNE);
			CApplication::GetSingleton().window.keys['8'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['9'])
		{
			SetPlanet(PLID_PLUTO);
			CApplication::GetSingleton().window.keys['9'] = false;
		}

	//	else if(CApplication::GetSingleton().window.keys['0'])
	//	{
		//	SetPlanet(PLID_MOON);
	//	CApplication::GetSingleton().window.keys['0'] = false;
		//}

		else	//none of those keys are pressed??
		{
			SetPlanet(PLID_EARTH);
		}

		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 05.06.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes App State
	//=============================================
	bool CPlanetState::DeInit()
	{
		log <<"CPlanetState::DeInit() - Deinitializing Planet App State\n";

		delete descriptionText;
		if(planet)	//if planet exists
		{
			planet->DeInit();	//deinitialize planet
			delete planet;	//delete planet from memory
			planet = NULL;	//secure the pointer
		}
		if(moon)	//if planet exists
		{
			moon->DeInit();	//deinitialize planet
			delete moon;	//delete planet from memory
			moon = NULL;	//secure the pointer
		}

		stat_txt.DeInit();

		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 05.06.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//
	//=============================================
	void CPlanetState::Update(float dT)
	{
		if(CApplication::GetSingleton().window.keys['1'])
		{
			SetPlanet(PLID_MERCURY);
			CApplication::GetSingleton().window.keys['1'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['2'])
		{
			SetPlanet(PLID_VENUS);
			CApplication::GetSingleton().window.keys['2'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['3'])
		{
			SetPlanet(PLID_EARTH);
			CApplication::GetSingleton().window.keys['3'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['4'])
		{
			SetPlanet(PLID_MARS);
			CApplication::GetSingleton().window.keys['4'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['5'])
		{
			SetPlanet(PLID_JUPITER);
			CApplication::GetSingleton().window.keys['5'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['6'])
		{
			SetPlanet(PLID_SATURN);
			CApplication::GetSingleton().window.keys['6'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['7'])
		{
			SetPlanet(PLID_URANUS);
			CApplication::GetSingleton().window.keys['7'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['8'])
		{
			SetPlanet(PLID_NEPTUNE);
			CApplication::GetSingleton().window.keys['8'] = false;
		}

		else if(CApplication::GetSingleton().window.keys['9'])
		{
			SetPlanet(PLID_PLUTO);
			CApplication::GetSingleton().window.keys['9'] = false;
		}

		//else if(CApplication::GetSingleton().window.keys['0'])
		//{
		//	SetPlanet(PLID_MOON);
		//	CApplication::GetSingleton().window.keys['0'] = false;
		//}

		if(CApplication::GetSingleton().window.keys['S'])
		{
			CApplication::GetSingleton().appManager.SetState(AS_SOLARSYSTEM);
			CApplication::GetSingleton().window.keys['S'] = false;
		}


		//move closer and further to the planet
		if(CApplication::GetSingleton().window.keys['A'] == true)
		{
			cameraDistance += CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
		}

		if(CApplication::GetSingleton().window.keys['Z'] == true)
		{
			cameraDistance -= CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
		}

		//rotate vertically around the planet
		if(CApplication::GetSingleton().window.keys[VK_UP] == true)
		{
			cameraRotationX += CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
			if(cameraRotationX >= 360)
			{
				cameraRotationX -= 360;
			}
		}

		if(CApplication::GetSingleton().window.keys[VK_DOWN] == true)
		{
			cameraRotationX -= CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
			if(cameraRotationX <= 0)
			{
				cameraRotationX += 360;
			}
		}

		//rotate horizontally around the planet
		if(CApplication::GetSingleton().window.keys[VK_LEFT] == true)
		{
			cameraRotationY += CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
			if(cameraRotationY >= 360)
			{
				cameraRotationY -= 360;
			}
		}

		if(CApplication::GetSingleton().window.keys[VK_RIGHT] == true)
		{
			cameraRotationY -= CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
			if(cameraRotationY <= 0)
			{
				cameraRotationY += 360;
			}
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear the screen and the depth buffer
		glLoadIdentity();

		CApplication::GetSingleton().textureManager.BindTexture(starfieldHandle);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f,0.0f); glVertex3f(-400.0f,-400.0f,-900.0f);
			glTexCoord2f(1.0f,0.0f); glVertex3f(400.0f,-400.0f,-900.0f);
			glTexCoord2f(1.0f,1.0f); glVertex3f(400.0f,400.0f,-900.0f);
			glTexCoord2f(0.0f,1.0f); glVertex3f(-400.0f,400.0f,-900.0f);

		}
		glEnd();

		glTranslatef(0.0f,0.0f,cameraDistance);		//translate to camera position

		glRotatef(cameraRotationX, 1.0f ,0.0f, 0.0f);
		glRotatef(cameraRotationY, 0.0f ,1.0f, 0.0f);

		//we assume that planet pointer is valid; it`s difficult for it to be not
		planet->Update(dT);
		if(moon)
		{
			moon->Update(dT);
		}

		planet->Draw();
		if(moon)
		{
			moon->Draw();
		}

		descriptionText->Draw();
	}


	//=============================================
	//Function: SetPlanet()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 05.06.2004
	//
	//Returns: nothing
	//Parameters: new planet`s ID
	//Description:
	//
	//=============================================
	void CPlanetState::SetPlanet(int planetID)
	{
		log <<"CPlanetState::SetPlanet() - creating planet ID: " << planetID <<"\n";
		if(shownPlanet == planetID)	//requested planet is already shown
		{
			return;
		}

		shownPlanet = planetID;

		if(planet)	//if planet exists
		{
			planet->DeInit();	//deinitialize planet
			delete planet;	//delete planet from memory
			planet = NULL;	//secure the pointer
		}
		if(moon)	//if planet exists
		{
			moon->DeInit();	//deinitialize planet
			delete moon;	//delete planet from memory
			moon = NULL;	//secure the pointer
		}

		switch(planetID)
		{
			//STUPID STD::STRING !! I HAVE NO IDEA WHY THIS PROGRAM DOESN`T LOAD WHEN TEXT IN STRING TABLE EXCEEDS 256 CHARS!!!!!!
			case PLID_MERCURY:
			{
				planet = new CSmallPlanet(0.0f, 5.0f, 0.0f, 90.0f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\mercury.bmp", false);
				planet->rotationAnglePerSecond = 25.0f;
				planet->angleAxis2Orbit = 180 + 2.0f;
				descriptionText->Clear();
				descriptionText->Printf( " Merkury\n\
					Pierwsza planeta liczac wg rosnacej odleglosci od Slonca; klasy J.\
					\n\n\n   DANE\n\
					Odleglosc od Slonca: 57.91 mln. km [0.3871 AU]\n\
					Czas obiegu wokol Slonca: 87.969 dni\n\
					Czas jednego obrotu wokol osi: 58.65 dnia.\n\
					Masa: 3.303 * 10 ^ 23 kg.\n\
					Predkosc Ucieczki (z rownika): 4.3 km/s\n\
					Brak ksiezycow\n\
					Rozlegle Zelazowo - Niklowe jadro. Srednia aktywnosc tektoniczna.");
				break;
			}

			case PLID_VENUS:
			{
				planet = new CSmallPlanet(0.0f, 5.0f, 0.0f, 90.0f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\venus.bmp", false);
				planet->rotationAnglePerSecond = -25.0f;
				planet->angleAxis2Orbit = 180 + 177.3f;
				descriptionText->Clear();
				descriptionText->Printf( " Wenus\n\
					Druga planeta liczac wg rosnacej odleglosci od Slonca; klasy C. Najgoretsza planeta w Ukladzie Slonecznym z racji wysokiego stezenia 9\
					ditlenku wegla w atmosferze.\
					\n\n\n   DANE\n\
					Odleglosc od Slonca: 108.2 mln. km [0.7233 AU]\n\
					Czas obiegu wokol Slonca: 224.701 dni\n\
					Czas jednego obrotu wokol osi: 243.01 dnia [obrot wsteczny].\n\
					Masa: 4.870 * 10 ^ 23 kg.\n\
					Predkosc Ucieczki (z rownika): 10.4 km/s\n\
					Brak ksiezycow\n\
					Zelazowo - Niklowe jadro. Srednia aktywnosc tektoniczna.");
				break;
			}

			case PLID_EARTH:
			{
				planet = new CSmallPlanet(0.0f, 5.0f, 0.0f, 90.0f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\earth.bmp", false);
				planet->rotationAnglePerSecond = 25.0f;
				planet->angleAxis2Orbit = 180 + 23.44f;
				//c:planet->bHasAtmosphere = true;
				descriptionText->Clear();
				descriptionText->Printf( " Ziemia\n\
					Trzecia planeta liczac wg rosnacej odleglosci od Slonca; klasy M, ojczyzna ludzi.\
					\n\n\n   DANE\n\
					Odleglosc od Slonca: 150 mln. km [1 AU]\n\
					Czas obiegu wokol Slonca: 365,256 dni\n\
					Czas jednego obrotu wokol osi: 24.9345 godziny.\n\
					Masa: 5.976 * 10 ^ 24 kg.\n\
					Predkosc Ucieczki (z rownika): 11.2 km/s\n\
					1 ksiezyc - Ksiezyc\n\
					Zelazowo - Niklowe jadro. Srednia aktywnosc tektoniczna.");
				break;
			}

			case PLID_MARS:
			{
				planet = new CSmallPlanet(0.0f, 5.0f, 0.0f , 90.0f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\mars.bmp", false);
				planet->rotationAnglePerSecond = 25.0f;
				planet->angleAxis2Orbit = 180 + 6.68f;
				descriptionText->Clear();
				descriptionText->Printf( " Mars\n\
					Czwarta planeta, liczac wg. rosnacej odleglosci od Slonca; klasy K. Tzw. Czerwona Planeta\
					\n\n\n   DANE\n\
					Odleglosc od Slonca: 227.94 mln. km [1.5237 AU]\n\
					Czas obiegu wokol Slonca: 686.98 dni\n\
					Czas jednego obrotu wokol osi: 24.6229 godziny.\n\
					Masa: 6,421 * 10 ^ 23\n\
					Predkosc Ucieczki (z rownika): 5 km/s\n\
					2 ksiezyce - Phobos i Deimos\n\
					Zelazowo - Niklowe jadro. Srednia aktywnosc tektoniczna" );
				break;
			}

			case PLID_JUPITER:
			{
				planet = new CSmallPlanet(0.0f, 5.0f, 0.0f, 90.0f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\jupiter.bmp", false);
				planet->rotationAnglePerSecond = 25.0f;
				planet->angleAxis2Orbit = 180 + 3.12f;
				descriptionText->Clear();
				descriptionText->Printf( " Jowisz\n\
					Piata planeta, liczac wg. rosnacej odleglosci od Slonca; klasy A. Pierwsza planeta za pasem asteroid (Ceres)\
					\n\n\n   DANE\n\
					Odleglosc od Slonca: 778.33 mln. km [5.2028 AU]\n\
					Czas obiegu wokol Slonca: 4332.71 dni\n\
					Czas jednego obrotu wokol osi: 9.841 godziny.\n\
					Masa: 1,900 * 10 ^ 27 kg\n\
					Predkosc Ucieczki (z rownika): 59.6 km/s\n\
					16 ksiezycow - Metis, Adrastea, Amaltea, Tebe, Io, Europa, Ganimedes, Kallisto, Leda, Himalia, Lysithea, Elara, Ananke, Karme, Pasifae, Sinope\n\
					Male Zelazowo - Niklowe jadro.\n\
					Masa Jowisza przekracza sume mas pozostalych planet (stanowi 71 procent tej masy)" );
				break;
			}

			case PLID_SATURN:
			{
				planet = new CSmallPlanet(0.0f, 5.0f, 0.0f, 90.0f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\saturn.bmp", true);
				planet->rotationAnglePerSecond = -25.0f;
				planet->angleAxis2Orbit = 180 + 26.71f;
				descriptionText->Clear();
				descriptionText->Printf( " Saturn\n\
					Szosta planeta, liczac wg. rosnacej odleglosci od Slonca; klasy B. Posiada widoczne z Ziemi pierscienie\
					\n\n\n   DANE\n\
					Odleglosc od Slonca: 1426.98 mln. km [9.5388 AU]\n\
					Czas obiegu wokol Slonca: 10759.5 dni\n\
					Czas jednego obrotu wokol osi: 10.233 godziny.\n\
					Masa: 5,688 * 10 ^ 26 kg\n\
					Predkosc Ucieczki (z rownika): 35.5 km/s\n\
					18 ksiezycow - Pan, Atlas, Prometheus, Pandora, Epimeteus, Janus, Mimas, Enceladus, Tethys, Telesto, Kalipso, Dione, Helena, Rea, Tytan, Hyperion, Japet, Febe\n\
					Male Skalisto - Zelazne jadro.\n\
					Gestosc Saturna wynosi 0.69 g / cm^3 - moglby unosic sie na wodzie." );
				break;
			}

			case PLID_URANUS:
			{
				planet = new CSmallPlanet(0.0f, 5.0f, 0.0f, 90.0f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\uranus.bmp", false);
				planet->rotationAnglePerSecond = 25.0f;
				planet->angleAxis2Orbit = 180 + 97.86f;
				descriptionText->Clear();
				descriptionText->Printf( " Uran\n\
					Siodma planeta, liczac wg. rosnacej odleglosci od Slonca; klasy B.\
					\n\n\n   DANE\n\
					Odleglosc od Slonca: 2870.99 mln. km [19.1914 AU]\n\
					Czas obiegu wokol Slonca: 30685 dni\n\
					Czas jednego obrotu wokol osi: 17.9 godziny [obrot wsteczny].\n\
					Masa: 8,684 * 10 ^ 25 kg\n\
					Predkosc Ucieczki (z rownika): 21.3 km/s\n\
					15 ksiezycow - Kordelia, Ofelia, Bianka, Cressida, Desdemona, Julia, Portia, Rozalinda, Belinda, Puk, Miranda, Ariel, Umbriel, Tytania, Oberon\n\
					Male skaliste zestalone jadro.\n\
					Rownik Urana jest nachylony do orbity pod katem 97 stopni i 86 minut - Uran obraca sie wiec prostopadle do orbity." );
				break;
			}

			case PLID_NEPTUNE:
			{
				planet = new CSmallPlanet(0.0f, 5.0f, 0.0f, 90.0f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\neptune.bmp", false);
				planet->rotationAnglePerSecond = 25.0f;
				planet->angleAxis2Orbit = 180 + 29.6f;
				descriptionText->Clear();
				descriptionText->Printf( " Neptun\n\
					Osma planeta, liczac wg. rosnacej odleglosci od Slonca; klasy B.\
					\n\n\n   DANE\n\
					Odleglosc od Slonca: 4497.07 mln. km [30.0611 AU]\n\
					Czas obiegu wokol Slonca: 60190 dni\n\
					Czas jednego obrotu wokol osi: 19.2 godziny.\n\
					Masa: 1,024 * 10 ^ 26 kg\n\
					Predkosc Ucieczki (z rownika): 23.3 km/s\n\
					8 ksiezycow - Najada, Talassa, Despoina, Galatea, Larissa, Proteus, Triton, Nereida\n\
					Male skaliste jadro.\n" );
				break;
			}

			case PLID_PLUTO:
			{
				planet = new CSmallPlanet(0.0f, 5.0f, 0.0f, 90.0f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\pluto.bmp", false);
				planet->rotationAnglePerSecond = 25.0f;
				planet->angleAxis2Orbit = 180 + 122.46f;
				descriptionText->Clear();
				descriptionText->Printf( " Pluton\n\
					Ostatnia (dziewiata) planeta, liczac wg. rosnacej odleglosci od Slonca; klasy L.\
					\n\n\n   DANE\n\
					Odleglosc od Slonca: 5913.527 mln. km [39.5294 AU]\n\
					Czas obiegu wokol Slonca: 90800 dni\n\
					Czas jednego obrotu wokol osi: 6.3872 dnia [obrot wsteczny].\n\
					Masa: 1,29 * 10 ^ 22 kg\n\
					Predkosc Ucieczki (z rownika): 1.1 km/s\n\
					1 ksiezyc - Charon\n\
					Duze skaliste jadro.\n\
					Obieg Plutona i Charona jest podwojnie synchroniczny - wokol Slonca krazy nie Pluton, ale srodek masy ukladu Pluton - Charon\n\
					Pluton okazyjnie bywa blizej Slonca niz Neptun." );
				break;
			}

			default:
			{
				log <<"CPlanetState::SetPlanet() - requested setting an unknown planet; suspending all actions\n";
				break;
			}
		}
		
		planet->Init();

		log <<"CPlanetState::SetPlanet() - planet successfuly created\n";
	}

} //end of namespace Sol