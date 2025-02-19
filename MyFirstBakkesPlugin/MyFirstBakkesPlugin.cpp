#include "pch.h"
#include "MyFirstBakkesPlugin.h"


BAKKESMOD_PLUGIN(MyFirstBakkesPlugin, "This is a plugin description!", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
bool coolEnabled = false;

void MyFirstBakkesPlugin::onLoad() {
	// This line is required for LOG to work and must be before any use of LOG()
	_globalCvarManager = cvarManager;
	LOG("Hello I'm the first real Plugin B) Im loaded");

	cvarManager->registerNotifier("MyBallOnTop", [this](std::vector<std::string> args) {
		ballOnTop();
		}, "", PERMISSION_ALL);

	cvarManager->registerCvar("cool_enabled", "0", "Enable Cool", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		coolEnabled = cvar.getBoolValue();
			});

	cvarManager->registerCvar("cool_distance", "200.0", "Distance to place the ball above");
}

void MyFirstBakkesPlugin::onUnload() {
	LOG("I was too cool for this world B'(");
}

void MyFirstBakkesPlugin::ballOnTop() {
	// Get the game wrapper and check if we are in freeplay
	if (!gameWrapper->IsInFreeplay()) { return; }
	ServerWrapper server = gameWrapper->GetGameEventAsServer();
	if (!server) { return; }

	if(!coolEnabled) { return; }

	CVarWrapper distanceCVar = cvarManager->getCvar("cool_distance");
	if (!distanceCVar) { return; }
	float distance = distanceCVar.getFloatValue();

	// Get the ball and the car and check if they exist
	BallWrapper ball = server.GetBall();
	if (!ball) { return; }
	CarWrapper car = gameWrapper->GetLocalCar();
	if (!car) { return; }

	// Set the ball's velocity to the car's velocity and set the ball's location to the car's location plus the ball's radius
	Vector carVelocity = car.GetVelocity();
	ball.SetVelocity(carVelocity);
	Vector carLocation = car.GetLocation();
	float ballRadius = ball.GetRadius();
	ball.SetLocation(carLocation + Vector(0, 0, ballRadius * 1.6));
}
