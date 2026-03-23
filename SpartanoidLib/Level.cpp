/**
 * @file Level.cpp
 * @author Omar Martinez
 * @author Sam Nowlan
 */

#include "pch.h"
#include "Level.h"

#include <wx/graphics.h>
#include <wx/xml/xml.h>
#include <memory>
#include <map>

#include "Spartanoid.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include "Background.h"
#include "PowerUp.h"
#include "Coin.h"
#include "Enemy.h"

using namespace std;

/**
 * Constructor
 *
 * Loads the XML file for the requested level and reads its
 * dimensions and optional coin declaration data.
 *
 * @param levelNumber The level number to load
 */
Level::Level(int levelNumber)
{
    std::wstring filename = L"levels/level" +
        std::to_wstring(levelNumber) + L".xml";

    if(!mXmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load level file: " + filename);
        return;
    }

    auto root = mXmlDoc.GetRoot();
    if(root == nullptr)
    {
        wxMessageBox(L"Invalid level file: " + filename);
        return;
    }
    root->GetAttribute(L"width").ToInt(&mWidth);
    root->GetAttribute(L"height").ToInt(&mHeight);
    
    auto child = root->GetChildren();
    for ( ; child; child = child->GetNext())
    {
        if (child->GetName() == L"declarations")
        {
            auto decl = child->GetChildren();
            for ( ; decl; decl = decl->GetNext())
            {
                if (decl->GetName() == L"coin")
                {
                    mHasCoin = true;
                    mCoinImage = L"images/" + decl->GetAttribute(L"image").ToStdWstring();
                    decl->GetAttribute(L"frames").ToInt(&mCoinFrames);
                    decl->GetAttribute(L"value").ToInt(&mCoinValue);
                }
            }
        }
    }
}

/**
 * Populate the items vector with items from this level
 * @param game Pointer to the Spartanoid game
 * @param items The items vector to populate
 * @param paddle The paddle shared pointer to set
 */
void Level::PopulateItems(Spartanoid* game,
                          std::vector<std::shared_ptr<Item>>& items,
                          std::shared_ptr<Paddle>& paddle)
{
    items.clear();

    auto root = mXmlDoc.GetRoot();
    if (root == nullptr)
    {
        return;
    }

    // First pass: build declarations map
    map<wxString, wxXmlNode*> declarations;
    auto child = root->GetChildren();
    for( ; child; child = child->GetNext())
    {
        if(child->GetName() == L"declarations")
        {
            auto decl = child->GetChildren();
            for( ; decl; decl = decl->GetNext())
            {
                wxString id = decl->GetAttribute(L"id");
                declarations[id] = decl;
            }
        }
    }

    // Second pass: create items
    child = root->GetChildren();
    for( ; child; child = child->GetNext())
    {
        if(child->GetName() == L"items")
        {
            auto itemNode = child->GetChildren();
            for( ; itemNode; itemNode = itemNode->GetNext())
            {
                wxString id = itemNode->GetAttribute(L"id");
                double x = 0;
                double y = 0;
                itemNode->GetAttribute(L"x").ToDouble(&x);
                itemNode->GetAttribute(L"y").ToDouble(&y);

                auto decl = declarations[id];
                if(decl == nullptr)  
                {
                    continue;
                }
                
                wxString image = L"images/" + decl->GetAttribute(L"image");
                wxString type = decl->GetName();


                if(type == L"paddle")
                {
                    paddle = make_shared<Paddle>(game, image.ToStdWstring());
                    paddle->SetPosition(x, y);
                    items.push_back(paddle);
                }
                else if(type == L"ball")
                {
                    auto ball = std::make_shared<Ball>(game, image.ToStdWstring());
                    ball->SetPosition(x, y);
                    items.push_back(ball);

                }
                else if(type == L"brick")
                {
                    auto brick = std::make_shared<Brick>(game, image.ToStdWstring());
                    brick->SetPosition(x, y);
                    items.push_back(brick);
                }
                else if(type == L"background")
                {
                    auto background = std::make_shared<Background>(game, image.ToStdWstring());
                    background->SetPosition(x, y);
                    items.push_back(background);
                }
                else if(type == L"power-up")
                {
                    auto powerUp = std::make_shared<PowerUp>(game, image.ToStdWstring());
                    powerUp->SetPosition(x, y);
                    items.push_back(powerUp);
                }
                else if(type == L"enemy")
                {
                    auto enemy = std::make_shared<Enemy>(game, image.ToStdWstring());
                    enemy->SetPosition(x, y);
                    items.push_back(enemy);
                }

            }
        }
    }
}