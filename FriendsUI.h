#pragma once
#include "Node.h"

namespace DuiLib
{
	struct FriendListItemInfo			//�����б����Ϣ �ṹ��
	{
		bool folder;	
		bool empty;		//�Ƿ��
		CDuiString id;	
		CDuiString logo;		//ͼ����Դ
		CDuiString nick_name;	//�ǳ���Դ
		CDuiString description;	//����������Դ
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
		Node* GetRoot();				//��ȡ���ڵ�
		Node* AddNode(const FriendListItemInfo& item, Node* parent = NULL);		//��ӽڵ�
		bool RemoveNode(Node* node);			//ɾ���ڵ�
		void SetChildVisible(Node* node, bool visible);		//���ú��ӽڵ� �Ƿ�ɼ�
		bool CanExpand(Node* node) const;					//�ڵ��Ƿ���չ
		bool SelectItem(int iIndex, bool bTakeFocus = false);
	private:
		Node*	root_node_;				//���ڵ�
		LONG	delay_deltaY_;			
		DWORD	delay_number_;		
		DWORD	delay_left_;
		CDuiRect	text_padding_;			
		int level_text_start_pos_;
		CDuiString level_expand_image_;			//��չ�ڵ�ͼ����Դ
		CDuiString level_collapse_image_;			//�ϲ��ڵ�ͼ����Դ
		CPaintManagerUI& paint_manager_;

		CDialogBuilder m_dlgBuilder;
	};
}

