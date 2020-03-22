#version 450 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 texCoor;

uniform mat4 projection;		// �任����
uniform mat4 prevProj;			// ��һ֡�۲����

uniform mat4 model;				// ģ�;���
uniform mat4 prevModel;			// ��һ֡��ģ�;���

uniform float interpAlpha;		// ��ֵ����

void main()
{
	mat4 tmpModel = prevModel + (model - prevModel) * interpAlpha;
	mat4 tmpProj = prevProj + (projection - prevProj) * interpAlpha;

	gl_Position = tmpProj * tmpModel * vec4(aPos.x, aPos.y, 0.0, 1.0);

	texCoor = aTex;
}