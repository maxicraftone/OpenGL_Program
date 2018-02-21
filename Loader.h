#ifndef LOADER_H
#define LOADER_H

unsigned int createAndBindVAO();
void storeDataInAttributeList(unsigned int attributeID, unsigned int coordinateSize, float data[], unsigned int datasize, unsigned int step, unsigned int skip);
unsigned int createIndicesBuffer(unsigned int indices[], unsigned int datasize);
void bindIndicesBuffer(unsigned int vboID);
void unbindVAO();
void bindTexture(unsigned int texture, unsigned int textureBank);
void enableAttribs(unsigned int from = 0, unsigned int to = 0);
void disableAttribs(unsigned int from = 0, unsigned int to = 0);
unsigned int loadDefaultTexture(const char *filePath);
void cleanUp();

#endif