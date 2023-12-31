#pragma once
#include <vector>
#include "Macros.h"

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    
    static unsigned int GetSizeOfType(unsigned int type){
        switch (type)
        {
            case GL_FLOAT         : return sizeof(GLfloat);
            case GL_UNSIGNED_INT  : return sizeof(GLuint);
            case GL_UNSIGNED_BYTE : return sizeof(GLbyte);
        }
        assert(false);
        return 0;
    }
};

class VertexBufferLayout{
    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
    public:
        VertexBufferLayout()
            :m_Stride(0) {};

        // template<typename T>
        // void Push(int count){
        //     static_assert(false);
        // }

        inline void Push(unsigned int type, unsigned int count){
            m_Elements.push_back({type, count, GL_FALSE});
            std::cout<<"These many Vertex BUffer Elements here - "<<m_Elements.size()<<std::endl;
            m_Stride+=count*VertexBufferElement::GetSizeOfType(type);
        }
        
        //inline void Push(unsigned int count){m_Elements.push_back({GL_FLOAT, count, GL_FALSE}); m_Stride+=count*VertexBufferElement::GetSizeOfType(GL_FLOAT);}
        inline const std::vector<VertexBufferElement> GetElements() const {return m_Elements;};
        inline unsigned int GetStride() const {return m_Stride;}
};

// template<> void VertexBufferLayout::Push<float>(unsigned int count){
//     m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
//     m_Stride+=count*VertexBufferElement::GetSizeOfType(GL_FLOAT);
// }

// template<> void VertexBufferLayout::Push<unsigned int>(unsigned int count){
//     m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
//     m_Stride+=count*VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
// }

// template<> void VertexBufferLayout::Push<unsigned char>(unsigned int count){
//     m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
//     m_Stride+=count*VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
// }
