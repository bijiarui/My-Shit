#pragma once
#ifndef __GAME_DEFINE__ 
#define __GAME_DEFINE__ 

#define max_range 10

#define UD_getInt UserDefault::sharedUserDefault()->getIntegerForKey 
#define UD_getBool UserDefault::sharedUserDefault()->getBoolForKey 
#define UD_getString UserDefault::sharedUserDefault()->getStringForKey 

#define UD_setInt UserDefault::sharedUserDefault()->setIntegerForKey 
#define UD_setBool UserDefault::sharedUserDefault()->setBoolForKey 
#define UD_setString UserDefault::sharedUserDefault()->setStringForKey 

struct Player
{
	std::string name;
	int score;
};
#endif
