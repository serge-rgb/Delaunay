/*
 * Vec.cc
 *
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
 *
 */

#include "Vec.h"

const Vec Vec::operator +(const Vec & v) {
    Vec res(x + v.x, y + v.y, z + v.z);
    return res;
}

const Vec Vec::operator -(const Vec & v) {
    Vec res(x - v.x, y - v.y, z - v.z);
    return res;
}

Vec& Vec::operator =(const Vec &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

double Vec::Magnitude2d(const Vec v) const {
    assert(z == 0 && v.z == 0);
    return sqrt(x * v.x + y * v.y);
}
