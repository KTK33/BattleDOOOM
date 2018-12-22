#pragma once
#include "../Actor.h"
#include "../Player/Player.h"

class Camera : public Actor {
public:
	Camera(IWorld& world,Vector3& position);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

protected:
	void CameraMove();
	void CameraCalculation(Vector3 pos);

private:
	//ÉvÉåÉCÉÑÅ[
	Actor* player_;

	Vector3 target_{ 0.0f,0.0f,0.0f };

	float Angle;
	float CAMERA_ANGLE_SPEED{ 3.0f };
	float CAMERA_LOOK_AT_HEIGHT{ 400.0f };
	float CAMERA_LOOK_AT_DISTANCE{ 2150.0f };
	float CameraHAngle;
	float CameraVAngle;

	bool Moveflag;
	Vector3 m_pos;
};