#version 450 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 texCoor;

uniform mat4 projection;		// 变换矩阵
uniform mat4 model;				// 模型矩阵
uniform mat4 prevModel;			// 上一帧的模型矩阵
uniform mat4 turModel;			// 底盘矩阵
uniform mat4 prevTur;			// 底盘矩阵上一帧
uniform float interpAlpha;		// 插值比率

uniform int turret;				// 底盘

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