#include "StdAfx.h"
#include "LoginFrame.h"
#include "MainFrame.h"
#include <process.h>


unsigned int WINAPI loginProc(void* p)
{
	CLoginFrame *m_loginFrame = (CLoginFrame*)p;
	Sleep(1500);
	::ShowWindow(m_loginFrame->GetHWND(),SW_HIDE);
	CMainFrame *mainFrame =new CMainFrame();
	mainFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE | WS_EX_TOPMOST);
	mainFrame->SetIcon(IDI_ICON_QQ);
	mainFrame->CenterWindow();
	mainFrame->ShowModal();
	delete mainFrame;
	m_loginFrame->Close();
	return 0;
}

CLoginFrame::CLoginFrame(void)
{
	m_VerticalLayoutBk = NULL;
	m_ControlFace = NULL;
	m_ButtonState = NULL;
	m_ComboAccount = NULL;
	m_EditAccount = NULL;
	m_ButtonZhuce = NULL;
	m_EditPassword = NULL;
	m_ButtonMima = NULL;
	m_OptionRempass = NULL;
	m_OptionAutoLog = NULL;
	m_ButtonLogin = NULL;
	m_cnt = 0;
}


CLoginFrame::~CLoginFrame(void)
{
}

LPCTSTR CLoginFrame::GetWindowClassName() const
{
	return _T("DUIMainFrame");
}

DuiLib::CDuiString CLoginFrame::GetSkinFile()
{
	return _T("QQskin_2.xml");
	//return _T("main_frame.xml");
}

DuiLib::CDuiString CLoginFrame::GetSkinFolder()
{
	return _T("QQSkin");
	//return _T("main_skin");
}

void CLoginFrame::SetControlVisible(bool flag /*= true*/)
{
	m_ComboAccount->SetVisible(flag);
	m_EditAccount->SetVisible(flag);
	m_ButtonZhuce->SetVisible(flag);
	m_EditPassword->SetVisible(flag);
	m_ButtonMima->SetVisible(flag);
	m_OptionRempass->SetVisible(flag);
	m_OptionAutoLog->SetVisible(flag);
}

void CLoginFrame::Notify(TNotifyUI& msg)
{
	CDuiString SenderName = msg.pSender->GetName();
	if( msg.sType == _T("windowinit") ) 
	{	
		OnPrepare();
	}
	if( msg.sType == _T("showactivex") )
	{
// 		if( msg.pSender->GetName() != _T("flash") ) return;
// 		IShockwaveFlash* pFlash = NULL;
// 		CActiveXUI* pActiveX = static_cast<CActiveXUI*>(msg.pSender);
// 		pActiveX->GetControl(IID_IUnknown, (void**)&pFlash);
// 		if( pFlash != NULL ) 
// 		{
// 			pFlash->put_WMode( _bstr_t(_T("Transparent") ) );
// 			pFlash->put_Movie( _bstr_t( CPaintManagerUI::GetInstancePath() +_T("QQskin\\anibk.gif")) );
// 			pFlash->DisableLocalSecurity();
// 			pFlash->put_AllowScriptAccess(L"always");
// 			BSTR response;
// 			pFlash->CallFunction(L"<invoke name=\"setButtonText\" returntype=\"xml\"><arguments><string>Click me!</string></arguments></invoke>", &response);
// 			pFlash->Release();
// 		}  
	}
	if( msg.sType == _T("click") ) 
	{	
		if(SenderName == L"ButtonLogin")
		{
			if(m_cnt == 0)
			{
				SetControlVisible(false);
				//m_VerticalLayoutBk->SetBkImage(L"login_skin/logging.bmp");
				m_ButtonLogin->SetNormalImage(L"login_skin/longin_cansel_normal.png");
				m_ButtonLogin->SetHotImage(L"login_skin/login_cancel_hilight.bmp");
				m_ButtonLogin->SetPushedImage(L"login_skin/login_cancel_hilight.bmp");
				RECT _rect = m_ButtonLogin->GetPos();
				_rect.left -= 14;
				m_ButtonLogin->SetPos(_rect);

				RECT rect = {180,190,m_ControlFace->GetWidth()+180,m_ControlFace->GetHeight()+190};
				m_ControlFace->SetPos(rect);
				rect.left = 180+68;
				rect.top = 190+68;
				rect.right = rect.left + m_ButtonState->GetWidth();
				rect.bottom = rect.top + m_ButtonState->GetWidth();
				m_ButtonState->SetPos(rect);//QQ状态按钮

				CloseHandle((HANDLE)_beginthreadex(NULL,0,loginProc,this,0,NULL));
			}
			else
			{
				SetControlVisible();
				//m_VerticalLayoutBk->SetBkImage(L"login_skin/bk.png");
				m_ButtonLogin->SetNormalImage(L"login_skin/but_login_normal.bmp");
				m_ButtonLogin->SetHotImage(L"login_skin/but_login_highlight.bmp");
				m_ButtonLogin->SetPushedImage(L"login_skin/but_login_down.bmp");
				RECT _rect = m_ButtonLogin->GetPos();
				_rect.left += 14;
				m_ButtonLogin->SetPos(_rect);
				RECT rect = {45,195,125,275};
				m_ControlFace->SetPos(rect);//头像按钮
				rect.left = 113;
				rect.top = 263;
				rect.right = rect.left + m_ButtonState->GetWidth();
				rect.bottom = rect.top + m_ButtonState->GetWidth();
				m_ButtonState->SetPos(rect);//QQ状态按钮
			}
			m_cnt++;
			m_cnt %= 2;
		}
		else if(SenderName == L"OptionAutoLog")
		{
			COptionUI* pControlRem = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("OptionRempass")));
			if(!pControlRem->IsSelected())
				pControlRem->Activate();
		}
		else if(SenderName== _T("ButtonState")) 
		{
			CMenuWnd* pMenu = new CMenuWnd();
			CButtonUI* pControl = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonState")));
			RECT pos = pControl->GetPos();
			CPoint point ;
			point.x = pos.left;
			point.y = pos.top;
			ClientToScreen(m_hWnd, &point);
			point.y += 18;
			pMenu->Init(NULL, _T("menutest.xml"), point, &m_PaintManager,NULL);
		}
		else if(SenderName == L"ButtonZhuce")
		{
			ShellExecute(NULL,L"open",L"http://zc.qq.com/chs/index.html?from=client&pt_clientver=5449&pt_src=1&ptlang=2052&regkey=3B1FE575871E5E50BF1BDE48FE718F17082BB40A3FE169E282C35A7BB2EEE3F1&ADUIN=0&ADSESSION=0&ADTAG=CLIENT.QQ.5449_NewAccount_Btn.0&ADPUBNO=26525",NULL,NULL,SW_SHOWNORMAL);
		}
		else if(SenderName == L"ButtonMima")
		{
			ShellExecute(NULL,L"open",L"https://aq.qq.com/cn2/findpsw/pc/pc_find_pwd_input_account?source_id=1003&pt_clientver=5449&pt_src=1&ptlang=2052&aquin=505273598",NULL,NULL,SW_SHOWNORMAL);
		}
	}
	else if(msg.sType== L"itemselect")
	{
		if(SenderName == L"ComboAccount")
		{
			CEditUI* pControl = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("EditAccount")));
			pControl->SetText(msg.pSender->GetText());
		}
	}
	else if(msg.sType == L"selectchanged")
	{
		CDuiString name = msg.pSender->GetName();
		CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabs")));
		// 			 if(name == L"contacts")
		// 			 {
		// 				pControl->SelectItem(0);
		// 			 }
		// 			 else if(name == L"last_contact")
		// 			 {
		// 				pControl->SelectItem(1);
		// 			 }
		// 			 else if(name == L"friend")
		// 			 {
		// 				 pControl->SelectItem(2);
		// 			 }
		// 			 else if(name == L"phone")
		// 			 {
		// 				 pControl->SelectItem(3);
		// 			 }
	}
	__super::Notify(msg);
}

LRESULT CLoginFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT CLoginFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_MENUCLICK)
	{
		CButtonUI* pControl = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonState")));
		CDuiString *strMenuName = (CDuiString*)wParam;
		BOOL bChecked = (BOOL)lParam;	
		if (*strMenuName == _T("menu_on_line")) 
		{
			pControl->SetNormalImage(L"login_skin/on_line.bmp");
		}
		else if(*strMenuName == _T("menu_q_me"))
		{
			pControl->SetNormalImage(L"login_skin/Qme.png");
		}
		else if(*strMenuName == _T("menu_leave"))
		{
			pControl->SetNormalImage(L"login_skin/leave.png");
		}
		else if(*strMenuName == _T("menu_buzy"))
		{
			pControl->SetNormalImage(L"login_skin/buzy.png");
		}
		else if(*strMenuName == _T("menu_donotdisturb"))
		{
			pControl->SetNormalImage(L"login_skin/donotdisturb.png");
		}
		else if(*strMenuName == _T("menu_invisible"))
		{
			pControl->SetNormalImage(L"login_skin/invisible.png");
		}
		delete strMenuName;
	}
	bHandled = false;
	return 0;
}

LRESULT CLoginFrame::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

void CLoginFrame::OnPrepare()
{
	m_GifAnimBK = static_cast<CGifAnimUI*>(m_PaintManager.FindControl(_T("gifbk")));
	m_VerticalLayoutBk = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("bkground")));
	m_ControlFace = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("ButtonQQface")));
	m_ButtonState = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonState")));
	m_ComboAccount = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("ComboAccount")));
	m_EditAccount =  static_cast<CEditUI*>(m_PaintManager.FindControl(_T("EditAccount")));
	m_ButtonZhuce = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonZhuce")));
	m_EditPassword = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("EditPassword")));
	m_ButtonMima = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonMima")));
	m_OptionRempass = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("OptionRempass")));
	m_OptionAutoLog = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("OptionAutoLog")));
	m_ButtonLogin = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonLogin")));
}
