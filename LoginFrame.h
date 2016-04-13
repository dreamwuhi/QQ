#pragma once

class CLoginFrame : public WindowImplBase
{
public:
	CLoginFrame(void);
	virtual ~CLoginFrame(void);
public:
	LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	void OnPrepare();
	void SetControlVisible(bool flag = true);
	virtual void Notify( TNotifyUI& msg );
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	CGifAnimUI			*m_GifAnimBK;
	CVerticalLayoutUI *m_VerticalLayoutBk;
	CControlUI			*m_ControlFace;
	CButtonUI				*m_ButtonState;
	CComboUI			*m_ComboAccount;
	CEditUI					*m_EditAccount;
	CButtonUI				*m_ButtonZhuce;
	CEditUI					*m_EditPassword;
	CButtonUI				*m_ButtonMima;
	COptionUI			*m_OptionRempass;
	COptionUI			*m_OptionAutoLog;
	CButtonUI				*m_ButtonLogin;
private:
	DWORD				m_cnt;
};

