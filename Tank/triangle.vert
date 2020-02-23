#version 450 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 texCoor;

uniform mat4 projection;		// �任����
uniform mat4 model;				// ģ�;���
uniform mat4 prevModel;			// ��һ֡��ģ�;���
uniform mat4 turModel;			// ���̾���
uniform mat4 prevTur;			// ���̾�����һ֡
uniform float interpAlpha;		// ��ֵ����

uniform int turret;				// ����

void main()
{
	if (turret == 0) {
		vec4 cur = projection * model * vec4(aPos.x, aPos.y, 0.0f, 1.0);
		vec4 pre = projection * prevModel * vec4(aPos.x, aPos.y, 0.0f, 1.0);

		gl_Position = pre + (cur - pre) * interpAlpha;
	} else {
		vec4 cur = projection * model * turModel * vec4(aPos.x, aPos.y, 0.0f, 1.0);
		vec4 pre = projection * prevModel * prevTur * vec4(aPos.x, aPos.y, 0.0f, 1.0);

		gl_Position = pre + (cur - pre) * interpAlpha;
	}
	
	texCoor = aTex;
}