/**
	SDE session
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

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <QProcess>

int main() {

	// Start desktop
	QProcess desktopProcess;
	desktopProcess.start("sde-desktop");
	desktopProcess.waitForStarted(-1);

	// Execute autostart apps


	// Wait for apps to die
	desktopProcess.waitForFinished(-1);

	return 0;
}
