#include <assert.h>
#include "wx/wx.h"
#include "wx/dataview.h"
#include "clib.h"
#include "ExpenseNavModel.h"

ExpenseNavModel::ExpenseNavModel(array_t *itemtotals) {
    m_itemtotals = itemtotals;
}
ExpenseNavModel::~ExpenseNavModel() {
}

wxDataViewItem ExpenseNavModel::GetParent(const wxDataViewItem &item) const {
    item_total_t *it = (item_total_t *) item.GetID();

    // null root node
    if (it == NULL)
        return wxDataViewItem(NULL);
    assert(it->year != 0);

    // year total: return null root node parent
    if (it->month == 0)
        return wxDataViewItem(NULL);

    // month total: return matching year total node
    for (size_t i=0; i < m_itemtotals->len; i++) {
        item_total_t *t = (item_total_t *) m_itemtotals->items[i];
        if (it->year == t->year && t->month == 0)
            return wxDataViewItem(t);

        if (t->month != 0)
            break;
    }

    return wxDataViewItem(NULL);
}
bool ExpenseNavModel::IsContainer(const wxDataViewItem &item) const {
    item_total_t *it = (item_total_t *) item.GetID();

    // null root node has children
    if (it == NULL)
        return true;
    assert(it->year != 0);

    // year total has children
    if (it->month == 0)
        return true;

    // month total has no children
    return false;
}
unsigned int ExpenseNavModel::GetChildren(const wxDataViewItem &parent, wxDataViewItemArray &array) const {
    item_total_t *it = (item_total_t *) parent.GetID();
    item_total_t *t;

    // null root node returns all year totals
    if (it == NULL) {
        for (size_t i=0; i < m_itemtotals->len; i++) {
            t = (item_total_t *) m_itemtotals->items[i];

            if (t->month != 0)
                break;

            assert(t->year != 0 && t->month == 0);
            array.Add(wxDataViewItem((void *) t));
        }
        return array.size();
    }
    assert(it->year != 0);

    // year total node: return month children
    if (it->month == 0) {
        for (size_t i=0; i < m_itemtotals->len; i++) {
            t = (item_total_t *) m_itemtotals->items[i];

            if (t->month == 0) // skip year total nodes
                continue;
            if (t->year > it->year)
                continue;
            if (t->year < it->year)
                break;

            assert(t->year == it->year && t->month != 0);
            array.Add(wxDataViewItem((void *) t));
        }
        return array.size();
    }

    // month total node: no children
    assert(it->month != 0);
    return 0;
}

int ExpenseNavModel::Compare(const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending) const {
    item_total_t *it1, *it2;

    assert(item1.IsOk() && item2.IsOk());

    it1 = (item_total_t *) item1.GetID();
    it2 = (item_total_t *) item2.GetID();

    if (it1->year > it2->year)
        return 1;
    if (it1->year < it2->year)
        return -1;

    if (it1->month > it2->month)
        return 1;
    if (it1->month < it2->month)
        return -1;

    return 0;
}

void ExpenseNavModel::GetValue(wxVariant &variant, const wxDataViewItem &item, unsigned int col) const {
    item_total_t *it = (item_total_t *) item.GetID();
    assert(it != NULL);

    assert(it->year != 0);

    // year total 
    if (it->month == 0) {
        if (col == 0) {
            variant = wxString::Format("%d", it->year);
            return;
        } else if (col == 1) {
            variant = wxString::Format("%'9.2f", it->amt);
            return;
        }
    }

    // month total
    if (col == 0) {
        int month = (int) wxDateTime::Jan + (it->month-1);
        variant = wxDateTime::GetMonthName((wxDateTime::Month) month, wxDateTime::Name_Full);
        return;
    } else if (col == 1) {
        variant = wxString::Format("%'9.2f", it->amt);
        return;
    }
}
bool ExpenseNavModel::SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col) {
    return false;
}
bool ExpenseNavModel::IsEnabled(const wxDataViewItem &item, unsigned int col) const {
    return false;
}

