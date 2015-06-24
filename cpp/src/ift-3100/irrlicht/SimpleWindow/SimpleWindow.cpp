// SimpleWindow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Espaces de nom d'irrlicht.
using namespace irr;
using namespace irr::core;
using namespace irr::io;
using namespace irr::gui;
using namespace irr::scene;
using namespace irr::video;

// Pointeur de device irrlicht.
IrrlichtDevice* device = nullptr;

// Pointeur de pilote graphique.
IVideoDriver* driver = nullptr;

// Pointeur d'interface graphique.
IGUIEnvironment* env = nullptr;

// Pointeur de gestionnaire de sc�nes.
ISceneManager* smgr	= nullptr;

//
// Fonction ex�cut�e lors de l'appel de la fonction exit(int).
//
void _cdecl IrrlichtExit(void)
{
	// Destruction du device irrlicht.
	if (!device->drop())
	{
		std::cerr << "Failed to drop irrlicht device " << &device << "." << std::endl;
	}

	// Mise � 0 des pointeurs, pour �viter d'avoir des r�f�rences pendantes.
	device	= nullptr;
	driver	= nullptr;
	env		= nullptr;
	smgr	= nullptr;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Sp�cification d'une fonction � ex�cuter lors
	// avant le retour de la fonction main, (arr�t du programme). 
	atexit(IrrlichtExit);

	try
	{
		// Nous appelons la fonction driverChoiceConsole pour permettre de s�lectionner
		// un pilote sp�cifique pour le rendement. 
		static irr::video::E_DRIVER_TYPE devType = driverChoiceConsole();

		// Cr�ation d'un device Irrlicht. Ce pointeur est tr�s important car
		// il permet d'acc�der � toutes les fonctionnalit�s.
		device = createDevice(devType, dimension2du(640, 480), 16U, false, false, false);

		// Validation du device irrlicht.
		if (!device)
			throw std::logic_error("Failed to create irrlicht device!");

		// Obtention d'un pointeur vers le pilote vid�o.
		driver = device->getVideoDriver();

		// Validation du pointeur de pilote vid�o.
		if (!driver)
			throw std::logic_error("Device has an uninitialized, or NULL driver!");

		// Obtention d'un pointeur vers l'interface graphique.
		env = device->getGUIEnvironment();

		// Validation du pointeur d'interface graphique.
		if (!env)
			throw std::logic_error("Device has an uninitialized, or NULL GUI environment!");

		// Obtention d'un pointeur vers le gestionnaire de sc�ne.
		smgr = device->getSceneManager();

		// Validation du pointeur du gestionnaire de sc�ne.
		if (!smgr)
			throw std::logic_error("Device has an uninitialized, or NULL scene manager!");
	}
	catch (const std::logic_error& e)
	{
		// Une exception de type logic_error est lev�e.
		std::cerr << "@logic_error: " << e.what() << std::endl;
		exit(1); // Appel de la fonction d'arr�t.
	}
	catch (...)
	{
		// Exception inconnue.
		std::cerr << "Caught an unknown exception!" << std::endl;
		exit(1); // Appel de la fonction d'arr�t.
	}

	try
	{
		// Tant qu'il est n�cessaire d'afficher la sc�ne.
		while (device->run())
		{
			// beginScene est une m�thode servant � sp�cifier le d�but de construction
			// d'une sc�ne dans irrlicht. Tout ce qui se passe apr�s cet instruction
			// sera envoy� au framebuffer.
			driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));

			// Nous ajoutons tous les �l�ments de la sc�nes au framebuffer.
			smgr->drawAll();

			// Nous ajoutons les interfaces graphiques au framebuffer.
			env->drawAll();

			// Nous utilisons la m�thode endScene pour sp�cifier la fin
			// de construction d'une sc�ne. Par la suite, tout ce qui se trouve
			// dans le framebuffer sera affich� � l'�cran.
			//
			// Il s'agit du processus de rast�risation, plus pr�cis�ment de
			// convertir les informations d'une sc�ne en image.
			driver->endScene();
		}
	}
	catch (const std::bad_alloc& e)
	{
		// Une exception de type logic_error est lev�e.
		std::cerr << "@bad_alloc: " << e.what() << std::endl;
		exit(1); // Appel de la fonction d'arr�t.
	}
	catch (...)
	{
		// Exception inconnue.
		std::cerr << "Caught an unknown exception!" << std::endl;
		exit(1); // Appel de la fonction d'arr�t.
	}

	return 0;
}

