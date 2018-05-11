# Documentation Arcade

 ## Classe : Core

Le Coeur du programme est initialisé dans le main. Il permet le chargement de la librairie graphique indiqué par l’utilisateur et le chargements de toutes les autres librairies graphiques en cas de besoin. Il crée une liste des librairies situé dans un dossier spécifique. Ces librairies seront donc utilisable par le programe.

> Core.hpp
```c++
namespace Arcade {
	// The core will be initialized by the main, then it will handle the program
	// The purpose of the Core is to handle the main loop for the program
	// Then load the actual lib chosen by the user and load the other libs when needed.
	// Then Core will call the function to render the game and then the lib function to do when the game "asks"

	// The core will get the events and "declare" them to the game.
	class Core {
	public:
		// path => the path to the lib given by the user in argument.
		// Error handling not necessary done, so need to do it then continue or not.
		explicit Core(const std::string &libPath);
		~Core();

		// Begin of the Core and the program.
		int startArcade();
		// find all the graph libs (.so files) in the /libs folder and fill the libraryPathes mem
		void parseLibDir();
		// find all the games (.so files) in the /games folder and fill the gamePathes mem
		void parseGameDir();
		const GameLibLoader &getGameLoader() const;
		void setGameLoader(const GameLibLoader &gameLoader);
		const GraphLibLoader &getGraphLoader() const;
		void setGraphLoader(const GraphLibLoader &graphLoader);
		bool checkEvents(Arcade::Keys key);
	};
}

```


## Classe : ArgPargser

La classe ArgParser permet la gestion et le parsing des arguments
>ArgParser/hpp

  ```c++
  namespace Arcade {
	// This class provide a static method to parse the arg sent by the user
	class ArgParser {
	public:
		ArgParser();
		~ArgParser() = default;
			//_Permet la gestion et le parsing des arguments_
			static int parseArgs(int argc, char **argv);

	};
}
  ```


## Classe : GameLibLoader


Le GameLibLoader permet le chargement, la gestion et la fermeture des jeux.
>GameLibLoader.hpp

```c++
namespace Arcade {
	class GameLibLoader {
	public:
		GameLibLoader();
		~GameLibLoader();

		// return the object created by the graphical lib when it has been loaded dlsym on the exntryPoint has been done.
		IGameLib *getLibInstance();
		// load the lib at the libPath given in argument. Then save the instance of the lib in the object. Need to call unloadLib before load a new one.
		bool loadLib(const std::string &libPath);
		// check the lib demanded exits and the file is an elf.
		bool isElfFile(const std::string &libPath) const;
		// this function call dlclose on the lib.
		bool unloadLib();

	private:
		std::string libPath;
		void *handleAddr;
		IGameLib *entryPointResult;
		bool isLibLoaded;
	};
}
```

## Classe : GraphLibLoader

Le GameLibLoader permet le chargement, la gestion et la fermeture des jeux.
>GrapLibLoadder.hpp
  ```c++
  namespace Arcade {
	// The purpose of this function is to load a lib with dlopen etc ...
	// Then get the instance of the IGraphicLib returned by the entryPoint
	// Of the loaded lib.
	class GraphLibLoader {
	public:
		GraphLibLoader();
		~GraphLibLoader();

		// return the object created by the graphical lib when it has been loaded dlsym on the exntryPoint has been done.
		IGraphicLib *getLibInstance();
		// load the lib at the libPath given in argument. Then save the instance of the lib in the object. Need to call unloadLib before load a new one.
		bool loadLib(const std::string &libPath);
		// check the lib demanded exits and the file is an elf.
		bool isElfFile(const std::string &libPath) const;
		// this function call dlclose on the lib.
		bool unloadLib();

	private:
		std::string libPath;
		void *handleAddr;
		IGraphicLib *entryPointResult;
		bool isLibLoaded;
	};
}
  ```

## Classe : Color

La classe Color permet la création et la manipulation des couleurs utilisés pour les jeux

>Color.hpp

```c++
namespace Arcade {
	class Color {
	public:
		Color(unsigned char red = 0, unsigned char green = 0,
			unsigned char blue = 0, unsigned char alpha = 0);
		~Color() = default;
		void setColor(unsigned char red = 0, unsigned char green = 0,
			unsigned char blue = 0, unsigned char alpha = 0);
		unsigned char getRed() const;
		unsigned char getGreen() const;
		unsigned char getBlue() const;
		unsigned char getAlpha() const;
		void setRed(unsigned char red);
		void setGreen(unsigned char green);
		void setBlue(unsigned char blue);
		void setAlpha(unsigned char alpha);
		operator unsigned char *();
		bool operator!=(const Color &ocolor);
		bool operator==(const Color &ocolor);

	};
};
```

## Classe : PixelBox

La Classe PixelBox permet la création et la manipulation de pixels dans le jeu

  > PixelBox.hpp
```c++
namespace Arcade {
	class PixelBox {
	public:
		PixelBox(Vect<size_t> size = Vect<size_t>(),
			Vect<size_t> pos = Vect<size_t>(),
			Color col = Color(255, 255, 255, 255));
		~PixelBox() = default;

		size_t getHeight() const;
		size_t getY() const;
		void setHeight(size_t height);
		void setY(size_t y);

		size_t getWidth() const;
		size_t getX() const;
		void setWidth(size_t width);
		void setX(size_t x);

		Vect<size_t> getSize() const;
		void setSize(Vect<size_t> size);
		Vect<size_t> getPos() const;
		void setPos(Vect<size_t> pos);

		void putPixel(Vect<size_t> pos, Color col);
		Color getPixel(Vect<size_t> pos) const;

		void putRect(Vect<size_t> pos, Vect<size_t> size, Color col);

		std::vector<Color> &getPixelArray();

	};
};

```

## Classe : TextBox

La Classe TextBox permet la création et la manipulation de textes dans le jeu
> TextBox.hpp

```c++
namespace Arcade {
	class TextBox {
	public:
		TextBox(std::string const &text, Vect<size_t> pos,
			size_t fontSize = 30,
			Color color = Color(255, 255, 255, 255),
			Color backgroundColor = Color(0, 0, 0, 255));
		~TextBox() = default;

		const std::string &getValue() const;
		void setValue(std::string const &text);

		Vect<size_t> getPos() const;
		void setPos(Vect<size_t> pos);

		size_t getX() const;
		size_t getY() const;
		void setX(size_t x);
		void setY(size_t y);

		size_t getFontSize() const;
		void setFontSize(size_t size);

		Color getColor() const;
		void setColor(Color color);

		Color getBackgroundColor() const;
		void setBackgroundColor(Color color);
	};
};
```




## Enum : Keys

Énumération listant toutes les touches utilisable dans un jeudi


## Classe : LogicExeption

La classe LogicExeption permet l ‘affichage d’un message lors d’une erreur
> LogicExeption.hpp
```c++
namespace Arcade {
	class LogicException : public std::exception {
	public:
		explicit LogicException(const std::string &message);
		~LogicException();
		const std::string &what();
	};
}
```

# Implémentation de lib et de jeux

## Implémenter un jeu

## Création d'un entry point

Créer un fichier entrypoint.cpp qui permet d'appeler le ctor /dtor de la futur classe, le placer dans games/src/**Nom Du Jeu**.
> Exemple de code
``` c++
#include <iostream>
#include "LibNibbler.hpp"

/* "Arcade::SFML" : For example, use the class of your lib */
Arcade::IGameLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	/* Again, it's for example, use the class of your lib */
	ret = new Arcade::LibNibbler;
}

__attribute__((destructor))
void out()
{
	delete ret;
}


extern "C" Arcade::IGameLib *entryPoint()
{
	return ret;
}

```
## Implémenter la classe

L'objectif est d'implémenter la classe en utilisant l'interface **IGameLib**

```c++
namespace Arcade {
	class IGameLib {
	public:
		virtual ~IGameLib() = default;

		/* Get the name of the game */
		virtual const std::string getName() const = 0;

		/* Resources handling */
		// Initializes the library
		virtual bool init() = 0;

		// Unloads the library
		virtual bool stop() = 0;

		// Processes the key obtained by the IGraphicLib from the user to update the game state
		virtual void applyEvent(Keys key) = 0;

		// Updates the game state. (Move the player forward and/or move the NPCs)
		virtual void update() = 0;

		// Renders the game state to the screen. This should call IGraphicLib::refresh() to display content to the user.
		virtual void refresh(IGraphicLib &graphicLib) = 0;

		// To call at the end of the execution of the game (after the player loose or win) for getting his score
		virtual size_t getScore() = 0;
	};
};

```

## Compiler et lancer le jeu

- Les fichier du jeu doivent être placés dans /games/src/**NomDuJeu**
- Ajouter dans le Makefile situé dans /games,  le **path** du jeu
-  Lancer Arcade, le jeu sera disponible dans le menu


## Implémenter une lib graphique

## Création d'un entry point
Créer un fichier entrypoint.cpp qui permet d'appeler le ctor /dtor de la futur classe, le placer dans libs/src/**Nom De La Lib**.

Créer un fichier entrypoint.cpp qui permet d'appeler le ctor /dtor de la futur classe.
> Exemple de code
``` c++
#include <iostream>
#include "LibSDL.hpp"

Arcade::IGraphicLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Arcade::LibSDL({800, 800}, "Arcade");
}

__attribute__((destructor))
void out()
{
	delete ret;
}

extern "C" Arcade::IGraphicLib *entryPoint()
{
	return ret;
}%
```
## Implémenter la classe

L'objectif est d'implémenter la classe en utilisant l'interface **IGraphicLib.hpp**

```c++
namespace Arcade {
	class IGraphicLib {
	public:
		virtual ~IGraphicLib() = default;

		/* Get the name of the library */
		virtual std::string getName() const = 0;

		/* Window handling */
		// Main loop condition
		virtual bool isOpen() const = 0;

		// Closes the window => stop loop (go menu)
		virtual void closeRenderer() = 0;

		// Opens the window => start loop
		virtual void openRenderer(std::string const &title) = 0;

		// Clears the screen
		virtual void clearWindow() = 0;

		// Displays the buffered frame to the screen
		virtual void refreshWindow() = 0;

		/* Rendering functions */
		// Draws a PixelBox or the sprite if supported
		virtual void drawPixelBox(PixelBox &) = 0;

		// Draws a TextBox
		virtual void drawText(TextBox &) = 0;

		/* EVENT HANDLING */
		/* */
		/* This part can seem complicated but the implementation is quite simple. */
		/* */
		/* pollEvent() fetches the events from the user and saves it */
		/* inside an std::vector<Arcade::Keys> or std::list<Arcade::Keys>. */
		/* It returns true if at least one new event was added to the list, false otherwise. */
		/* */
		/* getLastEvent() returns the first event of the list. (using front() and pop_front() methods) */
		/* or Arcade::Keys::NONE if the list is empty. */
		/* */
		/* clearEvents() clears the list (using clear() method). */
		/* */
		virtual bool pollEvents() = 0;
		virtual Keys getLastEvent() = 0;
		virtual void clearEvents() = 0;

		/* Context Info */
		// get the X and Y max of the windows
		virtual Vect<size_t> getScreenSize() const = 0;

		// get the Y max of the windows
		virtual size_t getMaxY() const = 0;

		// get the X max of the windows
		virtual size_t getMaxX() const = 0;
	};
};

```

## Compiler et lancer la lib

- Les fichier de la lib doivent être placés dans /games/src/**NomDeLaLib**
- Ajouter dans le Makefile situé dans /games,  le **path** de la lib
-  Lancer Arcade, la lib sera disponible dans le menu

