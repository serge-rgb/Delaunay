/*
 * Vec.h
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

#ifndef VEC_H_
#define VEC_H_

class HalfEdge;
/**
 * Immutable vector class. Serves as a 2d vector when z=0.
 */
class Vec {
public:

    // Constructors
    Vec() : x(0), y(0), z(0) {}
    Vec(double x, double y) : x(x), y(y), z(0) {}
    Vec(double x, double y, double z) : x(x), y(y), z(z) {}

    // Operators.
    const Vec operator +(const Vec &v);
    const Vec operator -(const Vec &v);
    Vec & operator =(const Vec &v);

    // Math operations

    /**
     * @param v
     * @return Pseudo-distance used for triangle bound gen.
     */
    double Magnitude2d(Vec const v) const;

    double x;
    double y;
    double z;

private:
    // Output
    friend ostream & operator << (ostream &s, const Vec &v) {
        return s << v.x << ", " << v.y << ", " << v.z;
    }
};



#endif /* VEC_H_ */
