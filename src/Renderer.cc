/*
 * Renderer.cc
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

#include "Renderer.h"
#include "Mesh.h"

Renderer renderer;

Renderer::Renderer() {

}

void Renderer::Remove(const Entity * entity) {
    entities.erase(entity);
}

void Renderer::Push(const Entity * entity) {
    entities.insert(entity);
}

void Renderer::Render() const {
    for(const Entity *e : entities) {
        if(e->GetType() == EntityType::MESH) {
            auto *faces = ((Mesh *) e)->GetFaces();
            const vector<HalfEdge> * edges = ((Mesh *) e)->GetEdges();
            const vector<Vec> * verts = ((Mesh *) e)->GetVerts();
            glColor3d(0,0,0);
            glBegin(GL_TRIANGLES);
            //for(int i = 0; i < faces->size(); ++i) {
            for(const int fi : *faces) {
                //const HalfEdge *e1 = &(edges->at(*(faces->find(i))));
                const HalfEdge *e1 = &(edges->at(fi));
                const HalfEdge *e2 = &(edges->at(e1->next));
                const HalfEdge *e3 = &(edges->at(e2->next));

                const Vec *a = &(verts->at(e1->point));
                const Vec *b = &(verts->at(e2->point));
                const Vec *c = &(verts->at(e3->point));

                glVertex2d(a->x,a->y);
                glVertex2d(b->x,b->y);
                glVertex2d(c->x,c->y);
            }
            glEnd();

            glColor3d(1,0,0);
            glBegin(GL_POINTS);
            for(Vec const v : *(verts)) {
                glVertex2d(v.x, v.y);
            }
            glEnd();
        }
    }
}

