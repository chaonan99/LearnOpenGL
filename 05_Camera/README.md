# Camera
* A camera is actually **a coordinate system with 3 perpendicular unit axes with the camera's position as the origin.**
* To define a camera in OpenGL
	* Define camera position
		```c
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		```
	* Define camera direction by specifying a target
		```c
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
		```
	* Get right vector (x-axis in camera space) by specifying an up vector
		```
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		```
	* Get up vector
		```
		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
		```

## Look At Matrix
* A great thing about matrices is that if you define a coordinate space using 3 perpendicular (or non-linear) axes you can create a matrix with those 3 axes plus a translation vector and you can transform any vector to that coordinate space by multiplying it with this matrix.
	![equation](http://latex.codecogs.com/svg.latex?LookAt%20%3D%20%5Cbegin%7Bbmatrix%7D%20R_x%20%26%20R_y%20%26%20R_z%20%26%200%20%5C%5C%20U_x%20%26%20U_y%20%26%20U_z%20%26%200%20%5C%5C%20D_x%20%26%20D_y%20%26%20D_z%20%26%200%20%5C%5C%200%20%26%200%20%26%200%20%20%26%201%20%5Cend%7Bbmatrix%7D%20%2A%20%5Cbegin%7Bbmatrix%7D%201%20%26%200%20%26%200%20%26%20-P_x%20%5C%5C%200%20%26%201%20%26%200%20%26%20-P_y%20%5C%5C%200%20%26%200%20%26%201%20%26%20-P_z%20%5C%5C%200%20%26%200%20%26%200%20%20%26%201%20%5Cend%7Bbmatrix%7D)

## Euler Angles
* Pitch, yaw and roll
	![euler](http://www.learnopengl.com/img/getting-started/camera_pitch_yaw_roll.png)
