#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
#include "LoadHmap.h"
#include "GlobalDatas.h"

class Camera3 : public Camera
{
public:
	enum CAM_TYPE
    {
		LAND_CAM,
		AIR_CAM,
		TOTAL_NUM_CAM,
	};

    enum PLAYER_STATE
    {
        PS_CROUCH,
        PS_STAND,
        PS_PRONE,

        PS_MAX,
    };

	virtual void SetCameraType(CAM_TYPE sCameraType);
	virtual CAM_TYPE GetCameraType();

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
    Vector3 previousPosition;
    Vector3 cameraView;
    Vector3 walkingView;
    Vector3 nextPosition;

	Camera3();
	~Camera3();

	//Camera Update Functions
	virtual void cameraRotation(const double dt);
	virtual void cameraMovement(const double dt);

	//Basic camera functions
	//Rotation
	virtual void lookLeft(const double dt);
	virtual void lookRight(const double dt);
	virtual void lookUp(const double dt);
	virtual void lookDown(const double dt);

	// Advance camera functions
	virtual void cameraYaw(const double dt);
	virtual void cameraPitch(const double dt);
    virtual void updateCameraView(const double dt);

	// Camera Basic Functions
	virtual void Reset();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);

	//Update camera Status
	virtual void UpdateStatus(const unsigned char key);

private:
	CAM_TYPE sCameraType;

	//Jumping variables
	float jumpVel;
    float jumpAccel;
    float jumpMaxSpeed;

    //Walking Variables
    Vector3 walkingVel;

	// Pull the player towards the ground according to gravity
	bool isFalling;
	bool hasJumped;

	//What key is pressed
	bool myKeys[255];

	float currentWorldHeightY;

    bool isProning;
    bool isCrouching;

    float proningHeight;
    float currentHeight;
    float standingHeight;
    float crouchingHeight;

    double actionCooldownTime;
    double currentActionCooldown;
    
    float yawVelocity;
    float pitchVelocity;
};

#endif