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

	// Register the render function for the ingame overlay
	gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {
		Render(canvas);
		});
}

void MyFirstBakkesPlugin::onUnload() {
	LOG("I was too cool for this world B'(");
}

void MyFirstBakkesPlugin::ballOnTop() {
	// Get the game wrapper and check if we are in freeplay
	if (!gameWrapper->IsInFreeplay()) { return; }
	ServerWrapper server = gameWrapper->GetCurrentGameState();
	if (!server) { return; }

	if (!coolEnabled) { return; }

	CVarWrapper distanceCVar = cvarManager->getCvar("cool_distance");
	if (!distanceCVar) { return; }
	float distance = distanceCVar.getFloatValue();

	BallWrapper ball = server.GetBall();
	if (!ball) { return; }
	CarWrapper car = gameWrapper->GetLocalCar();
	if (!car) { return; }

	Vector carVelocity = car.GetVelocity();
	ball.SetVelocity(carVelocity);

	Vector carLocation = car.GetLocation();
	float ballRadius = ball.GetRadius();
	ball.SetLocation(carLocation + Vector{ 0, 0, distance });
}

// This function is called every tick and is used to render the ingame overlay
void MyFirstBakkesPlugin::Render(CanvasWrapper canvas) {
	
	// defines colors in RGBA 0-255
	LinearColor colors;
	colors.R = 255;
	colors.G = 255;
	colors.B = 0;
	colors.A = 255;
	canvas.SetColor(MyColors::YELLOW);

	// sets position to top left
	// x moves to the right
	// y moves down
	// bottom right would be 1920, 1080 for 1080p monitors
	canvas.SetPosition(Vector2F{ 100.0, 100.0 });
	Vector2 canvasSize = canvas.GetSize();

	// says hi
	// draws from the last set position
	// the two floats are text x and y scale
	// the false turns off the drop shadow
	canvas.DrawString("Screensize: X:" + std::to_string(canvasSize.X) + "; Y:" + std::to_string(canvasSize.Y), 2.0, 2.0, false);

	// make a cross at the ball center location
	/*if (!coolEnabled) { return; }  
	ServerWrapper server = gameWrapper->GetCurrentGameState();  
	if (!server) { return; }  
	BallWrapper ball = server.GetBall();  
	if (!ball) { return; }  
	Vector ballLocation = ball.GetLocation();  
	Vector2 ballLocation2D = canvas.Project(ballLocation);  
	canvas.SetColor(255, 0, 0, 255);  
	canvas.DrawLine(Vector2{ballLocation2D.X - 10, ballLocation2D.Y}, Vector2{ballLocation2D.X + 10, ballLocation2D.Y});  
	canvas.DrawLine(Vector2{ballLocation2D.X, ballLocation2D.Y - 10}, Vector2{ballLocation2D.X, ballLocation2D.Y + 10});*/
}