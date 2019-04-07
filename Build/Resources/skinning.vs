
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;


// Vertex Shader

void main(void)
{
	// Calculate the position of the vertex against the world, view, and projection matrices.
	//vec4 pos = vec4(inputPosition, 1.0f);
	vec4 pos = vec4(0, 0, 0, 1.0f);

	vec4 temp = vec4(inputPosition, 1.0f);
	vec3 norm = vec3(0,0,0);
	for(int i = 0; i < 4; ++i)
	{
		pos  += boneWeights[i] * (temp   * skin.mat[int(boneIndices[i])]);
		norm += boneWeights[i] * (normal * mat3(skin.mat[int(boneIndices[i])]));
	}
	 
	gl_Position = sm.projectionMatrix   * (modelViewMatrix * vec4(pos.xyz, 1.0f));
	outNormal	= mat3(modelViewMatrix) * norm;

	outNormal = normalize(outNormal);
}
