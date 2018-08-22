#pragma once

#include <sge/model/mesh.hpp>
#include <sge/model/aabb.hpp>

namespace SGE
{
    class Box
    {
    private:
        GLuint vao, vbo;
        glm::vec4 mColour;

    public:
        Box(const AABB& aabb, const glm::vec4& colour = glm::vec4(0.8f, 1.0f, 0.8f, 0.8f))
        {
            mColour = colour;
            glm::vec3 min = aabb.min();
            glm::vec3 max = aabb.max();
            float vertices[] = {
                min.x, min.y, min.z, max.x, min.y, min.z,
                min.x, min.y, max.z, max.x, min.y, max.z,
                min.x, max.y, min.z, max.x, max.y, min.z,
                min.x, max.y, max.z, max.x, max.y, max.z,
                min.x, min.y, min.z, min.x, min.y, max.z,
                max.x, min.y, min.z, max.x, min.y, max.z,
                min.x, max.y, min.z, min.x, max.y, max.z,
                max.x, max.y, min.z, max.x, max.y, max.z,
                min.x, min.y, min.z, min.x, max.y, min.z,
                max.x, min.y, min.z, max.x, max.y, min.z,
                min.x, min.y, max.z, min.x, max.y, max.z,
                max.x, min.y, max.z, max.x, max.y, max.z
            };

            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        }

        ~Box()
        {
            glDeleteBuffers(1, &vbo);
            glDeleteVertexArrays(1, &vao);
        }

        void drawLines()
        {
            SubShader* shader = ShaderManager::getCurrentShader()->getCurrentSubShader();
            shader->setVariable("pointSize", 1.0f);
            shader->setVariable("debugColour", mColour);
            glBindVertexArray(vao);
            glEnable(GL_PROGRAM_POINT_SIZE);
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawArrays(GL_POINTS, 0, 24);
            glDrawArrays(GL_LINES, 0, 24);
            glBindVertexArray(0);
        }
    };
}
