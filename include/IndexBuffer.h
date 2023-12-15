#pragma once
#include "Macros.h"
#include <bitset>

class IndexBuffer{
    private:
        unsigned int m_rendererID;
        unsigned int m_Count;
    public:
        IndexBuffer(unsigned int* data, unsigned int count);
        ~IndexBuffer();

        void updateBuffer(unsigned int* data, unsigned int count) const;
        void Bind() const;
        void Unbind() const;

        inline unsigned int getCount() const { return m_Count; }
        // void modifyData(std::bitset<6> faces);
};