#include "Renderer.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader){
    shader.Bind();
    va.Bind();
    //unbind ib and clear ib( define a function in IndexBuffer.h)
    //push vertices that matter
    //bind ib
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
