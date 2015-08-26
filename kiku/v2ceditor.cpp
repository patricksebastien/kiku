/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#include "v2ceditor.h"
#include "main.h"
#include "v2capplication.h"

V2cEditor::V2cEditor(wxWindow *parent, wxString language, wxString v2a, V2cApplication *myparent) : gui_v2ceditor( parent )
{
	wxStandardPathsBase& stdpath = wxStandardPaths::Get();
	
	theparent = myparent;
	g_language = language;
	g_v2a = v2a;
	autocomplete();
	editmode = false;
	html_v2ceditor->LoadPage("http://www.workinprogress.ca/KIKU/help/v2ceditor.html");
}

V2cEditor::V2cEditor(MainFrame *parent, wxString language, wxString v2a) : gui_v2ceditor( parent )
{
	wxStandardPathsBase& stdpath = wxStandardPaths::Get();
	
	themf = parent;
	g_language = language;
	g_v2a = v2a;
	autocomplete();
	editmode = false;
	html_v2ceditor->LoadPage("http://www.workinprogress.ca/KIKU/help/v2ceditor.html");
}

V2cEditor::V2cEditor(wxWindow *parent, wxString language, wxString v2a, V2cApplication *myparent, wxString edit) : gui_v2ceditor( parent )
{
	wxStandardPathsBase& stdpath = wxStandardPaths::Get();
	
	theparent = myparent;
	g_language = language;
	g_v2a = v2a;
	autocomplete();
	b_add->SetLabel("Save");
	b_delete->Show(1);
	editmode = true;
	m_edit = edit;
	
	wxArrayString noti;
	wxArrayString pretrigger;
	wxArrayString trigger;
	wxArrayString command;
	wxArrayString comment;
	wxArrayString type;
	
	wxFileInputStream input(stdpath.GetUserDataDir()+"/v2c/"+g_v2a+".v2a");
	wxJSONValue  roottpm;
	wxJSONReader reader;
	
	int numErrors = reader.Parse( input, &roottpm );
	if ( numErrors > 0 )  {
		wxMessageBox("ERROR: the JSON document is not well-formed");
	}
	wxJSONValue modules = roottpm["Actions"];
	if ( !modules.IsArray() ) {
	  wxMessageBox("ERROR: \'Actions\' must be a JSON array");
	}
	
	for ( int i = 0; i < modules.Size(); i++ ) {
		if(modules[i]["Trigger"].AsString() == edit) {
			tc_notification->SetValue(modules[i]["Notification"].AsString());
			tc_pretrig->SetValue(modules[i]["Pretrigger"].AsString());
			tc_trig->SetValue(modules[i]["Trigger"].AsString());
			tc_command->SetValue(modules[i]["Command"].AsString());
			tc_comment->SetValue(modules[i]["Comment"].AsString());
			c_type->SetStringSelection(modules[i]["Type"].AsString());
		}
	}
	html_v2ceditor->LoadPage("http://www.workinprogress.ca/KIKU/help/v2ceditor.html");
}
	
V2cEditor::V2cEditor(MainFrame *parent, wxString language, wxString v2a, wxString edit) : gui_v2ceditor( parent )
{
	wxStandardPathsBase& stdpath = wxStandardPaths::Get();
	
	themf = parent;
	g_language = language;
	g_v2a = v2a;
	autocomplete();
	b_add->SetLabel("Save");
	b_delete->Show(1);
	editmode = true;
	m_edit = edit;
	
	wxArrayString noti;
	wxArrayString pretrigger;
	wxArrayString trigger;
	wxArrayString command;
	wxArrayString comment;
	wxArrayString type;
	
	wxFileInputStream input(stdpath.GetUserDataDir()+"/v2c/shortcut.v2s");
	wxJSONValue  roottpm;
	wxJSONReader reader;
	
	int numErrors = reader.Parse( input, &roottpm );
	if ( numErrors > 0 )  {
		wxMessageBox("ERROR: the JSON document is not well-formed");
	}
	wxJSONValue modules = roottpm["Actions"];
	if ( !modules.IsArray() ) {
	  wxMessageBox("ERROR: \'Actions\' must be a JSON array");
	}
	
	for ( int i = 0; i < modules.Size(); i++ ) {
		if(modules[i]["Trigger"].AsString() == edit) {
			tc_notification->SetValue(modules[i]["Notification"].AsString());
			tc_pretrig->SetValue(modules[i]["Pretrigger"].AsString());
			tc_trig->SetValue(modules[i]["Trigger"].AsString());
			tc_command->SetValue(modules[i]["Command"].AsString());
			tc_comment->SetValue(modules[i]["Comment"].AsString());
			c_type->SetStringSelection(modules[i]["Type"].AsString());
		}
	}
	html_v2ceditor->LoadPage("http://www.workinprogress.ca/KIKU/help/v2ceditor.html");
}


V2cEditor::~V2cEditor()
{
}

// autocomplete
void V2cEditor::autocomplete()
{
	extern wxArrayString juliusformat_word;
	if(!juliusformat_word.GetCount()) {
		themf->autocomplete();
	}
	wxTextEntryBase *pretrig = tc_pretrig;
	wxTextEntryBase *trig = tc_trig;
	pretrig->AutoComplete(juliusformat_word);
	trig->AutoComplete(juliusformat_word);
}

bool V2cEditor::save()
{
	extern wxArrayString juliusformat_word;
	
	long index = juliusformat_word.Index(tc_trig->GetValue().Lower());
	if(index == wxNOT_FOUND) {
		wxMessageBox("You use a word that is not in the language dictionary");
		return 0;
	}
		
	if(tc_pretrig->GetValue() != "") {
		long index = juliusformat_word.Index(tc_pretrig->GetValue().Lower());
		if(index == wxNOT_FOUND) {
			wxMessageBox("You use a word that is not in the language dictionary");
			return 0;
		}
	}
	
	// TODO clean up
	// logic
	if(tc_command->GetValue() != "" && tc_trig->GetValue() != "") {
		if(!editmode) {
			// read temp v2a
			bool fileexist;
			if(g_v2a == "shortcut") {
				fileexist = wxFile::Exists(stdpath.GetUserDataDir()+"/v2c/shortcut.v2s");
			} else {
				fileexist = wxFile::Exists(stdpath.GetUserDataDir()+"/v2c/"+g_v2a+".v2a");
			}
			if(fileexist) {
				wxArrayString noti;
				wxArrayString pretrigger;
				wxArrayString trigger;
				wxArrayString command;
				wxArrayString comment;
				wxArrayString type;
				
				wxString fileinput;
				if(g_v2a == "shortcut") {
					fileinput = stdpath.GetUserDataDir()+"/v2c/shortcut.v2s";
				} else {
					fileinput = stdpath.GetUserDataDir()+"/v2c/"+g_v2a+".v2a";
				}
				wxFileInputStream input(fileinput);
				wxJSONValue  roottpm;
				wxJSONReader reader;
				
				int numErrors = reader.Parse( input, &roottpm );
				if ( numErrors > 0 )  {
					wxMessageBox("ERROR: the JSON document is not well-formed");
				}
				wxJSONValue modules = roottpm["Actions"];
				if (modules.IsArray() ) {
					for ( int i = 0; i < modules.Size(); i++ ) {
						noti.Add( modules[i]["Notification"].AsString() );
						pretrigger.Add( modules[i]["Pretrigger"].AsString() );
						trigger.Add( modules[i]["Trigger"].AsString() );
						command.Add( modules[i]["Command"].AsString() );
						comment.Add( modules[i]["Comment"].AsString() );
						type.Add( modules[i]["Type"].AsString() );
					}
				}
				
				wxJSONValue root;
				root.AddComment( "// voice2command - do not edit by hand", wxJSONVALUE_COMMENT_BEFORE );
				
				if(g_v2a != "shortcut") {
					root["ProcessName"] = g_v2a;
				}
				
				wxJSONValue actions;
				actions["Notification"] = tc_notification->GetValue();
				actions["Pretrigger"] = tc_pretrig->GetValue();
				actions["Trigger"] = tc_trig->GetValue();
				actions["Command"] = tc_command->GetValue();
				actions["Comment"] = tc_comment->GetValue();
				actions["Type"] = c_type->GetStringSelection();
				root["Actions"].Append(actions);
				
				// temp
				for(unsigned int i = 0; i < noti.GetCount(); i++) {
					wxJSONValue actions;
					actions["Notification"] = noti.Item(i);
					actions["Pretrigger"] = pretrigger.Item(i);
					actions["Trigger"] = trigger.Item(i);
					actions["Command"] = command.Item(i);
					actions["Comment"] = comment.Item(i);
					actions["Type"] = type.Item(i);
					root["Actions"].Append(actions);	
				}
			
				// check if trigger is unique
				long indext = trigger.Index(tc_trig->GetValue().Lower());
				if(indext != wxNOT_FOUND) {
					wxMessageBox("You already use that word (trigger)");
					return 0;
				}

				wxJSONWriter writer( wxJSONWRITER_STYLED | wxJSONWRITER_WRITE_COMMENTS );
				wxString  jsonText;
				writer.Write( root, jsonText );
				
				wxString filewrite;
				if(g_v2a == "shortcut") {
					filewrite = stdpath.GetUserDataDir()+"/v2c/shortcut.v2s";
				} else {
					filewrite = stdpath.GetUserDataDir()+"/v2c/"+g_v2a+".v2a";
				}
				wxFile myFile(filewrite, wxFile::write);
				myFile.Write(jsonText);
				myFile.Close();
				
				// reload edit in v2capplication
				if(g_v2a == "shortcut") {
					themf->V2cShortcutReload();
				} else {
					theparent->reloadedit();
				}
				
			// new
			} else {
				wxJSONValue root;
				root.AddComment( "// voice2command - do not edit by hand", wxJSONVALUE_COMMENT_BEFORE );
				
				if(g_v2a != "shortcut") {
					root["ProcessName"] = g_v2a;
				}
				
				wxJSONValue actions;
				actions["Notification"] = tc_notification->GetValue();
				actions["Pretrigger"] = tc_pretrig->GetValue();
				actions["Trigger"] = tc_trig->GetValue();
				actions["Command"] = tc_command->GetValue();
				actions["Comment"] = tc_comment->GetValue();
				actions["Type"] = c_type->GetStringSelection();
				root["Actions"].Append(actions);		

				wxJSONWriter writer( wxJSONWRITER_STYLED | wxJSONWRITER_WRITE_COMMENTS );
				wxString  jsonText;
				writer.Write( root, jsonText );
				wxString filewrite;
				if(g_v2a == "shortcut") {
					filewrite = stdpath.GetUserDataDir()+"/v2c/shortcut.v2s";
				} else {
					filewrite = stdpath.GetUserDataDir()+"/v2c/"+g_v2a+".v2a";
				}
				wxFile myFile(filewrite, wxFile::write);
				myFile.Write(jsonText);
				myFile.Close();
				
				// reload edit in v2capplication
				if(g_v2a == "shortcut") {
					themf->V2cShortcutReload();
				} else {
					theparent->reloadedit();
				}
			}
			
			return 1;
		
		} else { // edit mode
		
				wxArrayString noti;
				wxArrayString pretrigger;
				wxArrayString trigger;
				wxArrayString command;
				wxArrayString comment;
				wxArrayString type;
				wxArrayString triggerunique;

				wxString fileinput;
				if(g_v2a == "shortcut") {
					fileinput = stdpath.GetUserDataDir()+"/v2c/shortcut.v2s";
				} else {
					fileinput = stdpath.GetUserDataDir()+"/v2c/"+g_v2a+".v2a";
				}
				wxFileInputStream input(fileinput);
				wxJSONValue  roottpm;
				wxJSONReader reader;
				
				int numErrors = reader.Parse( input, &roottpm );
				if ( numErrors > 0 )  {
					wxMessageBox("ERROR: the JSON document is not well-formed");
				}
				wxJSONValue modules = roottpm["Actions"];
				if (modules.IsArray() ) {
					for ( int i = 0; i < modules.Size(); i++ ) {
						triggerunique.Add( modules[i]["Trigger"].AsString() );
					}
					for ( int i = 0; i < modules.Size(); i++ ) {
						if(m_edit == modules[i]["Trigger"].AsString()) {
							noti.Add(tc_notification->GetValue());
							pretrigger.Add(tc_pretrig->GetValue());
							trigger.Add(tc_trig->GetValue());
							command.Add(tc_command->GetValue());
							comment.Add(tc_comment->GetValue());
							type.Add(c_type->GetStringSelection());
						} else {
							noti.Add( modules[i]["Notification"].AsString() );
							pretrigger.Add( modules[i]["Pretrigger"].AsString() );
							trigger.Add( modules[i]["Trigger"].AsString() );
							command.Add( modules[i]["Command"].AsString() );
							comment.Add( modules[i]["Comment"].AsString() );
							type.Add( modules[i]["Type"].AsString() );
						}
					}
				}
				
				wxJSONValue root;
				root.AddComment( "// voice2command - do not edit by hand", wxJSONVALUE_COMMENT_BEFORE );
				if(g_v2a != "shortcut") {
					root["ProcessName"] = g_v2a;
				}
				
				// temp
				for(unsigned int i = 0; i < noti.GetCount(); i++) {
					wxJSONValue actions;
					actions["Notification"] = noti.Item(i);
					actions["Pretrigger"] = pretrigger.Item(i);
					actions["Trigger"] = trigger.Item(i);
					actions["Command"] = command.Item(i);
					actions["Comment"] = comment.Item(i);
					actions["Type"] = type.Item(i);
					root["Actions"].Append(actions);	
				}
				
				// check if trigger is unique
				if(m_edit != tc_trig->GetValue()) {
					long indext = triggerunique.Index(tc_trig->GetValue().Lower());
					if(indext != wxNOT_FOUND) {
						wxMessageBox("You already use that word (trigger)");
						return 0;
					}
				}

				wxJSONWriter writer( wxJSONWRITER_STYLED | wxJSONWRITER_WRITE_COMMENTS );
				wxString  jsonText;
				writer.Write( root, jsonText );
				wxString filewrite;
				if(g_v2a == "shortcut") {
					filewrite = stdpath.GetUserDataDir()+"/v2c/shortcut.v2s";
				} else {
					filewrite = stdpath.GetUserDataDir()+"/v2c/"+g_v2a+".v2a";
				}
				wxFile myFile(filewrite, wxFile::write);
				myFile.Write(jsonText);
				myFile.Close();
				
				// reload edit in v2capplication
				if(g_v2a == "shortcut") {
					themf->V2cShortcutReload();
				} else {
					theparent->reloadedit();
				}
				return 1;
		}
	} else {
		wxMessageBox("You need at least a trigger and a command");
		return 0;
	}
}

// add / edit
void V2cEditor::Onb_add( wxCommandEvent& event )
{
	if(save()) {
		Destroy();
	}
}

// only for edit: delete
void V2cEditor::Onb_delete(wxCommandEvent& event)
{
	wxArrayString noti;
	wxArrayString pretrigger;
	wxArrayString trigger;
	wxArrayString command;
	wxArrayString comment;
	wxArrayString type;
	
	wxString fileinput;
	if(g_v2a == "shortcut") {
		fileinput = stdpath.GetUserDataDir()+"/v2c/shortcut.v2s";
	} else {
		fileinput = stdpath.GetUserDataDir()+"/v2c/"+g_v2a+".v2a";
	}
	wxFileInputStream input(fileinput);
	wxJSONValue  roottpm;
	wxJSONReader reader;
	
	int numErrors = reader.Parse( input, &roottpm );
	if ( numErrors > 0 )  {
		wxMessageBox("ERROR: the JSON document is not well-formed");
	}
	wxJSONValue modules = roottpm["Actions"];
	if ( !modules.IsArray() ) {
	  wxMessageBox("ERROR: \'Actions\' must be a JSON array");
	}
	
	for ( int i = 0; i < modules.Size(); i++ ) {
		if(modules[i]["Trigger"].AsString() != m_edit) {
			noti.Add( modules[i]["Notification"].AsString() );
			pretrigger.Add( modules[i]["Pretrigger"].AsString() );
			trigger.Add( modules[i]["Trigger"].AsString() );
			command.Add( modules[i]["Command"].AsString() );
			comment.Add( modules[i]["Comment"].AsString() );
			type.Add( modules[i]["Type"].AsString() );
		}
	}
	
	wxJSONValue root;
	root.AddComment( "// voice2command - do not edit by hand", wxJSONVALUE_COMMENT_BEFORE );
	if(g_v2a != "shortcut") {
		root["ProcessName"] = g_v2a;
	}

	// temp
	for(unsigned int i = 0; i < noti.GetCount(); i++) {
		wxJSONValue actions;
		actions["Notification"] = noti.Item(i);
		actions["Pretrigger"] = pretrigger.Item(i);
		actions["Trigger"] = trigger.Item(i);
		actions["Command"] = command.Item(i);
		actions["Comment"] = comment.Item(i);
		actions["Type"] = type.Item(i);
		root["Actions"].Append(actions);	
	}

	wxJSONWriter writer( wxJSONWRITER_STYLED | wxJSONWRITER_WRITE_COMMENTS );
	wxString  jsonText;
	writer.Write( root, jsonText );
	wxString filewrite;
	if(g_v2a == "shortcut") {
		filewrite = stdpath.GetUserDataDir()+"/v2c/shortcut.v2s";
	} else {
		filewrite = stdpath.GetUserDataDir()+"/v2c/"+g_v2a+".v2a";
	}
	wxFile myFile(filewrite, wxFile::write);
	myFile.Write(jsonText);
	myFile.Close();
	
	// reload edit in v2capplication
	if(g_v2a == "shortcut") {
		themf->V2cShortcutReload();
	} else {
		theparent->reloadedit();
	}
			
	Destroy();
}

// cancel
void V2cEditor::Onb_cancel(wxCommandEvent& event)
{
	Destroy();
}

void V2cEditor::OnLink(wxHtmlLinkEvent& event) {
	wxHtmlLinkInfo link;
	link = event.GetLinkInfo();
	wxLaunchDefaultBrowser(link.GetHref());
}