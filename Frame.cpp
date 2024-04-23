#include <stdio.h>

#include "wx/wx.h"
#include "wx/window.h"
#include "wx/dataview.h"

#include "clib.h"
#include "App.h"
#include "Frame.h"
#include "ExpenseNavModel.h"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_DATAVIEW_SELECTION_CHANGED(ID_DATAVIEW, MyFrame::OnDataViewSelectionChanged)
wxEND_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(640,480)) {
    setlocale(LC_NUMERIC, "");

    CreateControls();
}

MyFrame::~MyFrame() {
}

item_total_t *item_total_new(int year, int month, double amt) {
    item_total_t *it = (item_total_t *) malloc(sizeof(item_total_t));
    it->year = year;
    it->month = month;
    it->amt = amt;
    return it;
}

void MyFrame::CreateControls() {
    wxBoxSizer *top;
    wxBoxSizer *hbox;
    wxDataViewCtrl *dv;
    ExpenseNavModel *m;
    array_t *itemtotals;

    itemtotals = array_new(0);
    array_add(itemtotals, item_total_new(2024, 0, 123.45));
    array_add(itemtotals, item_total_new(2023, 0, 678.90));
    array_add(itemtotals, item_total_new(2022, 0, 10.90));
    array_add(itemtotals, item_total_new(2021, 0, 23.05));
    array_add(itemtotals, item_total_new(2020, 0, 1000.10));
    array_add(itemtotals, item_total_new(2024, 1, 1.23));
    array_add(itemtotals, item_total_new(2024, 2, 100123.23));
    array_add(itemtotals, item_total_new(2024, 3, 200123.23));
    array_add(itemtotals, item_total_new(2024, 4, 315457.23));
    array_add(itemtotals, item_total_new(2024, 5, 1000050.23));
    array_add(itemtotals, item_total_new(2024, 6, 1.23));
    array_add(itemtotals, item_total_new(2024, 7, 1.23));
    array_add(itemtotals, item_total_new(2024, 8, 1.23));
    array_add(itemtotals, item_total_new(2024, 9, 1.23));
    array_add(itemtotals, item_total_new(2024, 10, 1.23));
    array_add(itemtotals, item_total_new(2024, 11, 1.23));
    array_add(itemtotals, item_total_new(2024, 12, 1.23));
    array_add(itemtotals, item_total_new(2023, 1, 1.23));
    array_add(itemtotals, item_total_new(2023, 2, 1.23));
    array_add(itemtotals, item_total_new(2023, 3, 1.23));
    array_add(itemtotals, item_total_new(2023, 4, 1.23));
    array_add(itemtotals, item_total_new(2023, 5, 1.23));
    array_add(itemtotals, item_total_new(2023, 6, 1.23));
    array_add(itemtotals, item_total_new(2023, 7, 1.23));
    array_add(itemtotals, item_total_new(2023, 8, 1.23));
    array_add(itemtotals, item_total_new(2023, 9, 1.23));
    array_add(itemtotals, item_total_new(2023, 10, 1.23));
    array_add(itemtotals, item_total_new(2023, 11, 1.23));
    array_add(itemtotals, item_total_new(2023, 12, 1.23));

    dv = new wxDataViewCtrl(this, ID_DATAVIEW, wxDefaultPosition, wxSize(300,-1), wxDV_NO_HEADER);
    dv->AppendTextColumn("Date", 0, wxDATAVIEW_CELL_INERT, -1, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE);
    dv->AppendTextColumn("Total", 1, wxDATAVIEW_CELL_INERT, -1, wxALIGN_RIGHT, wxDATAVIEW_COL_RESIZABLE);
    m = new ExpenseNavModel(itemtotals);
    dv->AssociateModel(m);
    m->DecRef();

    hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(dv, 0, wxEXPAND, 0);
    hbox->AddStretchSpacer();

    top = new wxBoxSizer(wxVERTICAL);
    top->Add(hbox, 1, wxEXPAND|wxALL, 5);
    SetSizer(top);
}

void MyFrame::OnDataViewSelectionChanged(wxDataViewEvent &event) {
    item_total_t *it = (item_total_t *) event.GetItem().GetID();
    if (it == NULL)
        return;
    printf("select year: %d, month: %d\n", it->year, it->month);
}


