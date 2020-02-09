#version 450 core
layout (location = 0) in vec2 aPos;

uniform mat4 projection;		// �任����
uniform mat4 model;				// ģ�;���
uniform mat4 prevModel;			// ��һ֡��ģ�;���
uniform float interpAlpha;		// ��ֵ����

void main()
{
	vec4 cur = projection * model * vec4(aPos.x, aPos.y, 0.0f, 1.0);
	vec4 pre = projection * prevModel * vec4(aPos.x, aPos.y, 0.0f, 1.0);

    gl_Position = pre + (cur - pre) * interpAlpha;
}