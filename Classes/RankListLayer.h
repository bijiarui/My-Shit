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

	// 当滑动tableview时触发该方法 参数为当前的tableview对象  
	virtual void scrollViewDidScroll(ScrollView* view) {};
	// 当tableview被放大或缩小时触发该方法  参数为当前tableview对象  
	virtual void scrollViewDidZoom(ScrollView* view) {}
	// 当cell被点击时调用该方法 参数为当前的tableview对象与被点击的cell对象  
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	// 设置tableview的Cell大小  
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	// 获取编号为idx的cell  
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	// 设置tableview中cell的个数  
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	void menuCallBack(Ref* pSender);

public:
	SceneManager *tsm;
private:
	
	array<Player, max_range + 1> m_Player;
};



#endif // !_RANK_LIST_LAYER_