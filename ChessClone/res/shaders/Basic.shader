#shader vertex
#version 330 core

layout(location=0) in vec4 position;

void main()
{
	gl_Position=position;
}

#shader blackFragment
#version 330 core

layout(location=0) out vec4 color;

void main()
{
	color = vec4(0.28, 0.12, 0.0, 1.0);
};

#shader whiteFragment
#version 330 core

layout(location=0) out vec4 color;

void main()
{
	color = vec4(0.6, 0.48, 0.3, 1.0);
};
