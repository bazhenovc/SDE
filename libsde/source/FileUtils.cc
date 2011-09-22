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

#include <FileUtils.hh>

#include <unistd.h>
#include <fcntl.h>

QString FileUtils::cat(const QString &filename) {
	QString ret;
	ssize_t len = 0;

	int fd = open(filename.toStdString().c_str(), O_RDONLY);
	if (fd < 0) {
		return ret;
	}

	char buf = 0;
	while ((len = read(fd, &buf, sizeof(buf))) > 0) {
		ret += buf;
	}

	::close(fd);
	return ret;
}
