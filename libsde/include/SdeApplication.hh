/**
	SDE core libraries
	Copyright (c) 2011 SDE development team

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

/**
	This class provides general SDE apps messaging and theme handling
*/
class SdeApplication {
public:

	/**
		Initialize all basic settings
		@brief
		This function should be called right after QApplication instance
		created. It will load all initial app configuration, stored in
		~/.sde/app.conf
	*/
	static void init();

};
