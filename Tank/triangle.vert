#version 450 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 texCoor;

uniform mat4 projection;		// 变换矩阵
uniform mat4 prevProj;			// 上一帧观察矩阵

uniform mat4 model;				// 模型矩阵
uniform mat4 prevModel;			// 上一帧的模型矩阵

uniform float interpAlpha;		// 插值比率

void main()
{
	mat4 tmpModel = prevModel + (model - prevModel) * interpAlpha;
	mat4 tmpProj = prevProj + (projection - prevProj) * interpAlpha;

	gl_Position = tmpProj * tmpModel * vec4(aPos.x, aPos.y, 0.0, 1.0);

	texCoor = aTex;
}