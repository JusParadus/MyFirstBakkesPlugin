#include "pch.h"
#include "MyFirstBakkesPlugin.h"


BAKKESMOD_PLUGIN(MyFirstBakkesPlugin, "write a plugin description here", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void MyFirstBakkesPlugin::onLoad() {
	// This line is required for LOG to work and must be before any use of LOG()
	_globalCvarManager = cvarManager;
	LOG("Hello I'm the first real Plugin B) Im loaded");

	cvarManager->registerNotifier("MyBallOnTop", [this](std::vector<std::string> args) {
		ballOnTop();
		}, "", PERMISSION_ALL);

	//cvarManager->registerNotifier("my_aweseome_notifier", [&](std::vector<std::string> args) {
	//	LOG("Hello notifier!");
	//}, "", 0);

void MyFirstBakkesPlugin::onUnload() {
	LOG("I was too cool for this world B'(");
}

void MyFirstBakkesPlugin::ballOnTop() {
	// Get the game wrapper and check if we are in freeplay
	if (!gameWrapper->IsInFreeplay()) { return; }
	ServerWrapper server = gameWrapper->GetGameEventAsServer();
	if (!server) { return; }

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
	ball.SetLocation(carLocation + Vector(0, 0, ballRadius * 1.5));
}
