#pragma once
#include "Macros.h"

class VertexBuffer{
    private:
        unsigned int m_rendererID;
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void Bind() const ;
        void Unbind() const ;
};