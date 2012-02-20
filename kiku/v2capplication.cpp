/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#include "v2capplication.h"
#include "main.h"

// add
V2cApplication::V2cApplication(wxWindow *parent, wxString language) : gui_v2capplication( parent )
{
	stdpath = wxStandardPaths::Get();
	
	mf = (MainFrame *)parent;
	editmode = false;
	g_language = language;
	// gui
	b_delete->Show(0);
	c_editaction->Enable(0);
	b_editaction->Enable(0);
	
	// autocomplete
	autocomplete();
	autocompleteprocess();
	
	// avoid name clash
	wxDir dir(stdpath.GetUserDataDir()+"/v2c/");
	wxString filename;
	bool cont = dir.GetFirst(&filename, "*.v2a", wxDIR_FILES);
	while ( cont )
	{
		v2a.Add(filename.Mid(0, filename.Length() - 4));
		cont = dir.GetNext(&filename);
	}
}

// edit
V2cApplication::V2cApplication(wxWindow *parent, wxString language, wxString v2c) : gui_v2capplication( parent )
{	
	stdpath = wxStandardPaths::Get();
	
	mf = (MainFrame *)parent;
	editmode = true;
	bugpn = false;
	g_language = language;
	autocomplete();
	v2afile = v2c;
	
	b_addaction->Enable(1);
	tc_notification->Enable(1);
	tc_pretrig->Enable(1);
	tc_trig->Enable(1);
	tc_command->Enable(1);
	b_save->Enable(1);
	
	// read v2a
	wxFileInputStream input(stdpath.GetUserDataDir()+"/v2c/"+v2afile+".v2a");
	wxJSONValue  roottpm;
	wxJSONReader reader;
	
	int numErrors = reader.Parse( input, &roottpm );
	if ( numErrors > 0 )  {
		wxMessageBox("ERROR: the JSON document is not well-formed");
	}
	
	if(roottpm["Launcher"]["Notification"].AsString() != "null") {
		tc_notification->SetValue(roottpm["Launcher"]["Notification"].AsString() );
	}
	if(roottpm["Launcher"]["Pretrigger"].AsString() != "null") {
	tc_pretrig->SetValue(roottpm["Launcher"]["Pretrigger"].AsString() );
	}
	if(roottpm["Launcher"]["Trigger"].AsString() != "null") {
	tc_trig->SetValue(roottpm["Launcher"]["Trigger"].AsString() );
	}
	if(roottpm["Launcher"]["Command"].AsString() != "null") {
	tc_command->SetValue(roottpm["Launcher"]["Command"].AsString() );
	}
	
	wxJSONValue modules = roottpm["Actions"];
	if (modules.IsArray() ) {
		for ( int i = 0; i < modules.Size(); i++ ) {
			c_editaction->Append(modules[i]["Trigger"].AsString());
		}
	}
	if(c_editaction->GetCount()) {
		c_editaction->SetSelection(0);
		b_editaction->Enable(1);
	} else {
		b_editaction->Enable(0);
	}
}

void V2cApplication::reloadedit()
{
	c_editaction->Clear();
	
	wxFileInputStream input(stdpath.GetUserDataDir()+"/v2c/"+tc_processname->GetValue()+".v2a");
	wxJSONValue  root;
	wxJSONReader reader;
	
	int numErrors = reader.Parse( input, &root );
	if ( numErrors > 0 )  {
		wxMessageBox("ERROR: the JSON document is not well-formed");
	}

	wxJSONValue modules = root["Actions"];
	if (modules.IsArray() ) {
		for ( int i = 0; i < modules.Size(); i++ ) {
			c_editaction->Append( modules[i]["Trigger"].AsString().Lower() );
		}
		c_editaction->Enable(1);
		b_editaction->Enable(1);
		c_editaction->SetSelection(0);
	} else {
		c_editaction->Enable(0);
		b_editaction->Enable(0);
	}
	
}
// autocomplete
void V2cApplication::autocomplete()
{
	extern wxArrayString juliusformat_word;
	if(!juliusformat_word.GetCount()) {
		mf->autocomplete();
	}
	wxTextEntryBase *pretrig = tc_pretrig;
	wxTextEntryBase *trig = tc_trig;
	pretrig->AutoComplete(juliusformat_word, 3);
	trig->AutoComplete(juliusformat_word, 3);
}

void V2cApplication::autocompleteprocess()
{
	wxTextEntryBase *processname = tc_processname;
	wxArrayString completion_choices;
	
	
	int bytesread;
	const int BUFFERSIZE = 1000;
	
    char chrarry_CommandLinePath[100];
    char chrarry_NameOfProcess[BUFFERSIZE];
	char chrarry_OnlyNameOfProcess[BUFFERSIZE];
    char* chrptr_StringToCompare = NULL ;
    pid_t pid_ProcessIdentifier = (pid_t) -1 ;
    struct dirent* de_DirEntity = NULL ;
    DIR* dir_proc = NULL ;
    dir_proc = opendir(PROC_DIRECTORY) ;
    if (dir_proc == NULL)
    {
        wxMessageBox("Couldn't open the " PROC_DIRECTORY " directory");
    }

    while ( (de_DirEntity = readdir(dir_proc)) )
    {
        if (de_DirEntity->d_type == DT_DIR)
        {
            if (IsNumeric(de_DirEntity->d_name))
            {
                strcpy(chrarry_CommandLinePath, PROC_DIRECTORY) ;
                strcat(chrarry_CommandLinePath, de_DirEntity->d_name) ;
                strcat(chrarry_CommandLinePath, "/cmdline") ;
                FILE* fd_CmdLineFile = fopen (chrarry_CommandLinePath, "rt") ;  // open the file for reading text
                if (fd_CmdLineFile)
                {
					int fsrs = fscanf(fd_CmdLineFile, "%s", chrarry_OnlyNameOfProcess) ; // read from /proc/<NR>/cmdline
					// just avoiding -Wunused-variable
					(void)fsrs;
					rewind(fd_CmdLineFile);
					bytesread = fread(chrarry_NameOfProcess, 1, BUFFERSIZE, fd_CmdLineFile);
					for (int i = 0; i < bytesread; ++i)
						if (chrarry_NameOfProcess[i] == '\0')
							chrarry_NameOfProcess[i] = ' ';
					chrarry_NameOfProcess[bytesread] = '\0';
					fclose(fd_CmdLineFile);
	
                    if (strrchr(chrarry_OnlyNameOfProcess, '/')) {
                        chrptr_StringToCompare = strrchr(chrarry_OnlyNameOfProcess, '/') +1;
                    } else {
                        chrptr_StringToCompare = chrarry_OnlyNameOfProcess;
						wxString stc(chrptr_StringToCompare, wxConvUTF8);
						if(stc.Find("python") != wxNOT_FOUND) {
								chrptr_StringToCompare = strrchr(chrarry_NameOfProcess, '/') +1;
						}
					}
					
					//printf("Process name: %s\n", chrarry_NameOfProcess);
					//printf("Pure Process name: %s\n", chrptr_StringToCompare );

					// don't show basic process
					pid_ProcessIdentifier = (pid_t) atoi(de_DirEntity->d_name) ;
					if(pid_ProcessIdentifier > 1500) {
						wxString stc(chrptr_StringToCompare, wxConvUTF8);
						completion_choices.push_back(stc.Trim());
					}
					
				}
			}
		}
	}
	closedir(dir_proc) ;
	processname->AutoComplete(completion_choices);

}

int V2cApplication::IsNumeric(const char* ccharptr_CharacterList)
{
    for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}

V2cApplication::~V2cApplication()
{
}

void V2cApplication::OnCloseDialog(wxCloseEvent& event)
{
	Destroy();
}

// add action
void V2cApplication::Onb_addaction( wxCommandEvent& event )
{
	// now read only
	tc_processname->SetWindowStyle(wxTE_READONLY);
	
	// show v2c editor
	dv2ceditor = new V2cEditor(this, g_language, tc_processname->GetValue(), this);
	dv2ceditor->ShowModal();
}

void V2cApplication::Onb_editaction( wxCommandEvent& event )
{
	// show v2c editor
	dv2ceditor = new V2cEditor(this, g_language, tc_processname->GetValue(), this, c_editaction->GetStringSelection());
	dv2ceditor->ShowModal();	
}

// save
void V2cApplication::Onb_save( wxCommandEvent& event )
{
	if(save()) {
		Destroy();
	}
}

bool V2cApplication::save()
{
	extern wxArrayString juliusformat_word;
	
	// logic
	if(tc_command->GetValue() != "" && tc_trig->GetValue() == "") {
		wxMessageBox("Specify the trigger word for the launcher.");
		return 0;
	}
	
	if(tc_trig->GetValue() == "" && c_editaction->GetCount() == 0) {
		wxMessageBox("You need to at least provide a launcher or an action.");
		return 0;
	}
	
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
	
	// v2a final save
	wxJSONValue root;
	root.AddComment( "// voice2command - do not edit by hand", wxJSONVALUE_COMMENT_BEFORE );
	root["ProcessName"] = tc_processname->GetValue();

	// check if we have some actions
	if(wxFile::Exists(stdpath.GetUserDataDir()+"/v2c/"+tc_processname->GetValue()+".v2a")) {
		wxArrayString noti;
		wxArrayString pretrigger;
		wxArrayString trigger;
		wxArrayString command;
		wxArrayString comment;
		wxArrayString type;
		
		wxFileInputStream input(stdpath.GetUserDataDir()+"/v2c/"+tc_processname->GetValue()+".v2a");
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
		
		}
		

	}
	
	// if launcher trigger
	if(tc_trig->GetValue() != "") {
		root["Launcher"]["Notification"] = tc_notification->GetValue();
		root["Launcher"]["Pretrigger"] = tc_pretrig->GetValue();
		root["Launcher"]["Trigger"] = tc_trig->GetValue();
		root["Launcher"]["Command"] = tc_command->GetValue();
		root["Launcher"]["Type"] = _T("shell");
	}

	wxJSONWriter writer( wxJSONWRITER_STYLED | wxJSONWRITER_WRITE_COMMENTS );
	wxString  jsonText;
	writer.Write( root, jsonText );
	wxFile myFile(stdpath.GetUserDataDir()+"/v2c/"+tc_processname->GetValue()+".v2a", wxFile::write);
	myFile.Write(jsonText);
	myFile.Close();
	
	// dictionary save & reload application list
	mf->V2cApplicationReload();
	return 1;
}

// gui logic
void V2cApplication::OnUpdateUI( wxUpdateUIEvent& event )
{
	if(!editmode) {
		wxObject *updObj = event.GetEventObject();
		if(updObj == b_addaction)
		{
			if(tc_processname->GetValue() != "") {
				if(v2a.Index(tc_processname->GetValue()) == wxNOT_FOUND) {
					b_addaction->Enable(1);
					tc_notification->Enable(1);
					tc_pretrig->Enable(1);
					tc_trig->Enable(1);
					tc_command->Enable(1);
					b_save->Enable(1);
				} else {
					b_addaction->Enable(0);
					tc_notification->Enable(0);
					tc_pretrig->Enable(0);
					tc_trig->Enable(0);
					tc_command->Enable(0);
					b_save->Enable(0);
				}
			} else {
				b_addaction->Enable(0);
				tc_notification->Enable(0);
				tc_pretrig->Enable(0);
				tc_trig->Enable(0);
				tc_command->Enable(0);
				b_save->Enable(0);
			}
		}
		else
		{
			event.Skip();
		}
	} else {
		if(!bugpn) {
			tc_processname->SetValue(v2afile);
			tc_processname->SetWindowStyle(wxTE_READONLY);
			bugpn = true;
		}
	}
}

// cancel
void V2cApplication::Onb_cancel(wxCommandEvent& event)
{
	Destroy();
}

void V2cApplication::Ontc_processname(wxCommandEvent& event)
{
	if(!editmode) {
		tc_command->SetValue(tc_processname->GetValue());
	}
}

void V2cApplication::Onb_delete( wxCommandEvent& event )
{
	if(wxRemoveFile(stdpath.GetUserDataDir()+"/v2c/"+v2afile+".v2a")) {
		mf->V2cApplicationReload();
		Destroy();
	} else {
		wxMessageBox("Problem delete the file");
	}
}

