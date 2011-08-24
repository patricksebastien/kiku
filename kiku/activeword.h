/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#ifndef __activeword__
#define __activeword__

#include <wx/wx.h>
#include "gui_activeword.h"

const int WIDTH = 150;

class MainFrame;

class ActiveWord : public gui_activeword
{
	public:
		ActiveWord( wxWindow* parent );
		virtual ~ActiveWord();
		virtual void Onb_applicationrefresh( wxCommandEvent& event );
	
private:
		void fetch(wxTimerEvent& event);
		void fetchactions();
		void initlist();
		void InsertItemInReportView(int);
		MainFrame *m_parent;
};

#endif
