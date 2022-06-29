#version 330 core
layout (location = 0) in unsigned int inVertexData;

uniform mat4 projectionViewMatrix;

uniform ivec3 chunkPosition;

uniform unsigned int chunkSize;

out float fLighting;
out vec2 fTexCoords;
flat out unsigned int fTextureID;

vec2 texCoords[4] = vec2[4](
	vec2(1, 1),
	vec2(0, 1),
	vec2(0, 0),
	vec2(1, 0)
);

void main() {

    //// DECODING ////
	// BINARY                                   HEX
	// -------------------------------------------------
	// 000000000000 000 00 00000 00000 11111 -> 0x1F
	float x = float(inVertexData & 0x1Fu);
	// 000000000000 000 00 00000 11111 00000 -> 0x3E0
	float y = float((inVertexData & 0x3E0u) >> 5u);
	// 000000000000 000 00 11111 00000 00000 -> 0x7C00
	float z = float((inVertexData & 0x7C00u) >> 10u);
	
	
	// 000000000000 000 11 00000 00000 00000 -> 0x18000
	uint index = (inVertexData & 0x18000u) >> 15u;
	// 111111111111 000 00 00000 00000 00000    [& not needed]
	uint tex = inVertexData >> 20u;
	
	// fTexInfo is a vec3 containing the texture coordinates (the corners) and the index of the texture
	// texCoords is an array of vec2s that stores each possible corner ( (0, 0), (1, 0), (0, 1), (1, 1) )
	fTexCoords = texCoords[index];
	fTextureID = tex;
	// TODO : Maybe change texture (seen above) to be the precalculated 2d coords of the texture
	// Maybe I could even use a texture array instead. Who knows?
	
	
	// 000000000000 111 00 00000 00000 00000 -> 0xE0000
	// This is the simple lighting, it is what the texture is multiplied by
	// It ranges from 0.2 to 1.0, going up in 0.2s, 
	// I can just store it in 5 bits and divide it by 5 here [ Thanks hopson ;) ]
	fLighting = float((inVertexData & 0xE0000u) >> 17u) / 5.0;

	
    gl_Position = projectionViewMatrix * (vec4(x, y, z, 1.0) + vec4(chunkPosition * int(chunkSize), 1.0));
}