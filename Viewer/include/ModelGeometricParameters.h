#ifndef _PARAM_
# define _PARAM_

class ModelGeometricParameters
{
public:
	ModelGeometricParameters() : 
		trans_x(0), trans_y(0), trans_z(0),
		rot_x(0), rot_y(0), rot_z(0),
		scale_x(1), scale_y(1), scale_z(1) {}


	float trans_x, trans_y, trans_z;
	float rot_x, rot_y, rot_z;
	float scale_x, scale_y, scale_z;
};

#endif
