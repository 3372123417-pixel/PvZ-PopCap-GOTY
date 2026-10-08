#ifndef __GAMESELECTOR_H__
#define __GAMESELECTOR_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"
#include "AchievementsScreen.h"

class LawnApp;
class ToolTipWidget;
class ZombatarWidget;
namespace Sexy
{
    class DialogButton;
}

using namespace Sexy;

enum SelectorAnimState
{
    SELECTOR_OPEN,
    SELECTOR_NEW_USER,
    SELECTOR_SHOW_SIGN,
    SELECTOR_IDLE
};

class GameSelector : public Widget, public ButtonListener
{
private:
    enum
    {
        GameSelector_Adventure = 100,
        GameSelector_Minigame = 101,
        GameSelector_Puzzle = 102,
        GameSelector_Options = 103,
        GameSelector_Help = 104,
        GameSelector_Quit = 105,
        GameSelector_ChangeUser = 106,
        GameSelector_Store = 107,
        GameSelector_Almanac = 108,
        GameSelector_ZenGarden = 109,
        GameSelector_Survival = 110,
        GameSelector_Zombatar = 111,
        GameSelector_Achievements = 112
    };

public:
    LawnApp*                    mApp;                       //+0x8C
    NewLawnButton*              mAdventureButton;           //+0x90
    NewLawnButton*              mMinigameButton;            //+0x94
    NewLawnButton*              mPuzzleButton;              //+0x98
    NewLawnButton*              mOptionsButton;             //+0x9C
    NewLawnButton*              mQuitButton;                //+0xA0
    NewLawnButton*              mHelpButton;                //+0xA4
    NewLawnButton*              mStoreButton;               //+0xA8
    NewLawnButton*              mAlmanacButton;             //+0xAC
    NewLawnButton*              mZenGardenButton;           //+0xB0
    NewLawnButton*              mSurvivalButton;            //+0xB4
    NewLawnButton*              mChangeUserButton;          //+0xB8
    NewLawnButton*              mZombatarButton;            //+0xBC
    NewLawnButton*              mAchievementsButton;        //+0xC0
    Widget*                     mOverlayWidget;             //+0xC4
    bool                        mStartingGame;              //+0xC8
    int                         mStartingGameCounter;       //+0xCC
    bool                        mMinigamesLocked;           //+0xD0
    bool                        mPuzzleLocked;              //+0xD1
    bool                        mSurvivalLocked;            //+0xD2
    bool                        mShowStartButton;           //+0xD3
    ParticleSystemID            mTrophyParticleID;          //+0xD4
    ReanimationID               mSelectorReanimID;          //+0xD8
    ReanimationID               mCloudReanimID[6];          //+0xDC
    int                         mCloudCounter[6];           //+0xF4
    ReanimationID               mFlowerReanimID[3];         //+0x10C
    ReanimationID               mLeafReanimID;              //+0x118
    ReanimationID               mHandReanimID;              //+0x11C
    int                         mLeafCounter;               //+0x120
    SelectorAnimState           mSelectorState;             //+0x124
    int                         mLevel;                     //+0x128
    bool                        mLoading;                   //+0x12C
    ToolTipWidget*              mToolTip;                   //+0x130
    bool                        mHasTrophy;                 //+0x134
    bool                        mUnlockSelectorCheat;       //+0x135
    int                         mSlideCounter;              //+0x138
    int                         mStartX;                    //+0x13C
    int                         mStartY;                    //+0x140
    int                         mDestX;                     //+0x144
    int                         mDestY;                     //+0x148
    AchievementsWidget*         mAchievementsWidget;        //+0x14C
    ZombatarWidget*             mZombatarWidget;            //+0x150

public:
    GameSelector(LawnApp* theApp);
    virtual ~GameSelector();

    void                        SyncProfile(bool theShowLoading);
    virtual void                Draw(Graphics* g);
    virtual void                DrawOverlay(Graphics* g);
    virtual void                Update();
    virtual void                AddedToManager(WidgetManager* theWidgetManager);
    virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
    virtual void                OrderInManagerChanged();
    virtual void                ButtonMouseEnter(int theId);
    virtual void                ButtonPress(int theId, int theClickCount);
    virtual void                ButtonDepress(int theId);
    virtual void                KeyDown(KeyCode theKey);
    virtual void                KeyChar(char theChar);
    virtual void                MouseDown(int x, int y, int theClickCount);
    void                        TrackButton(DialogButton* theButton, const char* theTrackName, float theOffsetX, float theOffsetY);
    void                        SyncButtons();
    void                        AddTrophySparkle();
    void                        ClickedAdventure();
    void                        UpdateTooltip();
    /*inline*/ bool             ShouldDoZenTuturialBeforeAdventure();
    void                        AddPreviewProfiles();
    void                        ShowZombatarScreen();
    void                        ShowAchievementsScreen();
    void                        SlideTo(int theX, int theY);
};

class GameSelectorOverlay : public Widget
{
public:
    GameSelector*               mParent;                    //+0x88

public:
    GameSelectorOverlay(GameSelector* theGameSelector);
    virtual ~GameSelectorOverlay() { }

    virtual void Draw(Graphics* g);
};

#endif