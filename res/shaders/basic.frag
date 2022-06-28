#version 330 core
// Lighting and texture info from vertex shader
in float fLighting;
in vec3 fTexInfo;

// Out fragment color
out vec4 FragColor;

// The texture atlas
uniform sampler2D textureAtlas;


void main() {
	// Coordinate of the texture on the atlas
	vec2 atlasCoord = vec2(int(fTexInfo.z) % 8, int(fTexInfo.z) / 8);

	// This is a vector that stores the lighting values for multiplication, since i dont want to multiply alpha
	// It also makes it really easy to add rgb lighting if i want to later

	vec4 lighting = vec4(fLighting, fLighting, fLighting, 1);

	// To turn the coordinate of the texture on the atlas to be the actual texture:
	// You add the texCoord to it
	// Then multiply it by the size of each texture
	// Then divide it by (texture size * amount of textures)

	// Multiplied by the lighting value
	FragColor = lighting * texture(textureAtlas, (fTexInfo.xy + fTexInfo.z) * 16 / 128);
	
	// Discard the fragment if it's transparent (No support for semitransparency i think...)
	if (FragColor.w == 0) { discard; }
}