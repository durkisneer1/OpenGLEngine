#version 450 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tex;
uniform vec3 uColor;
uniform bool useTexture;

void main()
{
    if (useTexture)
        FragColor = texture(tex, TexCoord);
    else
        FragColor = vec4(uColor, 1.0);
}
