/*
 * common.h
 *
 *  This file is part of Delaunay.
 *
 *  Delaunay is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Delaunay is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Delaunay.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMON_H_
#define COMMON_H_

// C/C++ standard libraries
#include <iostream>
#include <cassert>
#include <cmath>
#include <tr1/memory>

#ifndef OPTIMIZE_SET
#include <set>
#endif
#ifdef OPTIMIZE_SET
//#include <tr1/unordered_set.h> would be preferable, not working for me with clang.
#include <backward/hash_set>
#define set __gnu_cxx::hash_set
#endif

#include <vector>
#include <algorithm>
#include <cstdlib>

// Unix
#include <unistd.h>

// OpenGL / GLUT in linux
#ifdef __linux__
#include <QApplication>
#include <QDesktopWidget>
#include <qt4/QtGui/QDesktopWidget>
#include <QtGui>
#include <QtOpenGL>
#endif

using namespace std;
using namespace tr1;

// Local includes:
// Gtest (used for friendly access..)
#include <gtest/gtest_prod.h>
#include "Math.h"

#endif /* COMMON_H_ */
