//This is *actually* part of the GuiList header and not meant to be compiled.

#include "GuiList.h"
#include <iostream>

template <typename listType>
GuiList<listType>::GuiList(int offsetX, int offsetY, Renderer::FontSize fontsize)
{
	mSelection = 0;
	mScrollDir = 0;
	mScrolling = 0;
	mScrollAccumulator = 0;

	setOffsetX(offsetX);
	setOffsetY(offsetY);

	mTextOffsetX = 0;

	mFont = fontsize;
	mSelectorColor = 0x000000;
	mSelectedTextColorOverride = -1;

	mDrawCentered = true;

	InputManager::registerComponent(this);
}

template <typename listType>
GuiList<listType>::~GuiList()
{
	InputManager::unregisterComponent(this);
}

template <typename listType>
void GuiList<listType>::onRender()
{
	const int cutoff = getOffsetY();
	const int entrySize = Renderer::getFontHeight(mFont) + 5;

	int startEntry = 0;

	//number of entries that can fit on the screen simultaniously
	int screenCount = (Renderer::getScreenHeight() - cutoff) / entrySize;
	screenCount -= 1;

	if((int)mRowVector.size() >= screenCount)
	{
		startEntry = mSelection - (screenCount * 0.5);
		if(startEntry < 0)
			startEntry = 0;
		if(startEntry >= (int)mRowVector.size() - screenCount)
			startEntry = mRowVector.size() - screenCount;
	}

	int y = cutoff;

	if(mRowVector.size() == 0)
	{
		Renderer::drawCenteredText("The list is empty.", 0, y, 0x0000FF, mFont);
		return;
	}

	int listCutoff = startEntry + screenCount;
	if(listCutoff > (int)mRowVector.size())
		listCutoff = mRowVector.size();

	for(int i = startEntry; i < listCutoff; i++)
	{
		if(mSelection == i)
		{
			Renderer::drawRect(getOffsetX(), y, Renderer::getScreenWidth(), Renderer::getFontHeight(mFont), mSelectorColor);
		}

		ListRow row = mRowVector.at((unsigned int)i);

		if(mDrawCentered)
			Renderer::drawCenteredText(row.name, getOffsetX(), y, row.color, mFont);
		else
			Renderer::drawText(row.name, getOffsetX() + mTextOffsetX, y, (mSelectedTextColorOverride != -1 && mSelection == i ? mSelectedTextColorOverride : row.color), mFont);

		y += entrySize;
	}
}

template <typename listType>
void GuiList<listType>::onInput(InputManager::InputButton button, bool keyDown)
{
	if(mRowVector.size() > 0)
	{
		if(keyDown)
		{
			if(button == InputManager::DOWN)
			{
				mScrollDir = 1;
				mSelection++;
			}

			if(button == InputManager::UP)
			{
				mScrollDir = -1;
				mSelection--;
			}
		}else{
			if((button == InputManager::DOWN && mScrollDir > 0) || (button == InputManager::UP && mScrollDir < 0))
			{
				mScrollAccumulator = 0;
				mScrolling = false;
				mScrollDir = 0;
			}
		}

		if(mSelection < 0)
			mSelection += mRowVector.size();

		if(mSelection >= (int)mRowVector.size())
			mSelection -= mRowVector.size();
	}
}

template <typename listType>
void GuiList<listType>::onTick(int deltaTime)
{
	if(mScrollDir != 0)
	{
		mScrollAccumulator += deltaTime;

		if(!mScrolling)
		{
			if(mScrollAccumulator >= SCROLLDELAY)
			{
				mScrollAccumulator = SCROLLTIME;
				mScrolling = true;
			}
		}

		if(mScrolling)
		{
			mScrollAccumulator += deltaTime;

			while(mScrollAccumulator >= SCROLLTIME)
			{
				mScrollAccumulator -= SCROLLTIME;

				mSelection += mScrollDir;
				if(mSelection < 0)
					mSelection += mRowVector.size();
				if(mSelection >= (int)mRowVector.size())
					mSelection -= mRowVector.size();
			}
		}
	}
}

//list management stuff
template <typename listType>
void GuiList<listType>::addObject(std::string name, listType obj, int color)
{
	ListRow row = {name, obj, color};
	mRowVector.push_back(row);
}

template <typename listType>
void GuiList<listType>::clear()
{
	mRowVector.clear();
	mSelection = 0;
}

template <typename listType>
std::string GuiList<listType>::getSelectedName()
{
	if((int)mRowVector.size() > mSelection)
		return mRowVector.at(mSelection).name;
	else
		return "";
}

template <typename listType>
listType GuiList<listType>::getSelectedObject()
{
	if((int)mRowVector.size() > mSelection)
		return mRowVector.at(mSelection).object;
	else
		return NULL;
}

template <typename listType>
int GuiList<listType>::getSelection()
{
	return mSelection;
}

template <typename listType>
bool GuiList<listType>::isScrolling()
{
	return mScrolling;
}

template <typename listType>
void GuiList<listType>::onPause()
{
	InputManager::unregisterComponent(this);
}

template <typename listType>
void GuiList<listType>::onResume()
{
	InputManager::registerComponent(this);
}

template <typename listType>
void GuiList<listType>::setSelectorColor(int selectorColor)
{
	mSelectorColor = selectorColor;
}

template <typename listType>
void GuiList<listType>::setSelectedTextColor(int selectedColor)
{
	mSelectedTextColorOverride = selectedColor;
}

template<typename listType>
void GuiList<listType>::setCentered(bool centered)
{
	mDrawCentered = centered;
}

template<typename listType>
void GuiList<listType>::setTextOffsetX(int textoffsetx)
{
	mTextOffsetX = textoffsetx;
}

template <typename listType>
int GuiList<listType>::getObjectCount()
{
	return mRowVector.size();
}

template <typename listType>
listType GuiList<listType>::getObject(int i)
{
	return mRowVector.at(i).object;
}

template <typename listType>
void GuiList<listType>::setSelection(int i)
{
	mSelection = i;
}
