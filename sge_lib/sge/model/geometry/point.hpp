#pragma once

#include <sge/model/mesh.hpp>
#include <sge/model/aabb.hpp>
#include <sge/graphics/shaders/Shader.hpp>
#include <sge/graphics/shaders/ShaderManager.hpp>

namespace SGE
{
    class Point
    {
    private:
        GLuint vao, vbo;
        float mPointSize;
        glm::vec4 mColour;

    public:
        Point(
            const glm::vec3& p,
            const glm::vec4& colour = glm::vec4(1.0f, 1.0f, 1.0f, 0.8f),
            float size = 10.0f
        ){
            mPointSize = size;
            mColour = colour;
            float vertices[] = {
                p.x, p.y, p.z
            };

            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        }

        ~Point()
        {
            glDeleteBuffers(1, &vbo);
            glDeleteVertexArrays(1, &vao);
        }

        void draw()
        {
            Shader* shader = ShaderManager::getCurrentShader();
            shader->setVariable("debugColour", mColour);
            shader->setVariable("pointSize", mPointSize);

            glBindVertexArray(vao);
            glEnable(GL_PROGRAM_POINT_SIZE);
            glEnable(GL_POINT_SMOOTH);
            glDrawArrays(GL_POINTS, 0, 1);
            glBindVertexArray(0);
        }
    };
}
