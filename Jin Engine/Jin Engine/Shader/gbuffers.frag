#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform sampler2D basicColorTexture;
layout(binding = 1) uniform sampler2D specularColorTexture;
layout(binding = 2) uniform sampler2D normalColorTexture;
layout(binding = 3) uniform sampler2D emissiveColorTexture;

layout(set = 0, binding = 4) uniform objectBuffer
{
	mat4 modelMat;
	mat4 InvTransposeMat;
};

layout(set = 0, binding = 5) uniform cameraBuffer
{
	mat4 viewMat;
	mat4 projMat;
	mat4 viewProjMat;
	mat4 InvViewProjMat;

	vec4 cameraWorldPos;
};



layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec3 fragTangent;
layout(location = 2) in vec3 fragBiTangent;
layout(location = 3) in vec3 fragNormal;
layout(location = 4) in vec2 fragUV;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outSpecColor;
layout(location = 2) out vec4 outNormal;
layout(location = 3) out vec4 outEmissiveColor;

void main()
{
    outColor = texture(basicColorTexture, fragUV);

	if(outColor.w < .1)
		discard;

	outSpecColor = texture(specularColorTexture, fragUV);

	outNormal = texture(normalColorTexture, fragUV);

	vec3 tangentNormal = outNormal.xyz;
	tangentNormal = normalize(tangentNormal * 2.0 - vec3(1.0));

	vec3 localNormal;	
	
	mat3 tbnMat;
	tbnMat[0] = fragTangent;
	tbnMat[1] = fragBiTangent;
	tbnMat[2] = fragNormal;

	localNormal = tbnMat * tangentNormal;	
	vec3 worldNormal = normalize( mat3(InvTransposeMat) * localNormal );

	outNormal = vec4(worldNormal, outNormal.w);

	//outNormal = vec4(fragTangent, outNormal.w);

	outEmissiveColor = texture(emissiveColorTexture, fragUV);
	outEmissiveColor.w = 1.0;
}