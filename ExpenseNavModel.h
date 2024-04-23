#ifndef EXPENSENAVMODEL_H
#define EXPENSENAVMODEL_H

#include "wx/wx.h"
#include "wx/dataview.h"
#include "clib.h"

typedef struct {
    int year;
    int month;
    double amt;
} item_total_t;

class ExpenseNavModel : public wxDataViewModel {
public:
    ExpenseNavModel(array_t *itemtotals);
    ~ExpenseNavModel();

    virtual wxDataViewItem GetParent(const wxDataViewItem &item) const override;
    virtual bool IsContainer(const wxDataViewItem &item) const override;
    virtual unsigned int GetChildren(const wxDataViewItem &parent, wxDataViewItemArray &array) const override;

    int Compare(const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending) const override;
    virtual void GetValue(wxVariant &variant, const wxDataViewItem &item, unsigned int col) const override;
    virtual bool SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col) override;
    virtual bool IsEnabled(const wxDataViewItem &item, unsigned int col) const override;

private:
    array_t *m_itemtotals;

};

#endif

