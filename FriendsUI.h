#pragma once
#include "Node.h"

namespace DuiLib
{
	struct FriendListItemInfo			//好友列表的信息 结构体
	{
		bool folder;	
		bool empty;		//是否空
		CDuiString id;	
		CDuiString logo;		//图标资源
		CDuiString nick_name;	//昵称资源
		CDuiString description;	//附加描述资源
	};

	class CFriendsUI : public CListUI
	{
	public:
		CFriendsUI(CPaintManagerUI& paint_manager);
		~CFriendsUI(void);
	public:
		enum {SCROLL_TIMERID = 10};
		bool Add(CControlUI* pControl);
		bool AddAt(CControlUI* pControl, int iIndex);
		bool Remove(CControlUI* pControl);
		bool RemoveAt(int iIndex);
		void RemoveAll();
		void DoEvent(TEventUI& event);
		Node* GetRoot();				//获取根节点
		Node* AddNode(const FriendListItemInfo& item, Node* parent = NULL);		//添加节点
		bool RemoveNode(Node* node);			//删除节点
		void SetChildVisible(Node* node, bool visible);		//设置孩子节点 是否可见
		bool CanExpand(Node* node) const;					//节点是否扩展
		bool SelectItem(int iIndex, bool bTakeFocus = false);
	private:
		Node*	root_node_;				//父节点
		LONG	delay_deltaY_;			
		DWORD	delay_number_;		
		DWORD	delay_left_;
		CDuiRect	text_padding_;			
		int level_text_start_pos_;
		CDuiString level_expand_image_;			//扩展节点图标资源
		CDuiString level_collapse_image_;			//合并节点图标资源
		CPaintManagerUI& paint_manager_;

		CDialogBuilder m_dlgBuilder;
	};
}

