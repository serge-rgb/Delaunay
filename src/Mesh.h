/*
 * Mesh.h
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

#ifndef MESH_H_
#define MESH_H_

#include "common.h"
#include "Entity.h"

//class MeshTest;

class Mesh : public Entity {
public:
    Mesh();
    /**
     *
     * Receives a verts in the ZX plane and returns a delaunay triangulation.
     * @param verts
     * @return
     */
    static const Mesh Generate(vector<Vec> *verts);
    const vector<HalfEdge> * GetEdges() const;
    const vector<Vec> * GetVerts() const;
    const set<int> * GetFaces() const;

private:
    // Private functions

    //================================================================================
    // Functions that help with the mesh generation.
    //================================================================================

    /**
     * Returns a vector of 3 ccw points making a triangle that contain all the vertices in the mesh.
     */
    vector<Vec> GetBoundingTriangle();
    FRIEND_TEST(MeshTest,BoundingTriangle);

    /**
     * Returns the index of the face containing the vector
     * Implementation This is linear-time.
     */
    int GetContainingFace(int iVec);

    /**
     * Will insert vec into triangle f and mutate it into 3 triangles.
     */
    void SplitFace(int faceIndex, int vecIndex);

    /**
     * Will rotate an edge within its bounding quadrilateral if
     * it doesn't meet the Delaunay criterion. Then it will fix the quad.
     *
     * @param edgeIndex
     * @param vecIndex
     */
    void SwapEdge(int edgeIndex);

    /**
     * Removes face and relevant edges. Cleans up to leave everything sanitized.
     * @param face
     */
    void RemoveFace(int face);
    /**
     *
     * @param v
     * @param t
     * @return Is v inside t?
     */
    bool IsInsideTriangle(Vec *v, Face t);

    bool IsInsideCircumcircle(Vec *v, Face t);
    int FindFace(int edgeIndex);

    //================================================================================
    // Private members
    //================================================================================

    vector<Vec>                 verts;
    vector<HalfEdge>            edges;
    set<int>                    faces; //indices into edges
};

#endif /* MESH_H_ */
