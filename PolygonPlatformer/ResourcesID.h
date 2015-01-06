
#pragma once

namespace States {
	enum ID {
		NONE = 0,
		TITLE = 1,
		MENU = 1 << 1,
		LOAD = 1 << 2,
		GAME = 1 << 3,
		PAUSE = 1 << 4,
		CREDITS = 1 << 5,
		UPGRADE = 1 << 6 ,
		OPTIONS = 1 << 7 ,
		LIMIT
	};
}


namespace Fonts {
	enum ID {
		F_MENU,
		F_CONSOLE,
		FONTS_COUNT
	};
}