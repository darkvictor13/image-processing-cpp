#include "main_frame.hpp"

MainFrame::MainFrame() :
		wxFrame(NULL, wxID_ANY, "Main Frame", wxPoint(), wxSize(800, 600)),
		img(new Image("../images/full_hd.jpg")),
		drawPane(new ImagePanel(this, "../images/full_hd.jpg", wxBITMAP_TYPE_JPEG)),
		sizer(new wxBoxSizer(wxHORIZONTAL)),
		menu_metods(new wxMenu()),
		menu_file(new wxMenu()),
		menu_bar(new wxMenuBar()) {

	debug("Construindo MainFrame\n");

	SetSizer(sizer);
	sizer->Add(drawPane, 1, wxEXPAND);

	menu_metods->Append(ID_LOW_PASS, "&Realizar passa baixa...\tCtrl-L");
	menu_metods->Append(ID_HIGH_PASS, "&Realizar passa alta...\tCtrl-H");
	menu_metods->Append(ID_THRESHOLD, "&Realizar threshold");
	menu_metods->Append(ID_GRAY, wxT("&Realizar transformação escala de cinsa"));
	menu_metods->Append(ID_ROBERTS, "&a");
	menu_metods->Append(ID_PREWITT, "&a");
	menu_metods->Append(ID_SOBEL, "&a");
	menu_metods->Append(ID_LOG, "&a");
	menu_metods->Append(ID_ZEROCROSS, "&a");
	menu_metods->Append(ID_CANNY, "&a");
	menu_metods->Append(ID_NOISE, "&a");
	menu_metods->Append(ID_WATERSHED, "&a");
	menu_metods->Append(ID_HISTOGRAM, "&a");
	menu_metods->Append(ID_HISTOGRAM_AJUST, "&a");
	menu_metods->Append(ID_COUNT, "&a");

	menu_file->Append(ID_OPEN, "Abrir uma imagem\tCtrl-O",
		wxT("Selecionando essa opção será levado ao gerenciador de arquivos do sistema"));
	menu_file->Append(ID_REFRESH, "&Recarregar o conteudo da imagem...\tCtrl-R");
	menu_file->Append(ID_SAVE_FILE, "&Salvando a imagem atual...\tCtrl-S",
		"Abre um menu para selecionar onde salvar a imagem");
	menu_file->AppendSeparator();
	menu_file->Append(ID_UNDO, wxT("&Desfazer ação...\tCtrl-Z"));
	menu_file->Append(ID_REDO, wxT("&Refazer ação...\tCtrl-Y"));

    menu_bar->Append(menu_file, "File");
    menu_bar->Append(menu_metods, "Metodos");

	SetMenuBar(menu_bar);
	CreateStatusBar();
    SetStatusText("WxWidgets main frame!");
	Centre();

	Bind(wxEVT_MENU, &MainFrame::onOpen, this, ID_OPEN);
	Bind(wxEVT_MENU, &MainFrame::onSave, this, ID_SAVE_FILE);
	Bind(wxEVT_MENU, &MainFrame::onUndo, this, ID_UNDO);
	Bind(wxEVT_MENU, &MainFrame::onRedo, this, ID_REDO);
	Bind(wxEVT_MENU, &MainFrame::onRefresh, this, ID_REFRESH);

	Bind(wxEVT_MENU, &MainFrame::onLowPass, this, ID_LOW_PASS);
	Bind(wxEVT_MENU, &MainFrame::onHighPass, this, ID_HIGH_PASS);
	Bind(wxEVT_MENU, &MainFrame::onThreshold, this, ID_THRESHOLD);
	Bind(wxEVT_MENU, &MainFrame::onGray, this, ID_GRAY);
	Bind(wxEVT_MENU, &MainFrame::onRoberts, this, ID_ROBERTS);
	Bind(wxEVT_MENU, &MainFrame::onPrewitt, this, ID_PREWITT);
	Bind(wxEVT_MENU, &MainFrame::onSobel, this, ID_SOBEL);
	Bind(wxEVT_MENU, &MainFrame::onLog, this, ID_LOG);
	Bind(wxEVT_MENU, &MainFrame::onZerocross, this, ID_ZEROCROSS);
	Bind(wxEVT_MENU, &MainFrame::onCanny, this, ID_CANNY);
	Bind(wxEVT_MENU, &MainFrame::onNoise, this, ID_NOISE);
	Bind(wxEVT_MENU, &MainFrame::onWatershed, this, ID_WATERSHED);
	Bind(wxEVT_MENU, &MainFrame::onHistogram, this, ID_HISTOGRAM);
	Bind(wxEVT_MENU, &MainFrame::onHistogramAjust, this, ID_HISTOGRAM_AJUST);
	Bind(wxEVT_MENU, &MainFrame::onCount, this, ID_COUNT);
}

void MainFrame::onOpen(wxCommandEvent& event) {
	if (!openImage()) {
		showError(wxT("Error loading file"));
	}
}

void MainFrame::onSave(wxCommandEvent& event) {

}

void MainFrame::onUndo(wxCommandEvent& event) {
	showError("Rodou o Undo");
}

void MainFrame::onRedo(wxCommandEvent& event) {

}

void MainFrame::onRefresh(wxCommandEvent& event) {
	int w, h;
	this->GetSize(&w, &h);
	this->SetSize(w - 1, h - 1);
	//this->SetSize(w, h);
}

void MainFrame::onLowPass(wxCommandEvent& event) {
	long temp = 0;
	int mat_filter_size;
	auto dialog_size = new wxTextEntryDialog(this, wxT("Entre com o tamanho da máscara"));
	//auto d = new wxAnyChoiceDialog;

	dialog_size->SetTextValidator(wxFILTER_DIGITS);
	while (1) {
		if (dialog_size->ShowModal() == wxID_OK) {
			dialog_size->GetValue().ToLong(&temp);
			if (temp % 2) break;
		}else {
			return; // o usuario cancelou o menu
		}
		dialog_size->SetValue("3");
		showError("O valor entrado precisa ser impar");
	}
	mat_filter_size = static_cast<int>(temp);

	std::cout << showQuestion(wxT("Deseja usar filtro da mediana? Caso contrario será usado filtro da média")) << '\n';

/*
	auto dialog_metod = new wxMessageDialog(this, "Deseja Utilizar filtro da media?");
	//if (dialog_metod->SetYesNoLabels(_("&Quit"), _("&Don't quit"))) {
	if (dialog_metod->SetYesNoLabels("Sim", "Nao")) {
		dialog_metod->SetMessage(_("What do you want to do?"));
	}else {// buttons have standard "Yes"/"No" values, so rephrase the question
		dialog_metod->SetMessage(_("Do you really want to quit?"));
	}
	if (dialog_metod->ShowModal() == wxID_YES) {
	}else {
		showError("Vc escolheu nao");
	}
*/

	img->medianBlur(mat_filter_size);
	drawPane->changeImage(img->toWxImage());
}

void MainFrame::onHighPass(wxCommandEvent& event) {

}

void MainFrame::onThreshold(wxCommandEvent& event) {
	
}

void MainFrame::onGray(wxCommandEvent& event) {
	img->toGray();
	drawPane->changeImage(img->toWxImage());
}

void MainFrame::onRoberts(wxCommandEvent& event) {
	
}

void MainFrame::onPrewitt(wxCommandEvent& event) {
	
}

void MainFrame::onSobel(wxCommandEvent& event) {
	
}

void MainFrame::onLog(wxCommandEvent& event) {
	
}

void MainFrame::onZerocross(wxCommandEvent& event) {
	
}

void MainFrame::onCanny(wxCommandEvent& event) {
	
}

void MainFrame::onNoise(wxCommandEvent& event) {
	
}

void MainFrame::onWatershed(wxCommandEvent& event) {
	
}

void MainFrame::onHistogram(wxCommandEvent& event) {
	
}

void MainFrame::onHistogramAjust(wxCommandEvent& event) {
	
}

void MainFrame::onCount(wxCommandEvent& event) {
	
}

bool MainFrame::openImage() {
	auto dialog = new wxFileDialog(
		this, "Escolha uma imagem jpg para abrir", "../images", wxEmptyString, "*.jpg"
	);
	
	if (dialog->ShowModal() == wxID_OK) {
		img->loadImage(dialog->GetPath().ToStdString());
		drawPane->changeImage(img->toWxImage());
		return true;
	}
	return false;
}

void MainFrame::showError(const wxString &message) {
	auto dial = new wxMessageDialog (
		this, message, wxT("Error"), wxOK | wxICON_ERROR
	);
	dial->ShowModal();
}

bool MainFrame::showQuestion(const wxString &message) {
	wxMessageDialog *dial = new wxMessageDialog(
		this,
		message, wxT("Question"),
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION
	);

	return dial->ShowModal() == wxID_YES;
}

MainFrame::~MainFrame() {
	debug("Destruindo MainFrame\n");
}
