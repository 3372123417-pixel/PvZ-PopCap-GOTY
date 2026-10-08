#ifndef __SEEDCHOOSERSCREEN_H__
#define __SEEDCHOOSERSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"

using namespace Sexy;

class Board;
class LawnApp;
class GameButton;
class ToolTipWidget;
namespace Sexy
{
    class MTRand;
}

class ChosenSeed
{
public:
    int                     mX;
    int                     mY;
    int                     mTimeStartMotion;
    int                     mTimeEndMotion;
    int                     mStartX;
    int                     mStartY;
    int                     mEndX;
    int                     mEndY;
    SeedType                mSeedType;
    ChosenSeedState         mSeedState;
    int                     mSeedIndexInBank;
    bool                    mRefreshing;
    int                     mRefreshCounter;
    SeedType                mImitaterType;
    bool                    mCrazyDavePicked;
};

class SeedChooserScreen : public Widget
{
private:
    enum
    {
        SeedChooserScreen_Start = 100,
        SeedChooserScreen_Random = 101,
        SeedChooserScreen_ViewLawn = 102,
        SeedChooserScreen_Almanac = 103,
        SeedChooserScreen_Menu = 104,
        SeedChooserScreen_Store = 105,
        SeedChooserScreen_Imitater = 106
    };

public:
    GameButton*             mStartButton;
    GameButton*             mRandomButton;
    GameButton*             mViewLawnButton;
    GameButton*             mStoreButton;
    GameButton*             mAlmanacButton;
    GameButton*             mMenuButton;
    GameButton*             mImitaterButton;
    ChosenSeed              mChosenSeeds[NUM_SEED_TYPES];
    LawnApp*                mApp;
    Board*                  mBoard;
    int                     mNumSeedsToChoose;
    int                     mSeedChooserAge;
    int                     mSeedsInFlight;
    int                     mSeedsInBank;
    ToolTipWidget*          mToolTip;
    int                     mToolTipSeed;
    int                     mLastMouseX;
    int                     mLastMouseY;
    SeedChooserState        mChooseState;
    int                     mViewLawnTime;

public:
    SeedChooserScreen();
    ~SeedChooserScreen();

    static int   PickFromWeightedArrayUsingSpecialRandSeed(TodWeightedArray* theArray, int theCount, MTRand& theLevelRNG);
    void                    CrazyDavePickSeeds();
    bool                    Has7Rows();
    void                    GetSeedPositionInChooser(int theIndex, int& x, int& y);
    void         GetSeedPositionInBank(int theIndex, int& x, int& y);
    unsigned int SeedNotRecommendedToPick(SeedType theSeedType);
    bool         SeedNotAllowedToPick(SeedType theSeedType);
    bool         SeedNotAllowedDuringTrial(SeedType theSeedType);
    void                    Draw(Graphics* g) override;
    void                    UpdateViewLawn();
    void                    LandFlyingSeed(ChosenSeed& theChosenSeed);
    void                    UpdateCursor();
    void                    Update() override;
    bool         DisplayRepickWarningDialog(const SexyChar* theMessage);
    bool                    FlyersAreComming();
    bool                    FlyProtectionCurrentlyPlanted();
    bool                    CheckSeedUpgrade(SeedType theSeedTypeTo, SeedType theSeedTypeFrom);
    void                    OnStartButton();
    void                    PickRandomSeeds();
    virtual void            ButtonDepress(int theId);
    SeedType                SeedHitTest(int x, int y);
    SeedType                FindSeedInBank(int theIndexInBank);
    void         EnableStartButton(bool theEnabled);
    void                    ClickedSeedInBank(ChosenSeed& theChosenSeed);
    void                    ClickedSeedInChooser(ChosenSeed& theChosenSeed);
    void                    ShowToolTip();
    void         RemoveToolTip();
    void         CancelLawnView();
    void                    MouseUp(int x, int y, int theClickCount) override;
    void                    UpdateImitaterButton();
    void                    MouseDown(int x, int y, int theClickCount) override;
    bool         PickedPlantType(SeedType theSeedType);
    void                    CloseSeedChooser();
    void                    KeyDown(KeyCode theKey) override;
    void                    KeyChar(SexyChar theChar) override;
    void                    UpdateAfterPurchase();
};

#endif