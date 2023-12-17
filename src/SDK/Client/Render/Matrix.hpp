#pragma once

#include <glm/mat4x4.hpp>

#include "../../../Utils/Utils.hpp"

// Original made by og Horion devs, translated to glm stuff by Intop, NOT skidded from continued

struct Matrix {
public:
	glm::mat4x4 matrix;

	inline Matrix correct() const {
		Matrix ret;
		ret.matrix = glm::transpose(this->matrix);
		return ret;
	}

	inline bool OWorldToScreen(Vec3<float> origin, Vec3<float> pos, Vec2<float>& screen, Matrix projectionMatrix, Vec2<float> clientUIScreenSize) {
		pos = pos.sub(origin);

		glm::vec4 transformedPos = this->matrix * glm::vec4(pos.x, pos.y, pos.z, 1.0f);

		if (transformedPos.z > 0)
			return false;

		float mX = clientUIScreenSize.x / 2.0f;
		float mY = clientUIScreenSize.y / 2.0f;

		screen.x = mX + (mX * transformedPos.x / -transformedPos.z * projectionMatrix.matrix[0][0]);
		screen.y = mY - (mY * transformedPos.y / -transformedPos.z * projectionMatrix.matrix[1][1]);

		return true;
	}
};
