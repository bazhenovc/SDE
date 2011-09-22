cmake_minimum_required(VERSION 2.6)

set(ARTWORK apps.png black.png close.png keyboard.png panel.png settings.png system.png
			wallpaper.png winlist.png)

INSTALL(FILES ${ARTWORK}
		DESTINATION ${CMAKE_INSTALL_PREFIX}/share/sde/data)
