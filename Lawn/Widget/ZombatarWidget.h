#ifndef __ZOMBATARWIDGET_H__
#define __ZOMBATARWIDGET_H__

#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"
#include "../System/Zombatar.h"

class GameSelector;
class LawnApp;
class Zombie;
class NewLawnButton;

enum ZombatarWidgetState
{
	ZOMBATAR_STATE_LIST,
	ZOMBATAR_STATE_CREATE,
	ZOMBATAR_STATE_CONFIRM,
	ZOMBATAR_STATE_TO_CONFIRM,
	ZOMBATAR_STATE_FROM_CONFIRM
};

class ZombatarWidget : public Widget, public ButtonListener
{
public:
	enum
	{
		ZOMBATAR_BTN_BACK = 300,
		ZOMBATAR_BTN_VIEW,
		ZOMBATAR_BTN_FINISHED,
		ZOMBATAR_BTN_NEW,
		ZOMBATAR_BTN_CONFIRM_BACK,
		ZOMBATAR_BTN_PREV_PORTRAIT,
		ZOMBATAR_BTN_NEXT_PORTRAIT,
		ZOMBATAR_BTN_PREV_PAGE,
		ZOMBATAR_BTN_NEXT_PAGE
	};

public:
	GameSelector*				mGameSelector;		//+0x88
	LawnApp*					mApp;				//+0x8C
	ZombatarWidgetState			mState;				//+0x90
	ZombatarPage				mPage;				//+0x94
	int							mCurrentIndex;		//+0x98
	int							mSubPage;			//+0x9C
	int							mMaxSubPages;		//+0xA0
	int							mMouseX;			//+0xA4
	int							mMouseY;			//+0xA8
	int							mHoverGridCell;		//+0xAC
	int							mHoverColorCell;	//+0xB0
	int							mHoverTab;			//+0xB4
	bool						mDeleteHover;		//+0xB8
	int							mTransitionTimer;	//+0xBC
	int							mPart[NUM_ZOMBATAR_PAGES];		//+0xC0
	int							mColor[NUM_ZOMBATAR_PAGES];		//+0xE4

	NewLawnButton*				mBackButton;		//+0x108
	NewLawnButton*				mViewButton;		//+0x10C
	NewLawnButton*				mFinishedButton;	//+0x110
	NewLawnButton*				mNewButton;			//+0x114
	NewLawnButton*				mConfirmBackButton;	//+0x118
	NewLawnButton*				mPrevPortraitButton;//+0x11C
	NewLawnButton*				mNextPortraitButton;//+0x120
	NewLawnButton*				mPrevPageButton;	//+0x124
	NewLawnButton*				mNextPageButton;	//+0x128
	Zombie*						mPreviewZombie;		//+0x12C

public:
	ZombatarWidget(GameSelector* theGameSelector);
	~ZombatarWidget() override;

	void						Open();
	void						ResetDraft();
	void						LoadCurrentToDraft();
	bool						SaveDraft();
	void						ExportAvatarImage();
	void						DeleteCurrent();
	bool						CanSaveNewHead() const;
	int							GetHeadCount() const;
	void						ClampCurrentIndex();
	void						ChangeState(ZombatarWidgetState theState);
	void						ChangePage(ZombatarPage thePage);

	void						Draw(Graphics* g) override;
	void						Update() override;
	void						AddedToManager(WidgetManager* theWidgetManager) override;
	void						RemovedFromManager(WidgetManager* theWidgetManager) override;
	void						MouseMove(int x, int y) override;
	void						MouseUp(int x, int y) override;
	void						KeyDown(KeyCode theKey) override;

	void						ButtonPress(int theId, int theClickCount) override;
	void						ButtonDepress(int theId) override;
	void						ButtonDownTick(int) override {}
	void						ButtonMouseEnter(int) override {}
	void						ButtonMouseLeave(int) override {}
	void						ButtonMouseMove(int, int, int) override {}

private:
	void						DrawMainBackground(Graphics* g);
	void						DrawList(Graphics* g);
	void						DrawCreate(Graphics* g);
	void						DrawConfirm(Graphics* g);
	void						DrawTransition(Graphics* g);
	void						DrawAvatar(Graphics* g, int theX, int theY, const unsigned char* theRecord);
	void						DrawDraftAvatar(Graphics* g, int theX, int theY);
	void						DrawColorSwatches(Graphics* g, int thePaletteBase, int theCount, int theSavedColor);
	void						DrawAvatarBox(Graphics* g);
	void						DrawPartImage(Graphics* g, ZombatarPage thePage, int theIndex, int theX, int theY, int theColorIndex);
	Rect						GetCategoryRect(int theIndex) const;
	Rect						GetItemRect(int theIndex) const;
	Rect						GetItemHitRect(int theIndex) const;
	Rect						GetColorRect(int theIndex) const;
	int							GetTotalItemsForPage(ZombatarPage thePage) const;
	int							GetSubPageItemCount() const;
	bool						PageAllowsNone() const;
	bool						PageAllowsColors() const;
	Image*						GetCategoryImage(ZombatarPage thePage, bool theSelected, bool theOver) const;
	Image*						GetPartImage(ZombatarPage thePage, int theIndex) const;
	Image*						GetPartMaskImage(ZombatarPage thePage, int theIndex) const;
	Image*						GetBackgroundImage(int theIndex) const;
	void						DrawImageColorized(Graphics* g, Image* theImage, int theX, int theY, int theColorIndex);
	void						BackToSelector();
	void						ShowMaxHeadsMessage();
	void						HandleGridClick(int theX, int theY);
	void						HandleColorClick(int theX, int theY);
	void						UpdateButtonState();
	void						DecodeRecord(const unsigned char* theRecord, int* thePart, int* theColor) const;
	void						EncodeRecord(unsigned char* theRecord) const;
	void						CreatePreviewZombie();
	void						DestroyPreviewZombie();
};

#endif