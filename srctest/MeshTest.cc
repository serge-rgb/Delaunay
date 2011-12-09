/*
 * MeshTest.cc
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

#include <Mesh.h>
#include <gtest/gtest.h>
#include <tr1/random.h>
#include <random>
#include <time.h>
#include <Interface/Linux.h>

class MeshTest: public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    MeshTest() {
        // You can do set-up work for each test here.
        srand(time(NULL));
    }

    virtual ~MeshTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
        mesh = new Mesh;
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
        delete mesh;
    }

    // Objects declared here can be used by all tests in the test case for Foo.
    Mesh *mesh;

};

extern Vec ToBarycentric2d(Vec*,Vec*,Vec*,Vec*);

/**
 * A lot of random points in the subset of the plane that we will be using
 * and a check for contention within the generated bounding triangle.
 */
TEST_F(MeshTest, BoundingTriangle) {
    vector<Vec> vecs;
    Mesh mesh;
    for(int i = 0; i < 10 * 10 * 10 * 10; ++i){
        double x =  (double)W * (static_cast<double>(rand()) / RAND_MAX);
        double y =  (double)H * (static_cast<double>(rand()) / RAND_MAX);
        mesh.verts.push_back(Vec(x,y));
    }
    vector<Vec> tri = mesh.GetBoundingTriangle();
    for(auto v : mesh.verts) {
        Vec bar = ToBarycentric2d(&v, &tri[0], &tri[1], &tri[2]);
        ASSERT_TRUE(bar.x <= 1 && bar.y <= 1 && bar.z <= 1 && bar.x >= 0 && bar.y >= 0 && bar.z >= 0)
            << "Barycentric: " << bar << " Vector: " << v <<  endl;
    }

}
