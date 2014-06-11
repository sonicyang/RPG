RPG
===

An ANSI RPG Game, Promgramed in C/C++

This is my Final Project of 2014 Spring Introduction to Computer Class.

License Under GPL v2

Compile Requirement:
1. SDL
	1.1 SDL2
	1.2 SDL2_Image
	1.3 SDL2_ttf
2. gnu toolchains

Compiling:

	Windows:
		1. Install Code::Blocks (if you are not using it)
			Code::Blocks Download : http://www.codeblocks.org/downloads
		2. Download SDL2 and its developemnt packages
				  SDL2: http://www.libsdl.org/release/SDL2-devel-2.0.3-mingw.tar.gz
			SDL2_Image: https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.0-mingw.tar.gz
			  SDL2_ttf:	https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.12-mingw.tar.gz
		3. Install SDL2
			Method 1: 
				1. Copy every File in i686-w64-mingw32(might in subDirectory) from each GZip file you just downloaded to (Where you Install Code::Blocks)/MinGW/
				2. Add "-lmingw32 -lSDL2main -lSDL2 -mwindows -lSDL2_ttf -lSDL2_image" (without quotes) 
			Method 2: Follow http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/codeblocks/index.php
		4. Compile Using Code::Blocks
		
	Linux:
		1. Install DL2 and its developemnt packages
			Ubuntu : issue "sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev"
			Other  : Use your own Package Manager or compile using source : 
				http://www.libsdl.org/release/SDL2-2.0.3.tar.gz
				https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0.tar.gz
				https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12.tar.gz
		2. make sure you have g++ or clang and make, if not
			Ubuntu : issue "sudo apt-get install make G++"
			Other  : Use your own Package Manager
		3. issue make under ./
		4. Excutable will be at ./RPG
	
	MacOSX:
		1. make sure you have MacPorts
		2. Install DL2 and its developemnt packages
			issue "sudo port install libsdl2 libsdl2-image libsdl2-ttf"
		3. make sure you have Xcodes
			Install from App Store
		4. make sure you have make, if not
			issue "sudo port install make"
		5. issue make under ./
		6. Excutable will be at ./RPG

Editing:
	As Current Editor (github.com/sonicyang/RPGMaker) is still developing, Editing will be Done using Text Editor(Nopepad++, Vim... etc) in data folder, 
	Every File is in JSON Format and Plain Text
	
	data/
		setting.manifest		Basic App Settings
		
		inv.sav					saving data
		map.sav					saving data
		team.sav				saving data
	
		imgs/ 					Holds image resources
		tiles/					Holds map Tile resources
		font/					Holds font resources
		events/					Holds events
			eventlist.lst		Event LookUp List
			***.evt				Event ***
		items/
			***.item			Item ***
		maps/					Holds maps
			maplist.lst			Map LookUp List
			***.map				map ***
		monsters/				Holds Monsters
			monsterlist.lst		Monster LookUp List
			***.mst				Monster ***
		roles/					Holds Roles
			rolelist.lst		Role LookUp List
			***.rol				Role ***
		team/
			teamlist.lst		Team&Character Setting List
	
	For an Event
		It has a Name.
		TriggerType is not used
		Command is list of Commands Event will excute
			in format "command|Parameter1|Parameter2|Parameter3|..."
			
			List of Commands : 
			
			command 	means			parameters
				1		showPrompt		Whom, Message
				2		endEvent		
				3		transferMap		mapName, x, y
				4		addItem			name, Number
				5		removeItem		name, Number
				6		setMoney		value
				7		addMoney		value(negative if to decrease)
				8		jner   			Name of Var, value, address(Relatively)	// Jump Not Equal
				9		jer,        	Name of Var, value, address(Relatively	// Jump Equal
				10		jne,        	Name of Var, value, address(Absolute)	// Jump Not Equal
				11		je,         	Name of Var, value, address(Absolute)	// Jump Equal
				12		mov,        	Name of Destination Var, Name of Source Var //Move Vars
				13		set,			Name of Var, Value						//Set Var Values
				14		addCharToTeam   Character Name
				15		removeCharFromTeam  Character Name         15,
				16		battle,         Name of Monsters(Cna have up to 4)
				17		vendor,         Name of Item
				18		setRole			Name of Character, Name of Role
	
	For Map System
		Facing ranges form 0~3 means North, East, South, West; and serve as a offset on Tile's X axis when rendering
		
	For Map LookUp List
		Count -> Map Count
		Path -> List of Path to Maps
		Default > When Game Start which map is default
		pTile -> Player Tile file for rendering
		pIcon -> x, y coordinates of the Tile of Player Rendering
	
	For a Map
		It has a Name.
		It has a Size.
		It has a Tile File for rendering
		It's hav 3 Arrays for data
			Floorx -> x coordinate for each block on map in Tile File
			Floory -> y coordinate for each block on map in Tile File
			Floors -> 1 Wall, 0 Not Wall
		BackGound a Background Image
		List of Objects:
			Has a Name
			Type doesn't matter
			canStep -> can be steped on
			Trigger -> Name of Event to Trigger
			TrigType -> 1 Trigger by pressing z; 2 Trigger by walking over it
			Tile -> Tile File for Rendering
			Facing -> Which way is the Object Facing
			Icon -> x, y coordinates of the Tile
	
	For a Item
		Has a Name and Description.
		Has HPv MPv ATKv DEFv -> Variants of Hp Mp Attack Defense up on usage
		Comsumable -> 1 will depose upon usage; 0 can reuse
		Type:
			0	Potion
			1	Team Potion
			2	Head
			3	Armor
			4	Legs
			5	Shoes
			6	Weapons
	
	For a Skill
		Has a Name and Description.
		MPC -> Mp comsumed
		eTarget: Enemy Target Setting
			0: None
			1: One
			2: All
		Has eHPv eMPv eATKv eDEFv -> Variants of Enemy Hp Mp Attack Defense up on usage
		fTarget: Friendly Target Setting
			0: None
			1: One
			2: All
		Has fHPv fMPv fATKv fDEFv -> Variants of Friendly Hp Mp Attack Defense up on usage
		
	For a Role
		Has a Name.
		HP MP Attack Defense as Array of 2 intergers to present the form of following Formula
		Eg:
			HP = a + b*level
		
		a as first interger of the Array, b as the second one
		
		List of Skills with Level as the Level to Learn it, Name as the Name of Skill.
	
	For teamlist.lst
		Count Number of Chacters
		All a List of Characters
			Name : Character Name
			Role : Default Role
			Level : Default Level
		Default : Default Character in Team
		
			

