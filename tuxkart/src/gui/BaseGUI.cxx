//  $Id: BaseGUI.cxx,v 1.3 2004/08/08 03:45:09 jamesgregory Exp $
//
//  TuxKart - a fun racing game with go-kart
//  Copyright (C) 2004 Steve Baker <sjbaker1@airmail.net>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "BaseGUI.h"
#include "tuxkart.h"
#include "MainMenu.h"
#include "CharSel.h"
#include "Difficulty.h"
#include "GameMode.h"
#include "Options.h"
#include "TrackSel.h"
#include "NumPlayers.h"
#include "RaceGUI.h"
#include "RaceMenu.h"

void updateGUI()
{
	static uint rememberSize = 0;
	
	if (rememberSize != guiStack.size())
	{
		if (gui)
		{
			delete gui;
			gui = NULL;
		}
		
		rememberSize = guiStack.size();
		
		if (guiStack.size())
		{		
			switch (guiStack.back())
			{
			case GUIS_MAINMENU:
				gui = new MainMenu;
				break;
			case GUIS_CHARSEL:
				gui = new CharSel;
				break;
			case GUIS_DIFFICULTYGP:
			case GUIS_DIFFICULTYQR:
				gui = new Difficulty;
				break;
			case GUIS_GAMEMODE:
				gui = new GameMode;
				break;
			case GUIS_OPTIONS:
				gui = new Options;
				break;
			case GUIS_TRACKSEL:
				gui = new TrackSel;
				break;
			case GUIS_NUMPLAYERS:
				gui = new NumPlayers;
				break;
			case GUIS_RACE:
				gui = new RaceGUI;
				break;
			case GUIS_RACEMENU:
				gui = new RaceMenu;
				break;
			case GUIS_EXITRACE:
				backToSplash();
			}
		}
		//something somewhere (most likely in the WidgetSet stuff) means the cursor will get enabled again before the game starts if you just call this when the game starts
		SDL_ShowCursor(SDL_DISABLE);
	}
	
	static int then = SDL_GetTicks();
	int now = SDL_GetTicks();
	
	if (gui)
		gui -> update( (now - then) / 1000.f );
		
	then = now;
}

/*---------------------------------------------------------------------------*/
