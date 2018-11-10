#ifndef _TRANSFORM_MAT_
# define _TRANSFORM_MAT_

class TransformationMatrices
{
public:
	TransformationMatrices()
	{
		glm::mat4x4 _scaleMatrix
		{	1	,  0	,  0	,  0,
			0	,  1	,  0	,  0,
			0	,  0	,  1	,  0,
			0	,  0	,  0	,  1 };

		glm::mat4x4 _translationMatrix
		{	1	,	0	,	0	,	0,
			0	,	1	,	0	,	0,
			0	,	0	,	1	,	0,
			0	,	0	,	0	,	1 };

		glm::mat4x4 _rotataionXmatrix
		{	1	,	0	,	0	,	0,
			0	,	1	,	0	,	0,
			0	,	0	,	1	,	0,
			0	,	0	,	0	,	1 };

		glm::mat4x4 _rotataionYmatrix
		{	1	,	0	,	0	,	0,
			0	,	1	,	0	,	0,
			0	,	0	,	1	,	0,
			0	,	0	,	0	,	1 };


		glm::mat4x4 _rotataionZmatrix
		{	1	,	0	,	0	,	0,
			0	,	1	,	0	,	0,
			0	,	0	,	1	,	0,
			0	,	0	,	0	,	1 };

		scaleMatrix = _scaleMatrix;
		rotataionXmatrix = _rotataionXmatrix;
		rotataionYmatrix = _rotataionYmatrix;
		rotataionZmatrix = _rotataionZmatrix;
		translationMatrix = _translationMatrix;
	}

	glm::mat4x4 scaleMatrix, translationMatrix, rotataionXmatrix, rotataionYmatrix, rotataionZmatrix;
};

#endif
