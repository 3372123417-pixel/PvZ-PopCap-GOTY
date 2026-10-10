#include "../Board.h"
#include "../Zombie.h"
#include "GameButton.h"
#include "../../LawnApp.h"
#include "ContinueDialog.h"
#include "../../Resources.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../Sexy.TodLib/TodStringFile.h"

//0x4330D0
ContinueDialog::ContinueDialog(LawnApp* theApp) : LawnDialog(
	theApp, 
	Dialogs::DIALOG_CONTINUE, 
	true, 
	theApp->GetString("CONTINUE_GAME_HEADER", _S("CONTINUE GAME?")),
	_S(""), 
	_S("[DIALOG_BUTTON_CANCEL]"),
	Dialog::BUTTONS_FOOTER)
{
    if (theApp->IsAdventureMode())
    {
        mDialogLines = mApp->GetString("CONTINUE_GAME_OR_RESTART",
            _S("Do you want to continue your current game or restart the level?"));
        mContinueButton = MakeButton(ContinueDialog::ContinueDialog_Continue, this, TodStringTranslate(_S("[CONTINUE_BUTTON]")));
        mNewGameButton = MakeButton(ContinueDialog::ContinueDialog_NewGame, this, TodStringTranslate(_S("[RESTART_BUTTON]")));
    }
    else
    {
        mDialogLines = mApp->GetString("CONTINUE_GAME",
            _S("Do you want to continue your current game or start a new game?"));
        mContinueButton = MakeButton(ContinueDialog::ContinueDialog_Continue, this, TodStringTranslate(_S("[CONTINUE_BUTTON]")));
        mNewGameButton = MakeButton(ContinueDialog::ContinueDialog_NewGame, this, TodStringTranslate(_S("[NEW_GAME_BUTTON]")));
    }

    mTallBottom = true;
    CalcSize(10, 60);

    int aBtnLeft = IMAGE_BUTTON_LEFT->mWidth;
    int aBtnMid = IMAGE_BUTTON_MIDDLE->mWidth;
    int aBtnRight = IMAGE_BUTTON_RIGHT->mWidth;
    int aBtnWidth = aBtnLeft + aBtnMid * 3 + aBtnRight;
    int aInsetH = mContentInsets.mLeft + mContentInsets.mRight + mBackgroundInsets.mLeft + mBackgroundInsets.mRight;
    // Min width that keeps the Continue and New Game buttons from overlapping.
    int aMinCancelWidth = 2 * aBtnWidth - 40;
    int aSteps = (aMinCancelWidth - aBtnLeft - aBtnRight + aBtnMid - 1) / aBtnMid;
    int aMinWidth = aBtnLeft + aBtnRight + aSteps * aBtnMid + aInsetH - 8;
    if (mWidth < aMinWidth)
    {
        int aTopMidWidth = IMAGE_DIALOG_TOPMIDDLE->mWidth;
        int aImageWidth = IMAGE_DIALOG_TOPLEFT->mWidth + IMAGE_DIALOG_TOPRIGHT->mWidth + aTopMidWidth;
        int aWidth = aMinWidth;
        if (aWidth <= aImageWidth)
        {
            aWidth = aImageWidth;
        }
        else if (aTopMidWidth > 0)
        {
            int anExtraWidth = (aWidth - aImageWidth) % aTopMidWidth;
            if (anExtraWidth)
            {
                aWidth += aTopMidWidth - anExtraWidth;
            }
        }
        Resize(mX, mY, aWidth, mHeight);
    }
}

//0x4333D0��0x4333F0
ContinueDialog::~ContinueDialog()
{
    delete mContinueButton;
    delete mNewGameButton;
}

//0x433470
int ContinueDialog::GetPreferredHeight(int theWidth)
{
    return LawnDialog::GetPreferredHeight(theWidth) + 40;
}

//0x433480
void ContinueDialog::Resize(int theX, int theY, int theWidth, int theHeight)
{
    LawnDialog::Resize(theX, theY, theWidth, theHeight);

    int aBtnWidth = IMAGE_BUTTON_LEFT->mWidth + IMAGE_BUTTON_MIDDLE->mWidth * 3 + IMAGE_BUTTON_RIGHT->mWidth;
    int aBtnHeight = mLawnYesButton->mHeight;

    /*
    int aContinueX = mLawnYesButton->mX - 20;
    int aNewGameX = mLawnYesButton->mX + mLawnYesButton->mWidth - aBtnWidth + 24;
    while (aContinueX + aBtnWidth > aNewGameX)
    {
        aContinueX -= 20;
        aNewGameX += 20;
    }

    mContinueButton->Resize(aContinueX, mLawnYesButton->mY - aBtnHeight - 2, aBtnWidth, aBtnHeight);
    mNewGameButton->Resize(aNewGameX, mContinueButton->mY, aBtnWidth, aBtnHeight);
    mLawnYesButton->Resize(theWidth / 2 - aBtnWidth / 2, mLawnYesButton->mY, aBtnWidth, aBtnHeight);
    */

    mContinueButton->Resize(mLawnYesButton->mX - 20, mLawnYesButton->mY - aBtnHeight, aBtnWidth, aBtnHeight);
    mNewGameButton->Resize(mLawnYesButton->mX + mLawnYesButton->mWidth - aBtnWidth + 20, mContinueButton->mY, aBtnWidth, aBtnHeight);
}

//0x433520
void ContinueDialog::AddedToManager(WidgetManager* theWidgetManager)
{
    LawnDialog::AddedToManager(theWidgetManager);
    AddWidget(mContinueButton);
    AddWidget(mNewGameButton);
}

//0x433590
void ContinueDialog::RemovedFromManager(WidgetManager* theWidgetManager)
{
    LawnDialog::RemovedFromManager(theWidgetManager);
    RemoveWidget(mContinueButton);
    RemoveWidget(mNewGameButton);
}

//0x4335D0
void ContinueDialog::RestartLoopingSounds()
{
    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_RAINING_SEEDS || mApp->IsStormyNightLevel())
    {
        mApp->PlayFoley(FoleyType::FOLEY_RAIN);
    }

    Zombie* aZombie = nullptr;
    while (mApp->mBoard->IterateZombies(aZombie))
    {
        if (aZombie->mPlayingSong)
        {
            aZombie->StartZombieSound();
        }
    }
}

//0x4336C0
void ContinueDialog::ButtonDepress(int theId)
{
    if (theId == ContinueDialog::ContinueDialog_Continue)
    {
        if (mApp->mBoard->mNextSurvivalStageCounter != 1)
        {
            std::string aFileName = GetSavedGameName(mApp->mGameMode, mApp->mPlayerInfo->mId);
            mApp->EraseFile(aFileName);
        }

        RestartLoopingSounds();
        mApp->KillDialog(mId);
    }
    else if (theId == ContinueDialog::ContinueDialog_NewGame)
    {
        if (mApp->IsAdventureMode())
        {
            LawnDialog* aDialog = (LawnDialog*)mApp->DoDialog(
                Dialogs::DIALOG_RESTARTCONFIRM, 
                true, 
                mApp->GetString("RESTART_LEVEL_HEADER", _S("Restart Level?")),
                mApp->GetString("RESTART_LEVEL", _S("Are you sure that you want to restart the level?")),
                _S(""), 
                Dialog::BUTTONS_OK_CANCEL
            );
            aDialog->mLawnYesButton->mLabel = TodStringTranslate(_S("[RESTART_BUTTON]"));
        }
        else
        {
            LawnDialog* aDialog = (LawnDialog*)mApp->DoDialog(
                Dialogs::DIALOG_RESTARTCONFIRM, 
                true, 
                mApp->GetString("NEW_GAME_HEADER", _S("New Game?")),
                mApp->GetString("NEW_GAME", _S("Are you sure that you want to start a new game?")),
                _S(""), 
                Dialog::BUTTONS_OK_CANCEL
            );
            aDialog->mLawnYesButton->mLabel = TodStringTranslate(_S("[NEW_GAME_BUTTON]"));
        }
    }
    else
    {
        mApp->KillDialog(mId);
        if (mApp->IsAdventureMode())
        {
            mApp->ShowGameSelector();
        }
        else if (mApp->IsSurvivalMode())
        {
            mApp->KillBoard();
            mApp->ShowChallengeScreen(ChallengePage::CHALLENGE_PAGE_SURVIVAL);
        }
        else if (mApp->IsPuzzleMode())
        {
            mApp->KillBoard();
            mApp->ShowChallengeScreen(ChallengePage::CHALLENGE_PAGE_PUZZLE);
        }
        else
        {
            mApp->KillBoard();
            mApp->ShowChallengeScreen(ChallengePage::CHALLENGE_PAGE_CHALLENGE);
        }
    }
}