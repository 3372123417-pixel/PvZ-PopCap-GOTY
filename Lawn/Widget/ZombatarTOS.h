#ifndef __ZOMBATARTOS_H__
#define __ZOMBATARTOS_H__

#include "LawnDialog.h"
#include "../../SexyAppFramework/SliderListener.h"
#include "../../SexyAppFramework/CheckboxListener.h"

class LawnApp;
class NewLawnButton;
namespace Sexy
{
	class Slider;
	class Checkbox;
}

class ZombatarTOS : public LawnDialog, public Sexy::SliderListener, public Sexy::CheckboxListener
{
protected:
	enum
	{
		ZombatarTOS_Checkbox = 500,
		ZombatarTOS_Accept = 501,
		ZombatarTOS_Back = 502,
		ZombatarTOS_Slider = 503
	};

public:
	Sexy::Slider*			mTOSSlider;
	NewLawnButton*			mBackButton;
	NewLawnButton*			mAcceptButton;
	Sexy::Checkbox*			mTOSCheckbox;
	int						mTextHeight;
	bool					mFlashArrow;
	int						mArrowAlpha;
	int						mArrowFadeDir;
	std::string				mBodyText;

public:
	ZombatarTOS(LawnApp* theApp);
	~ZombatarTOS() override;

	void						Draw(Graphics* g) override;
	void						Update() override;
	void						AddedToManager(WidgetManager* theWidgetManager) override;
	void						RemovedFromManager(WidgetManager* theWidgetManager) override;
	void						Resize(int theX, int theY, int theWidth, int theHeight) override;
	void						ButtonPress(int theId) override;
	void						ButtonDepress(int theId) override;
	void						KeyDown(KeyCode theKey) override;
	void						MouseWheel(int theDelta) override;
	void						CheckboxChecked(int theId, bool checked) override;
	void						SliderVal(int theId, double theVal) override;
};

#endif