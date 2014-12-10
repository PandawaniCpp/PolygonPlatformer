
#pragma once

namespace States {
	enum ID {
		NONE = 0,
		TITLE = 1,
		MENU = 1 << 1,
		LOAD = 1 << 2,
		GAME = 1 << 3,
		PAUSE = 1 << 4,
		EXIT = 1 << 5,
		LIMIT
	};
}