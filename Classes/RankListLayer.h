#pragma once
#ifndef _RANK_LIST_LAYER_
#define _RANK_LIST_LAYER_

#include <array> 
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SceneManager.h"
#include "ListDefine.h"
 
using std::array;
USING_NS_CC;
USING_NS_CC_EXT;


class RankListLayer : public Layer, TableViewDataSource, TableViewDelegate 
{
public:
	virtual bool init();
	CREATE_FUNC(RankListLayer);

	virtual void scrollViewDidScroll(ScrollView* view) {};  
	virtual void scrollViewDidZoom(ScrollView* view) {} 
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx); 
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	void menuCallBack(Ref* pSender);

public:
	SceneManager *tsm;
private:
	
	array<Player, max_range + 1> m_Player;
};



#endif // !_RANK_LIST_LAYER_