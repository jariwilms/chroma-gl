#version 460 core

#ifdef VULKAN
    #define INSTANCE_ID gl_InstanceIndex
#else
    #define INSTANCE_ID gl_InstanceID
#endif

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

layout(location = 0) out vec3 fragColor;

void main() {
    float offset        = (float(INSTANCE_ID) - 4.5) * 0.1; 
    vec2  instancePos   = aPos + vec2(offset, 0.0);
    vec3  instanceColor = aColor * (0.3 + 0.7 * (float(INSTANCE_ID) / 9.0));
    
    gl_Position = vec4(instancePos, 0.0, 1.0);
    fragColor = instanceColor;
}