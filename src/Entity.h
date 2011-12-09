/*
 * Entity.h
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

#ifndef ENTITY_H_
#define ENTITY_H_

class Renderer;

enum class EntityType{
    UNDEFINED = 0,
    MESH
};

/**
 *
 * An entity is something that the Renderer knows how to draw based on its type.
 *
 */
class Entity {
public:
    Entity();
    const EntityType GetType() const { return type; }
    virtual ~Entity();
protected:
    EntityType type;
    Renderer *renderer;
};

#endif /* ENTITY_H_ */
