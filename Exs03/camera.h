
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include "vecspace.h"

namespace enzosys
{

	class Camera
	{
	public:
		Camera(void)
		{
			cameraSpeed = 0.005f;
			position.reset(0.764331460f, -1.66760659f, 0.642456770);
			forwardVec.reset(-0.398769796f, 0.763009906f, -0.508720219f);
			rightVec.reset(0.886262059f, 0.463184059f, 0.000000000f);
			upVec.reset(-0.235630989f, 0.450859368f, 0.860931039f);
		}

		void transformOrientation(void)
		{
			gluLookAt(0, 0, 0, forwardVec.x, forwardVec.y, forwardVec.z, upVec.x, upVec.y, upVec.z);
		}

		void transformTranslation(void)
		{
			glTranslatef(-position.x, -position.y, -position.z);
		}

		// points the camera at the given point in 3d space
		void pointing(vec3f target)
		{
			vec3f temp;
			vec3f up(0.0f, 0.0f, 1.0f);

			forwardVec.copy(target);
			forwardVec.minus(position);
			forwardVec.normalize();
			forwardVec.rotate(up, temp, -1.57079632679f);

			temp.z = 0;
			temp.normalize();
			rightVec.copy(temp);
			forwardVec.rotate(rightVec, temp, 1.57079632679f);

			upVec.copy(temp);
		}

		// move the camera forward
		void forward(void)
		{
			// make a movement vector the right speed facing the forward direction
			vec3f vec;
			vec.copy(forwardVec);
			vec.multiply(cameraSpeed);

			// add the movement vec to the position vec
			position.add(vec);
		}

		// move the camera backward
		void backward(void)
		{
			// make a movement vector the right speed facing the backward direction
			vec3f vec;
			vec.copy(forwardVec);
			vec.multiply(-cameraSpeed); // -cameraSpeed for backwards

			// add the movement vec to the position vec
			position.add(vec);
		}

		// strafe left
		void left(void)
		{
			// make a movement vector the right speed facing the left direction
			vec3f vec;
			vec.copy(rightVec);
			vec.multiply(-cameraSpeed); // -cameraSpeed for left

			// add the movement vec to the position vec
			position.add(vec);
		}

		// strafe right
		void right(void)
		{
			// make a movement vector the right speed facing the right direction
			vec3f vec;
			vec.copy(rightVec);
			vec.multiply(cameraSpeed);

			// add the movement vec to the position vec
			position.add(vec);
		}

	private:
		// Vector pointing forward
		vec3f forwardVec;

		// Vector pointing right
		vec3f rightVec;

		// Vector pointing upwards
		vec3f upVec;

		// Position vector
		vec3f position;

		// the camera speed
		float cameraSpeed;
	};

}

#endif // _CAMERA_H_
