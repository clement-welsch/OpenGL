#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLCheckError()
{
    while (GLenum error = glGetError())
    {

        std::cout << "[OpenGL Error] ";
        switch (error) {
        case GL_INVALID_ENUM:
            std::cout << "GL_INVALID_ENUM : An unacceptable value is specified for an enumerated argument.";
            break;
        case GL_INVALID_VALUE:
            std::cout << "GL_INVALID_OPERATION : A numeric argument is out of range.";
            break;
        case GL_INVALID_OPERATION:
            std::cout << "GL_INVALID_OPERATION : The specified operation is not allowed in the current state.";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION : The framebuffer object is not complete.";
            break;
        case GL_OUT_OF_MEMORY:
            std::cout << "GL_OUT_OF_MEMORY : There is not enough memory left to execute the command.";
            break;
        case GL_STACK_UNDERFLOW:
            std::cout << "GL_STACK_UNDERFLOW : An attempt has been made to perform an operation that would cause an internal stack to underflow.";
            break;
        case GL_STACK_OVERFLOW:
            std::cout << "GL_STACK_OVERFLOW : An attempt has been made to perform an operation that would cause an internal stack to overflow.";
            break;
        default:
            std::cout << "Unrecognized error" << error;
        }
        std::cout << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    glClearColor(0.49f, 0.49f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& _va, const IndexBuffer&  _ib, Shader& _shaderBasic) const
{
    _ib.Bind();
    _va.Bind();

    //1-Draw Triangles, lines from triangulation
    {
        _shaderBasic.Bind();
        GLCall(glPatchParameteri(GL_PATCH_VERTICES, 3));
        _shaderBasic.SetUniform4f("u_color", 0.73f, 0.73f, 0.78f, 1.0f);
        GLCall(glDrawElements(GL_TRIANGLES, _ib.GetCount(), GL_UNSIGNED_INT, nullptr));
        
        GLCall(glLineWidth(3.0f));
        _shaderBasic.SetUniform4f("u_color", 0.28f, 0.64f, 0.29f, 1.0f);
        GLCall(glDrawElements(GL_LINE_STRIP, _ib.GetCount(), GL_UNSIGNED_INT, nullptr));
        _shaderBasic.Unbind();
    }
    //3-Draw vertex
    {
        _shaderBasic.Bind();
        GLCall(glPointSize(15.0f));
        _shaderBasic.SetUniform4f("u_color", 0.13f, 0.3f, 1.0f, 0.13f);
        GLCall(glDrawElements(GL_POINTS, _ib.GetCount(), GL_UNSIGNED_INT, nullptr));
        _shaderBasic.Unbind();
    }
}
