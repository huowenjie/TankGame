#version 450 core
layout (location = 0) in vec2 aPos;

uniform mat4 projection;		// 变换矩阵
uniform mat4 model;				// 模型矩阵
uniform mat4 prevModel;			// 上一帧的模型矩阵
uniform float interpAlpha;		// 插值比率

void main()
{
	vec4 cur = projection * model * vec4(aPos.x, aPos.y, 0.0f, 1.0);
	vec4 pre = projection * prevModel * vec4(aPos.x, aPos.y, 0.0f, 1.0);

    gl_Position = pre + (cur - pre) * interpAlpha;
}