#include "catch.hpp"
#include <core/types.hpp>
#include <core/primitives/triangle.hpp>
#include <core/primitives/quad.hpp>
#include <array>

Triangle generate_triangle(const std::array<float, 9>& vertices) {
    Mesh* m = new Mesh();
    for (int i = 0; i < 9; i += 3) {
        Vertex v;
        v.position = {vertices[i], vertices[i + 1], vertices[i + 2]};
        m->vertices.push_back(v);
    }
    auto& verts = m->vertices;
    vec3<float> normal = (verts[1].position - verts[0].position)
        .cross(verts[2].position - verts[0].position)
        .norm();
    for (auto& v : verts)  v.normal = normal;
    m->indices = {0, 1, 2};
    m->count = 1;
    return Triangle(0, m, nullptr);
}

Quad generate_quad(const std::array<float, 12>& vertices) {
    Mesh* m = new Mesh();
    for (int i = 0; i < 12; i += 3) {
        Vertex v;
        v.position = {vertices[i], vertices[i + 1], vertices[i + 2]};
        m->vertices.push_back(v);
    }
    auto& verts = m->vertices;
    vec3<float> normal = (verts[2].position - verts[0].position)
        .cross(verts[1].position - verts[0].position)
        .norm();
    for (auto& v : verts)  v.normal = normal;
    m->indices = {0, 1, 2, 3};
    m->count = 1;
    return Quad(0, m, nullptr);
}


/***
 * TEST
 *     CASES 
 *            */


TEST_CASE("Ray-Triangle intersection") {
    Ray r;
    r.origin = {2, 2, 2};
    r.dir = {-1, -1, -1};
    auto triangle = generate_triangle({
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, -1.0, 0.0
    });
    auto intersection = triangle.intersect(r);
    REQUIRE( intersection.hit == true);
}

TEST_CASE("Ray-Quad intersection") {
    Ray r;
    r.origin = {2, 2, 2};
    r.dir = {-1, -1, -1};
    auto quad = generate_quad({
        -1.01, 0.99, 0.0,
        1.00, 0.99, 0.0,
        1.00, -1.04, 0.0,
        -0.99, -1.04, 0.0,
    });
    REQUIRE( quad.intersect(r).hit == true);
}