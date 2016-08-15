#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

//The default camera speed
static float CAMERA_SPEED = 150.f;
static const float CAM_ACC = 50.f;
static const float ROT_SPEED = 20.f;
static const float ROT_MAX_SPEED = 50.f;

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
    this->position = defaultPosition = pos;
    this->target = defaultTarget = target;
    this->cameraView = (target - position).Normalized();
    this->right = cameraView.Cross(up);
    this->right.y = 0;
    this->right.Normalize();
    this->up = defaultUp = this->right.Cross(cameraView).Normalized();
    this->walkingView = this->cameraView;

    //Initialise camera movement flags
    for (int i = 0; i < 255; ++i)
    {
        myKeys[i] = false;
    }

    //Initialise camera type
    sCameraType = LAND_CAM;

    //jumping Variables
    isFalling = false;
    jumpVel = 0.f;
    jumpAccel = 200.f;
    jumpMaxSpeed = 200.f;
    hasJumped = false;

    //Walking variables
    walkingVel = Vector3(0, 0, 0);

    previousPosition = defaultPosition;
    currentWorldHeightY = 0;

    yawVelocity = 0;
    pitchVelocity = 0; 

    position.y = 100.f;

    isProning = false;
    isCrouching = false;

    proningHeight = 10.f;
    standingHeight = 30.f;
    crouchingHeight = 15.f;
    currentHeight = standingHeight;

    nextPosition = position;
}

void Camera3::Update(double dt)
{

}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

//Basic Functions
void Camera3::lookLeft(const double dt)
{
    yawVelocity += -Application::camera_yaw * ROT_SPEED * dt;
	if (yawVelocity > ROT_MAX_SPEED)
	{
		yawVelocity = ROT_MAX_SPEED;
	}
	
}

void Camera3::lookRight(const double dt)
{
    yawVelocity += -Application::camera_yaw * ROT_SPEED * dt;
	if (yawVelocity < -ROT_MAX_SPEED)
	{
		yawVelocity = -ROT_MAX_SPEED;

	}
}

void Camera3::lookUp(const double dt)
{
	pitchVelocity += -Application::camera_pitch * ROT_SPEED * dt;

	if (pitchVelocity > ROT_MAX_SPEED)
	{
		pitchVelocity = ROT_MAX_SPEED;
	}
}

void Camera3::lookDown(const double dt)
{
	pitchVelocity += -Application::camera_pitch * ROT_SPEED * dt;
	if (pitchVelocity < -ROT_MAX_SPEED)
	{
		pitchVelocity = -ROT_MAX_SPEED;
	}
}

//Advance Functions
void Camera3::updateCameraView(const double dt)
{
	if (Application::camera_yaw == 0)
	{
		yawVelocity *= 0.5f;
	}

	if (Application::camera_pitch == 0)
	{
		pitchVelocity *= 0.5f;
	}
	

	//yaw rotation
	{
		Mtx44 rotation;
		rotation.SetToRotation(yawVelocity, 0, 1, 0);
		cameraView = rotation * cameraView;
		right = cameraView.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(cameraView).Normalize();
	}

	//pitch rotation
	{
		right = cameraView.Cross(up);
		up = right.Cross(cameraView).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitchVelocity, right.x, right.y, right.z);

		Vector3 nextView = rotation * cameraView;

		if (nextView.y >= -0.95 && nextView.y <= 0.95)
		{
			cameraView = nextView;
		}
	}
}

void Camera3::cameraYaw(const double dt)
{
	if (Application::camera_yaw < 0)
	{
		lookLeft(dt);
	}
	else if (Application::camera_yaw > 0)
	{
		lookRight(dt);
	}
}

void Camera3::cameraPitch(const double dt)
{
	if (Application::camera_pitch < 0)
	{
		lookUp(dt);
	}
	else if (Application::camera_pitch > 0)
	{
		lookDown(dt);
	}
}

//Camera Control Functions
void Camera3::cameraRotation(double dt)
{
	if (Application::camera_yaw != 0)
	{
		cameraYaw(dt);
	}
    if (Application::camera_pitch != 0)
    {
        cameraPitch(dt);
    }
    updateCameraView(dt);
}

void Camera3::cameraMovement(const double dt)
{
	if (myKeys['w'] == true)
	{
        walkingVel += CAM_ACC * walkingView;
		myKeys['w'] = false;
	}

	if (myKeys['a'] == true)
	{
        Vector3 walkingRight = right;
        walkingRight.y = 0;
        walkingRight.Normalize();
        walkingVel += CAM_ACC * -walkingRight;
		myKeys['a'] = false;
	}

	if (myKeys['s'] == true)
	{
        walkingVel += CAM_ACC * -walkingView;
		myKeys['s'] = false;
	}

	if (myKeys['d'] == true)
	{
        Vector3 walkingRight = right;
        walkingRight.y = 0;
        walkingRight.Normalize();
        walkingVel += CAM_ACC * walkingRight;
		myKeys['d'] = false;
	}

	if (myKeys[VK_SPACE] == true && !isProning)
    {
        myKeys[VK_SPACE] = false;
	}

    if (myKeys[VK_LCONTROL] == true)
    {
        isCrouching = true;
        myKeys[VK_LCONTROL] = false;
    }
    else
    {
        isCrouching = false;
    }

    if (myKeys[VK_LSHIFT] == true)
    {
        isProning = true;
        myKeys[VK_LSHIFT] = false;
    }
    else
    {
        isProning = false;
    }
}

//Others
void Camera3::UpdateStatus(const unsigned char key)
{
	myKeys[key] = true;
}

void Camera3::SetCameraType(CAM_TYPE sCameraType)
{
	this->sCameraType = sCameraType;
}

Camera3::CAM_TYPE Camera3::GetCameraType()
{
	return this->sCameraType;
}

