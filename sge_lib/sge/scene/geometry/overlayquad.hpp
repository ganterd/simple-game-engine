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
                -1.0f,  1.0f,
                 1.0f, 1.0f,
                 1.0f, -1.0f,

                 -1.0f,  1.0f,
                 1.0f, -1.0f,
                 -1.0f, -1.0f,
            };

            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
    		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        }

        void draw()
        {
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    };
}

#endif /* end of include guard: SGE_GEOMETRY_OVERLAY_QUAD */
