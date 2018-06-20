#ifndef SGE_GEOMETRY_OVERLAY_QUAD
#define SGE_GEOMETRY_OVERLAY_QUAD

#include <sge/model/Mesh.hpp>

namespace SGE
{
    class OverlayQuad
    {
    private:
        GLuint vao;
        GLuint vbo;

    public:
        OverlayQuad()
        {
            float vertices[] = {
                 0.0f,  0.5f, // Vertex 1 (X, Y)
                 0.5f, -0.5f, // Vertex 2 (X, Y)
                -0.5f, -0.5f  // Vertex 3 (X, Y)
            };

            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        }

        void draw()
        {
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
        }
    };
}

#endif /* end of include guard: SGE_GEOMETRY_OVERLAY_QUAD */
