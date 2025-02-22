#pragma once

#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "MyColors.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class MyFirstBakkesPlugin : public BakkesMod::Plugin::BakkesModPlugin, public SettingsWindowBase {
public:
	void onLoad() override;
	void onUnload() override;
	void ballOnTop();

	// for in BakkesMod settings
	void RenderSettings() override;

	// for ingame overlay
	void Render(CanvasWrapper canvas);

private:

};