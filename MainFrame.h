#pragma once
#include "FriendsUI.h"

class CMainFrame : public WindowImplBase
{                                         
public:
	CMainFrame(void);
	virtual ~CMainFrame(void);
public:
	LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	void OnPrepare();
	void Notify( TNotifyUI& msg );
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void OnPrepare(TNotifyUI& msg);
	void UpdateFriendsList();
	CControlUI* CreateControl(LPCTSTR pstrClass);
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	std::vector<FriendListItemInfo> friends_;
};

