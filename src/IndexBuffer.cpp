#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int* data, unsigned int count) :m_Count(count){

    assert(sizeof(unsigned int)==sizeof(GLuint));

    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*4, data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//update data??

IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::updateBuffer(unsigned int* data, unsigned int count) const {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*4, data, GL_DYNAMIC_DRAW);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//pass in a bitset to tell what faces to render
// void IndexBuffer::modifyData(std::bitset<6> faces) {
    
//     int d_count = 0;
//     for(int i=0; i<6; i++){
//         if(faces[i]){
//             d_count++;
//         }
//     }
//     // d_count*=6;
//     int data[d_count*6];

//     // std::cout<<"CountBitset: "<<d_count<<std::endl;

//     Unbind();
//     glDeleteBuffers(1, &m_rendererID);
//     glGenBuffers(1, &m_rendererID);
//     Bind();

//     int c_size = 0;

//     // // using bitset push what faces to render
//     for(int i=0; i<6; i++){
//         if(faces[i]){
//             data[c_size] = i*4;
//             data[c_size+1] = i*4+1;
//             data[c_size+2] = i*4+3;
//             data[c_size+3] = i*4+1;
//             data[c_size+4] = i*4+2;
//             data[c_size+5] = i*4+3;
//             c_size+=6;
//         }
//     }

//     // std::cout<<sizeof(data)<<" ";

//     // for(int i=0; i<c_size; i++){
//     //     std::cout<<data[i]<<", ";
//     // }
//     // std::cout<<"<CUT>";

//     int count = sizeof(data);

//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, &data, GL_STATIC_DRAW);
//     Unbind();
// }