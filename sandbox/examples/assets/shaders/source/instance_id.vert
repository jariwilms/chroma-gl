#version 460 core

#ifdef VULKAN
    #define INSTANCE_ID gl_InstanceIndex
#else
    #define INSTANCE_ID gl_InstanceID
#endif

layout(location = 0) in  vec2 a_Position;
layout(location = 1) in  vec3 a_Color;

layout(location = 0) out vec3 v_Color;

void main()
{
    float offset           = (float(INSTANCE_ID) - 4.5) * 0.1;
    vec2  instancePosition = a_Position + vec2(offset, 0.0);
    vec3  instanceColor    = a_Color * (0.3 + 0.7 * (float(INSTANCE_ID) / 9.0));
    
    gl_Position = vec4(instancePosition, 0.0, 1.0);
    v_Color = instanceColor;
}