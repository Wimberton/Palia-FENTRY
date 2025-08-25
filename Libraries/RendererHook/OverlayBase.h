#pragma once
#include <mutex>

struct ImFont;

class OverlayBase
{
public:
	virtual ~OverlayBase() = default;
	static OverlayBase* Instance;

	void HookReady();
	void SetupFonts();
	void OverlayProc();

	bool ShowOverlay() const { return bShowOverlay; }
	void ShowOverlay(bool bShow);

	void SetupOverlay();
	bool IsReady() const { return bIsReady; }

	bool bShowOverlay;

	ImFont* FontDefault; // Inter-Medium
	ImFont* FontHUD;
	ImFont* InterBlack;
	ImFont* InterLight;
	ImFont* FontAwesome;
	ImFont* ESPFont;

protected:
	// Called always - use to draw an HUD
	virtual void DrawHUD() = 0;
	// Called only when overlay is active
	virtual void DrawOverlay() = 0;
	// Called to display the FOV circle
	virtual void DrawGuiESP() = 0;
	// Called to display the ESP logic
	virtual void DrawGuiFOVCircle() = 0;
	// Called to display the enabled features
	virtual void DrawEnabledFeatures() = 0;

protected:
	std::recursive_mutex OverlayMutex;
	bool bSetupOverlayCalled;
	bool bIsReady;
};