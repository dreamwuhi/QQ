#include "StdAfx.h"
#include "MainFrame.h"
#include "UIAnimationTabLayout.h"

const TCHAR* const kTabControlName = _T("tabs");
const TCHAR* const kFriendsListControlName = _T("friends");

CMainFrame::CMainFrame()
{
}


CMainFrame::~CMainFrame(void)
{
}

LPCTSTR CMainFrame::GetWindowClassName() const
{
	return _T("UISkinPickerDialog");
}

DuiLib::CDuiString CMainFrame::GetSkinFile()
{
	return _T("main_frame.xml");
	//return _T("OwnerUI.xml");
}

DuiLib::CDuiString CMainFrame::GetSkinFolder()
{
	return L"";
	//return _T("OwnerFolder");
}



void CMainFrame::OnPrepare(TNotifyUI& msg)
{
	UpdateFriendsList();
}

void CMainFrame::Notify(TNotifyUI& msg)
{
	CDuiString SenderName = msg.pSender->GetName();
	if( msg.sType == _T("click") ) 
	{
		if(SenderName == L"setting_quit")
		{
			Close();
		}
		else if(SenderName == L"state")
		{
			CMenuWnd* pMenu = new CMenuWnd();
			CButtonUI* pControl = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("state")));
			RECT pos = pControl->GetPos();
			CPoint point ;
			point.x = pos.left;
			point.y = pos.top;
			ClientToScreen(m_hWnd, &point);
			point.y += 18;
			pMenu->Init(NULL, _T("menu_main.xml"), point, &m_PaintManager,NULL);
		}
		else if(SenderName == L"setting")
		{
			CMenuWnd* pMenu = new CMenuWnd();
			CButtonUI* pControl = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("setting")));
			RECT pos = pControl->GetPos();
			CPoint point ;
			point.x = pos.left;
			point.y = pos.top;
			ClientToScreen(m_hWnd, &point);
			point.y -= 304;
			point.x += 5;
			pMenu->Init(NULL, _T("menu_setting.xml"), point, &m_PaintManager,NULL);
		}
	}
	else if(msg.sType == _T("windowinit"))
	{
		OnPrepare(msg);
	}
	else if(msg.sType  == _T("itemclick"))
	{
		//CTabLayoutUI* pTabControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(kTabControlName));
		CAnimationTabLayoutUI* pTabControl	=	static_cast<CAnimationTabLayoutUI*>(m_PaintManager.FindControl(kTabControlName));
		if (pTabControl != NULL)
		{
			if (pTabControl->GetCurSel() == 0)
			{
				CFriendsUI* pFriendsList = static_cast<CFriendsUI*>(m_PaintManager.FindControl(kFriendsListControlName));
				if ((pFriendsList != NULL) &&  pFriendsList->GetItemIndex(msg.pSender) != -1)
				{
					if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
					{
						Node* node = (Node*)msg.pSender->GetTag();
						if (pFriendsList->CanExpand(node))   //只有点击了 根节点
						{
							pFriendsList->SetSelectedItemBkColor(0xfff5e1bc);
							pFriendsList->SetChildVisible(node, !node->data().child_visible_);
						}
						else
						{
							pFriendsList->SetSelectedItemBkColor(0xfffbeba9);
						}
					}
				}
			}
		}
	}
	__super::Notify(msg);
}

LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch(uMsg)
	{
	case WM_NCLBUTTONDBLCLK:
		lRes= 0;
		break;
	case WM_NCHITTEST:     
		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); 
		break;
	default:
		bHandled = FALSE;
	}
	if(bHandled ) return lRes;
	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMainFrame::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if( !::IsZoomed(*this) )//窗口放大
	{
		RECT rcSizeBox = m_PaintManager.GetSizeBox();
		if( pt.y < rcClient.top + rcSizeBox.top )
		{
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
			return HTTOP;
		}
		else if( pt.y > rcClient.bottom - rcSizeBox.bottom )
		{
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}

		if( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
		if( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
	}

	RECT rcCaption = m_PaintManager.GetCaptionRect();
	//鼠标点击的位置在标题栏内
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) 
	{
		CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(pt));
		if( pControl && _tcsicmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
			_tcsicmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
			_tcsicmp(pControl->GetClass(), _T("SliderUI")) != 0 &&
			_tcsicmp(pControl->GetClass(), _T("EditUI")) != 0 &&
			_tcsicmp(pControl->GetClass(), _T("RichEditUI")) != 0 &&
			_tcsicmp(pControl->GetClass(), _T("ComboUI")) != 0)
			return HTCAPTION;
	}
	return HTCLIENT;
}

void CMainFrame::UpdateFriendsList()
{
	CFriendsUI* pFriendsList = static_cast<CFriendsUI*>(m_PaintManager.FindControl(kFriendsListControlName));
	if(pFriendsList != NULL)
	{
		if (!friends_.empty())					//清空还有列表
			friends_.clear();
		if (pFriendsList->GetCount() > 0)
			pFriendsList->RemoveAll();

		FriendListItemInfo item;
		item.id = _T("0");					//根节点
		item.folder = true;
		item.empty = false;
		item.nick_name = _T("我的好友");
		Node* root_parent = pFriendsList->AddNode(item, NULL);		//添加根节点，返回自身节点（根）
		friends_.push_back(item);				//主窗口保存一份好友列表

		item.id = _T("1");
		item.folder = false;
		item.logo = _T("/login_skin/myface.png");
		item.nick_name = _T("MJH_辉");
		item.description = _T("Start again");
		pFriendsList->AddNode(item,root_parent);
		friends_.push_back(item);

		item.id = _T("1");
		item.folder = false;
		item.logo = _T("/login_skin/dior.png");
		item.nick_name = _T("Dior");
		item.description = _T("不忘初心，放得始终！");
		pFriendsList->AddNode(item, root_parent);
		friends_.push_back(item);

		item.id = _T("1");
		item.folder = false;
		item.logo = _T("/login_skin/dior.png");
		item.nick_name = _T("Dior");
		item.description = _T("不忘初心，放得始终！");
		pFriendsList->AddNode(item, root_parent);
		friends_.push_back(item);
		item.id = _T("1");
		item.folder = false;
		item.logo = _T("/login_skin/dior.png");
		item.nick_name = _T("Dior");
		item.description = _T("不忘初心，放得始终！");
		pFriendsList->AddNode(item, root_parent);
		friends_.push_back(item);

		item.id = _T("1");
		item.folder = false;
		item.logo = _T("/login_skin/dior.png");
		item.nick_name = _T("Dior");
		item.description = _T("不忘初心，放得始终！");
		pFriendsList->AddNode(item, root_parent);
		friends_.push_back(item);
		item.id = _T("1");

		item.folder = false;
		item.logo = _T("/login_skin/dior.png");
		item.nick_name = _T("Dior");
		item.description = _T("不忘初心，放得始终！");
		pFriendsList->AddNode(item, root_parent);
		friends_.push_back(item);

		item.id = _T("1");
		item.folder = false;
		item.logo = _T("/login_skin/dior.png");
		item.nick_name = _T("Dior");
		item.description = _T("不忘初心，放得始终！");
		pFriendsList->AddNode(item, root_parent);
		friends_.push_back(item);

		item.id = _T("1");
		item.folder = false;
		item.logo = _T("/login_skin/dior.png");
		item.nick_name = _T("Dior");
		item.description = _T("不忘初心，放得始终！");
		pFriendsList->AddNode(item, root_parent);
		friends_.push_back(item);

		item.id = _T("1");
		item.folder = false;
		item.logo = _T("/login_skin/dior.png");
		item.nick_name = _T("Dior");
		item.description = _T("不忘初心，放得始终！");
		pFriendsList->AddNode(item, root_parent);
		friends_.push_back(item);

		item.id = _T("0");					//根节点
		item.folder = true;
		item.empty = false;
		item.nick_name = _T("我的亲人");
		Node* root_parent1 = pFriendsList->AddNode(item, NULL);
		friends_.push_back(item);
	}
}


CControlUI* CMainFrame::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, _T("FriendList")) == 0)
	{
		return new CFriendsUI(m_PaintManager);
	}
	else if(_tcsicmp(pstrClass, _T("AnimationTabLayout")) == 0)
	{
		return new CAnimationTabLayoutUI();
	}
	return NULL;
}

LRESULT CMainFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_MENUCLICK)
	{
		CButtonUI* pControl = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("setting_quit")));
		CDuiString *strMenuName = (CDuiString*)wParam;
		BOOL bChecked = (BOOL)lParam;	
		if (*strMenuName == _T("menu_on_line")) 
		{
			pControl->SetNormalImage(L"login_skin/on_line.bmp");
		}
		delete strMenuName;
	}
	bHandled = false;
	return 0;
}

