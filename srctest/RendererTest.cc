/*
 * RendererTest.cc
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
 */



#include <gtest/gtest.h>
#include <Renderer.h>
#include <Mesh.h>

namespace {

// The fixture for testing class Foo.
class RendererTest: public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    RendererTest() {

    }

    virtual ~RendererTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
        renderer = new Renderer;
        mesh = new Mesh;
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
        delete renderer;
        delete mesh;
    }
    Renderer *renderer;
    Mesh *mesh;
};

/**
 * Check that the renderer doesn't accept the same object twice.
 */

TEST_F(RendererTest, DoublePush) {
    renderer->Push(static_cast<Entity*>(mesh));
    renderer->Push(static_cast<Entity*>(mesh));
    ASSERT_TRUE(renderer->GetNumEntities() == 1);
}
TEST_F(RendererTest, DoubleDelete) {
    renderer->Push(mesh);
    renderer->Remove(mesh);
    ASSERT_TRUE(renderer->GetNumEntities() == 0);
    ASSERT_NO_FATAL_FAILURE(renderer->Remove(mesh));
    ASSERT_TRUE(renderer->GetNumEntities() == 0);
}

}
