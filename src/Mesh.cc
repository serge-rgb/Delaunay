/*
 * Mesh.cc
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

#include "Mesh.h"

Mesh::Mesh() {
    type = EntityType::MESH;
}

const vector<HalfEdge> * Mesh::GetEdges() const {
    return &edges;
}

const vector<Vec> * Mesh::GetVerts() const {
    return &verts;
}

const set<int> * Mesh::GetFaces() const {
    return &faces;
}

//Todo: Sanity check.
/*static*/const Mesh Mesh::Generate(vector<Vec> *inVerts) {
    Mesh result;
    if (inVerts->size() <= 0) {
        return result;
    }
    // Copy all verts
    random_shuffle(inVerts->begin(),inVerts->end());
    result.verts = *inVerts;

    // Get bounding triangle
    vector<Vec> triangle = result.GetBoundingTriangle();

    // First face : ==========
    // Push the triangle. Will remove at the end
    for (Vec v : triangle) {
        result.verts.push_back(v);
    }

    // Add edges for the triangle.
    for (int i = result.verts.size() - 3; i < result.verts.size(); ++i) {
        HalfEdge e;
        e.point = i;
        result.edges.push_back(e);
    }

    // Adjacency for the triangle.
    for (int i = 0; i < result.edges.size(); ++i) {
        result.edges[i].next = (i + 1) % result.edges.size();
    }
    result.faces.insert(0);
    //========================

    // The last three points are the bounding triangle.

    // Split containing face for each point that is not part of the bounding triangle.
    for (int iVec = 0; iVec < result.verts.size() - 2; iVec++) {
        int iFace = result.GetContainingFace(iVec);
        result.SplitFace(iFace, iVec);
    }
    int nfaces = result.faces.size();
    set<int> todelete;
    for(int ei = 0; ei < result.edges.size(); ++ei) {
        auto edge = result.edges[ei];
        auto point = edge.point;
        auto size = result.verts.size();
        if(point == size-1 || point == size-2 || point == size-3) {
            auto face = result.FindFace(ei);
            todelete.insert(face);
        }
    }
    for(auto face : todelete) {
        result.RemoveFace(face);
    }
    // Pop triangle verts.
    for(int i = 0; i < 3; i++) {
        result.verts.pop_back();
    }
    return result;
}

/**
 * General idea:
 * a) Get the center of the bounding box of the points.
 * b) Get the farthest point from the center and calculate the distance. Add an epsilon.
 * c) Create a triangle that has two sides tangent to the circle derived from the center and the distance.
 *    One point is directly above. The edges are tangent at a 45 degree angle to make the math simpler.
 *    The other two points are symmetrical so we really only calculate one.
 */
vector<Vec> Mesh::GetBoundingTriangle() {
    const double epsilon = 0.5; //Used to make the triangle a little larger so that points don't intersect
    // Find the center.
    assert(verts.size() > 0);
    const Vec v0 = verts[0];
    double left = v0.x, right = v0.x, top = v0.y, bottom = v0.y;
    for (Vec v : verts) {
        if (v.x < left)
            left = v.x;
        if (v.x > right)
            right = v.x;
        if (v.y < bottom)
            bottom = v.y;
        if (v.y > top)
            top = v.y;
    }
    Vec center(left + (right - left) / 2, bottom + (top - bottom) / 2);

    // Find the vector farthest away from the center.
    // This is the radius of a circle that contains all points.
    double radius = 0;
    for (Vec v : verts) {
        double const newDist = center.Distance2d(v);
        if (newDist > radius) {
            radius = newDist;
        }
    }

    Vec b(center.x, center.y + radius + epsilon); // Top-most point in the triangle.
    double const sin45 = 0.707106781; // cos(pi/4) = sin(pi/4) = sqrt(2)/2

    // Direction vector from b to a.
    Vec dir = Vec(radius * sin45, radius * (sin45 - 1) - epsilon).Normalize();

    // The magnitude of the vector from b to a
    const double scale = -2 * (radius + epsilon) / dir.y;

    // Displacement in x from center to a.
    const double ax = b.x + dir.x * scale;

    Vec a(center.x + ax, center.y - radius - epsilon);

    // Vector c is reflected along the y axis at the center.
    Vec c(center.x - ax, a.y);

    vector<Vec> res;
    res.push_back(a);
    res.push_back(b);
    res.push_back(c);

    return res;
}

void Mesh::SplitFace(int faceIndex, int vecIndex) {
    // indices of the triangle
    const int e[3] = { faceIndex, edges[faceIndex].next, edges[edges[faceIndex].next].next };

    // Check if it is a triangle
    assert(edges[edges[e[2]].next] == edges[e[0]]);

    const int edgeI = edges.size();

    // Create 6 new half edges.
    for (int i = 0; i < 6; ++i) {
        edges.push_back(HalfEdge());
    }
    // new edges and their twins.
    const int n[3] = { edgeI, edgeI + 1, edgeI + 2 };
    const int tn[3] = { edgeI + 3, edgeI + 4, edgeI + 5 };

    for (int i = 0; i < 3; ++i) {
        edges[n[i]].point = edges[e[i]].point;
        edges[n[i]].next = e[(i + 1) % 3];
        edges[n[i]].twin = tn[i];

        edges[tn[i]].point = vecIndex;
        edges[tn[i]].next = n[(i + 2) % 3];
        edges[tn[i]].twin = n[i];

        edges[e[i]].next = tn[i];
    }
    // Add the extra faces.
    // e[0] is the original face. The other two sides now represent the new faces.
    faces.insert(e[1]);
    faces.insert(e[2]);
    for (int i = 0; i < 3; i++) {
        SwapEdge(e[i]);
    }
}

void Mesh::SwapEdge(int ei) {
    // Edge stack to avoid recursion.
    vector<int> stack;
    stack.push_back(ei);
    while(!stack.empty()){
        const int edgeIndex = stack.back();
        stack.pop_back();
        const int vecIndex = edges[edges[edgeIndex].next].point;
        HalfEdge *edge = &edges.at(edgeIndex);
        if (edge->twin == (int) HalfEdgeProperties::NO_TWIN) {
            return; // This edge is adjacent to the infinite face.
        }

        Vec origin = verts[edges[edge->next].point];
        Vec toChange = verts[edges[edges[edge->twin].next].point];

        // If it is inside a circumcircle then swap.
        if (IsInsideCircumcircle(&toChange, edge)) {
            int a, b, c, d;

            // The edge to swap and its twin
            HalfEdge *e = &edges.at(edgeIndex);
            HalfEdge *et = &edges[e->twin];

            // Get the two faces
            int f1, f2;
            f1 = FindFace(edgeIndex);
            f2 = FindFace(edges[edgeIndex].twin);

            //Set up the quad
            b = et->next;
            c = edges[b].next;
            d = e->next;
            a = edges[d].next;

            // Change the points of the edge (i.e. Swap)
            e->point = edges[d].point;
            et->point = edges[b].point;
            e->next = a;
            et->next = c;

            // Reflect change in topology
            edges[a].next = b;
            edges[b].next = edgeIndex;
            edges[c].next = d;
            edges[d].next = e->twin;

            // Change faces.
            faces.erase(f1);
            faces.erase(f2);
            faces.insert(edgeIndex);
            faces.insert(e->twin);

            // Add edges that now may be invalid (the quad.)
            stack.push_back(a);
            stack.push_back(b);
            stack.push_back(c);
            stack.push_back(d);
        }
    }
}

/*
 * O(n)
 * Doing a linear search is not an issue (profiling). Most of the time will not be spent here for any
 * reasonable number of points for this application.
 * Normal usage has ~16% time of mesh generation here, and ~76% in the SplitFace method.
 * (or ~27% vs 66% if we are using hash_set or unordered_set).
 */
int Mesh::GetContainingFace(int iVec) {
    Vec *vec = &verts[iVec];
    for (int iFace : faces) {
        HalfEdge *e1 = &edges[iFace];
        if (IsInsideTriangle(vec, e1)) {
            return iFace;
        }
    }
    //todo: Error.
    return -1;
}

// ====
// Helper functions to determine if a face is inside a triangle
inline double BarycentricDet(Vec *a, Vec *b, Vec *c) {
    return (b->x - a->x) * (c->y - a->y) - (c->x - a->x) * (b->y - a->y);
}

/**
 *
 * @param v
 * @param a, b, c Base triangle
 * @return v in barycentric coordinates relative to the triangle.
 */
inline Vec ToBarycentric2d(Vec *v, Vec *a, Vec *b, Vec *c) {
    Vec res;

    double A = BarycentricDet(a, b, c);
    if (A == 0) {
        cerr << "Called ToBarycentric2d with a triangle of area 0\n";
        exit(-1);
    }

    res.x = BarycentricDet(v, b, c) / A;
    res.y = BarycentricDet(a, b, v) / A;
    res.z = 1 - res.x - res.y;

    return res;
}
// ===

bool Mesh::IsInsideTriangle(Vec *v, Face f) {
    Vec *a, *b, *c;
    a = &verts[f->point];
    b = &verts[edges[f->next].point];
    c = &verts[edges[edges[f->next].next].point];
    Vec bar = ToBarycentric2d(v, a, b, c);
    return bar.x <= 1 && bar.y <= 1 && bar.z <= 1 && bar.x >= 0 && bar.y >= 0 && bar.z >= 0;
}

//todo: test IsInsideCircumcircle
bool Mesh::IsInsideCircumcircle(Vec *v, Face t) {
    // Compute the determinant..
    Vec *a = &verts[t->point];
    Vec *b = &verts[edges[t->next].point];
    Vec *c = &verts[edges[edges[t->next].next].point];


    const double t1 = a->x*a->x - v->x*v->x + a->y*a->y - v->y*v->y;
    const double t2 = b->x*b->x - v->x*v->x + b->y*b->y - v->y*v->y;
    const double t3 = c->x*c->x - v->x*v->x + c->y*c->y - v->y*v->y;

    const double det =
            (a->x - v->x) * ((b->y - v->y) * t3
            - (c->y - v->y) * t2)
            + (a->y - v->y) * ((c->x - v->x) * t2
            - (b->x - v->x) * t3)
            + t1 * ((b->x - v->x) * (c->y - v->y)
            - (b->y - v->y) * (c->x - v->x));

    return det > 0;

    // Other impl: ==============================================
    // 4x4 matrix determinant.
    const double a1 = a->x;
    const double a2 = b->x;
    const double a3 = c->x;
    const double a4 = v->x;

    const double b1 = a->y;
    const double b2 = b->y;
    const double b3 = c->y;
    const double b4 = v->y;

    const double c1 = a1*a1 + b1*b1;
    const double c2 = a2*a2 + b2*b2;
    const double c3 = a3*a3 + b3*b3;
    const double c4 = a4*a4 + b4*b4;

    const double d1 = 1, d2 = 1, d3 = 1, d4 = 1;

    const double det1 = a1*b2*c3*d4 - a1*b2*c4*d3 + a1*b3*c4*d2 - a1*b3*c2*d4
                     + a1*b4*c2*d3 - a1*b4*c3*d2 - a2*b3*c4*d1 + a2*b3*c1*d4
                     - a2*b4*c1*d3 + a2*b4*c3*d1 - a2*b1*c3*d4 + a2*b1*c4*d3
                     + a3*b4*c1*d2 - a3*b4*c2*d1 + a3*b1*c2*d4 - a3*b1*c4*d2
                     + a3*b2*c4*d1 - a3*b2*c1*d4 - a4*b1*c2*d3 + a4*b1*c3*d2
                     - a4*b2*c3*d1 + a4*b2*c1*d3 - a4*b3*c1*d2 + a4*b3*c2*d1;

    return det1 > 0;
}

void Mesh::RemoveFace(int face) {
    if(!faces.count(face)){
        return;
    }
    HalfEdge *edge = &edges[face];
    int ei = face;
    do{
        // Virtually erase the edge.
        if(edge->twin != (int) HalfEdgeProperties::NO_TWIN){
            edges[edge->twin].twin = (int)HalfEdgeProperties::NO_TWIN;
        }
        //edges[ei] = HalfEdge();
        ei = edges[ei].next;
    }while(ei!=face);
    faces.erase(face);

}

// O(logn)
int Mesh::FindFace(int edgeIndex) {
    int i = edgeIndex;
    do {
        if(faces.count(i)) {
            return i;
        }
        i = edges[i].next;
    } while(i!=edgeIndex);
    //todo: error
    return -1;
}
