/*
 * HalfEdge.h
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

#ifndef HALFEDGE_H_
#define HALFEDGE_H_

/**
 *
 * The half edge data structure stores topology information.
 * It has three indices that act as pointers to the structures of a Mesh.
 * The indices point to the incident vector,
 *  to the next counter clockwise half edge, and to its twin edge,
 * inversely oriented and part of an adjacent face.
 *
 */

enum class HalfEdgeProperties {
    NO_TWIN = -1
};

class HalfEdge {
public:
    // Constructor.
    HalfEdge() : point(0), next(0), twin((int) HalfEdgeProperties::NO_TWIN) {}
    bool operator ==(const HalfEdge &e);
    int         point;
    int         next;
    int         twin;

};

/**
 * A face is a pointer to a half edge. It is useful for traversal of meshes.
 */
typedef HalfEdge* Face;

inline bool HalfEdge::operator ==(const HalfEdge & e) {
    return point == e.point && next == e.next && twin == e.twin;
}



#endif /* HALFEDGE_H_ */
