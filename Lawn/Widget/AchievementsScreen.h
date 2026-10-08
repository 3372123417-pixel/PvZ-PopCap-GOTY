#ifndef __ACHIEVEMENTSSCREEN_H__
#define __ACHIEVEMENTSSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"

class LawnApp;

using namespace Sexy;

enum AchievementId {
    HomeSecurity,
    NovelPeasPrize,
    BetterOffDead,
    ChinaShop,
    Spudow,
    Explodonator,
    Morticulturalist,
    DontPea,
    RollSomeHeads,
    Grounded,
    Zombologist,
    PennyPincher,
    SunnyDays,
    PopcornParty,
    GoodMorning,
    NoFungusAmongUs,
    BeyondTheGrave,
    Immortal,
    ToweringWisdom,
    MustacheMode,
    MAX_ACHIEVEMENTS
};

class AchievementItem {
public:
    const char* name;
    const char* description;
};

extern const AchievementItem gAchievementList[MAX_ACHIEVEMENTS];

class AchievementsWidget : public Widget {
public:
    LawnApp*    mApp;
    int         mScrollDirection;
    Rect        mMoreRockRect;
    int         mScrollValue;
    int         mScrollDecay;
    int         mDefaultScrollValue;
    bool        mDidPressMoreButton;
    int         mTouchDownY;
    int         mDragStartY;
    bool        mIsDragging;
    bool        mHasExceededDeadZone;
    float       mLastDragDelta;

    AchievementsWidget(LawnApp* theApp);
    ~AchievementsWidget() override;

    void                        Update() override;
    void                        Draw(Graphics* g) override;
    void                        KeyDown(KeyCode theKey) override;
    void                        MouseDown(int x, int y, int theClickCount) override;
    void                        MouseUp(int x, int y, int theClickCount) override;
    void                        MouseDrag(int x, int y) override;
    void                        MouseWheel(int theDelta) override;
};

class ReportAchievement {
public:
    static void GiveAchievement(LawnApp* theApp, int theAchievement, bool theForceGive);
    static void AchievementInitForPlayer(LawnApp* theApp);
};

#endif