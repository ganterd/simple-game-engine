#pragma once

#include <sge/model/mesh.hpp>
#include <sge/model/aabb.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SGE
{
    class Frustum
    {
    private:
        GLuint vao, vbo;
        glm::vec4 mColour;

    public:
        Frustum(const glm::mat4& frustumMat, const glm::vec4& colour = glm::vec4(0.8f, 1.0f, 0.8f, 0.8f))
        {
            mColour = colour;

            glm::mat4 invFrustumMat = glm::inverse(frustumMat);
            glm::vec4 _near0 = invFrustumMat * glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f);
            glm::vec4 _near1 = invFrustumMat * glm::vec4(+1.0f, -1.0f, -1.0f, 1.0f);
            glm::vec4 _near2 = invFrustumMat * glm::vec4(-1.0f, +1.0f, -1.0f, 1.0f);
            glm::vec4 _near3 = invFrustumMat * glm::vec4(+1.0f, +1.0f, -1.0f, 1.0f);
            glm::vec4 _far0 = invFrustumMat * glm::vec4(-1.0f, -1.0f, +1.0f, 1.0f);
            glm::vec4 _far1 = invFrustumMat * glm::vec4(+1.0f, -1.0f, +1.0f, 1.0f);
            glm::vec4 _far2 = invFrustumMat * glm::vec4(-1.0f, +1.0f, +1.0f, 1.0f);
            glm::vec4 _far3 = invFrustumMat * glm::vec4(+1.0f, +1.0f, +1.0f, 1.0f);

            glm::vec3 near0 = glm::vec3(_near0) / _near0.w;
            glm::vec3 near1 = glm::vec3(_near1) / _near1.w;
            glm::vec3 near2 = glm::vec3(_near2) / _near2.w;
            glm::vec3 near3 = glm::vec3(_near3) / _near3.w;
            glm::vec3 far0 = glm::vec3(_far0) / _far0.w;
            glm::vec3 far1 = glm::vec3(_far1) / _far1.w;
            glm::vec3 far2 = glm::vec3(_far2) / _far2.w;
            glm::vec3 far3 = glm::vec3(_far3) / _far3.w;

            glm::vec3 vertices[] = {
                near0, near1,
                near0, near2,
                near1, near3,
                near2, near3,

                near0, far0,
                near1, far1,
                near2, far2,
                near3, far3,

                far0, far1,
                far0, far2,
                far1, far3,
                far2, far3
            };

            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (GLfloat*)vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        }

        ~Frustum()
        {
            glDeleteBuffers(1, &vbo);
            glDeleteVertexArrays(1, &vao);
        }

        void draw()
        {
            Shader* shader = ShaderManager::getCurrentShader();
            shader->setVariable("pointSize", 2.0f);
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
