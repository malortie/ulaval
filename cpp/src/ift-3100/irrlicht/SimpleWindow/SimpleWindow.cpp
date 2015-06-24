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

// Pointeur de gestionnaire de scènes.
ISceneManager* smgr	= nullptr;

//
// Fonction exécutée lors de l'appel de la fonction exit(int).
//
void _cdecl IrrlichtExit(void)
{
	// Destruction du device irrlicht.
	if (!device->drop())
	{
		std::cerr << "Failed to drop irrlicht device " << &device << "." << std::endl;
	}

	// Mise à 0 des pointeurs, pour éviter d'avoir des références pendantes.
	device	= nullptr;
	driver	= nullptr;
	env		= nullptr;
	smgr	= nullptr;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Spécification d'une fonction à exécuter lors
	// avant le retour de la fonction main, (arrêt du programme). 
	atexit(IrrlichtExit);

	try
	{
		// Nous appelons la fonction driverChoiceConsole pour permettre de sélectionner
		// un pilote spécifique pour le rendement. 
		static irr::video::E_DRIVER_TYPE devType = driverChoiceConsole();

		// Création d'un device Irrlicht. Ce pointeur est très important car
		// il permet d'accéder à toutes les fonctionnalités.
		device = createDevice(devType, dimension2du(640, 480), 16U, false, false, false);

		// Validation du device irrlicht.
		if (!device)
			throw std::logic_error("Failed to create irrlicht device!");

		// Obtention d'un pointeur vers le pilote vidéo.
		driver = device->getVideoDriver();

		// Validation du pointeur de pilote vidéo.
		if (!driver)
			throw std::logic_error("Device has an uninitialized, or NULL driver!");

		// Obtention d'un pointeur vers l'interface graphique.
		env = device->getGUIEnvironment();

		// Validation du pointeur d'interface graphique.
		if (!env)
			throw std::logic_error("Device has an uninitialized, or NULL GUI environment!");

		// Obtention d'un pointeur vers le gestionnaire de scène.
		smgr = device->getSceneManager();

		// Validation du pointeur du gestionnaire de scène.
		if (!smgr)
			throw std::logic_error("Device has an uninitialized, or NULL scene manager!");
	}
	catch (const std::logic_error& e)
	{
		// Une exception de type logic_error est levée.
		std::cerr << "@logic_error: " << e.what() << std::endl;
		exit(1); // Appel de la fonction d'arrêt.
	}
	catch (...)
	{
		// Exception inconnue.
		std::cerr << "Caught an unknown exception!" << std::endl;
		exit(1); // Appel de la fonction d'arrêt.
	}

	try
	{
		// Tant qu'il est nécessaire d'afficher la scène.
		while (device->run())
		{
			// beginScene est une méthode servant à spécifier le début de construction
			// d'une scène dans irrlicht. Tout ce qui se passe après cet instruction
			// sera envoyé au framebuffer.
			driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));

			// Nous ajoutons tous les éléments de la scènes au framebuffer.
			smgr->drawAll();

			// Nous ajoutons les interfaces graphiques au framebuffer.
			env->drawAll();

			// Nous utilisons la méthode endScene pour spécifier la fin
			// de construction d'une scène. Par la suite, tout ce qui se trouve
			// dans le framebuffer sera affiché à l'écran.
			//
			// Il s'agit du processus de rastérisation, plus précisément de
			// convertir les informations d'une scène en image.
			driver->endScene();
		}
	}
	catch (const std::bad_alloc& e)
	{
		// Une exception de type logic_error est levée.
		std::cerr << "@bad_alloc: " << e.what() << std::endl;
		exit(1); // Appel de la fonction d'arrêt.
	}
	catch (...)
	{
		// Exception inconnue.
		std::cerr << "Caught an unknown exception!" << std::endl;
		exit(1); // Appel de la fonction d'arrêt.
	}

	return 0;
}

