#ifndef __COLOR_H__
#define __COLOR_H__


namespace df {
	
	//Colors that are recognized by the engine
	enum Color {
		UNEFINED_COLOR = -1,
		BLACK = 0,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
	};

	//Default color
	const Color COLOR_DEFAULT = WHITE;

}//End of namespace
#endif