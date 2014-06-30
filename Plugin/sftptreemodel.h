//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2014 The CodeLite Team
// file name            : sftptreemodel.h
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef __SFTPTreeModel_GUARD__H__
#define __SFTPTreeModel_GUARD__H__

#include <wx/variant.h>
#include <wx/dataview.h>
#include <algorithm>
#include <wx/clntdata.h>

/**
 * @brief each item in the wxDataViewCtrl is represented in the model by this class.
 * m_data - contains the data (columns values) as passed when adding an item to the wxDataViewCtrl model class 
 * m_clientData - is the user client data (owned by the model) 
 * To convert between a wxDataViewItem to a SFTPTreeModel_Item class, simply use:
 * @code
 * SFTPTreeModel_Item* itemData = reinterpret_cast<SFTPTreeModel_Item*>( item.GetID() );
 * if ( itemData ) {
 *      // you can now traverese the tree or have a direct access to the model internal data
 *      // note that you must not delete itemData as it is owned by the model and 
 * }
 * @endcode
 */
class SFTPTreeModel_Item
{
protected:
    wxVector<wxVariant>        m_data;
    SFTPTreeModel_Item*           m_parent;
    wxVector<SFTPTreeModel_Item*> m_children;
    bool                       m_isContainer;
    wxClientData*              m_clientData;

public:
    SFTPTreeModel_Item()
        : m_parent(NULL)
        , m_isContainer(false)
        , m_clientData(NULL)
    {}
    virtual ~SFTPTreeModel_Item() {
        if ( m_clientData ) {
            delete m_clientData;
            m_clientData = NULL;
        }
        m_data.clear();

        // Delete our children
        // since the deletion of a child may alter its parent m_children array
        // we use a temporary vector for the loop
        wxVector<SFTPTreeModel_Item*> tmpChildren = m_children;
        while ( !tmpChildren.empty() ) {
            delete (*tmpChildren.begin());
            tmpChildren.erase(tmpChildren.begin());
        }
        m_children.clear();

        // Remove us from the parent
        if ( m_parent ) {
            m_parent->RemoveChild(this);
        }
    }

    void SetIsContainer(bool b) {
        m_isContainer = b;
    }

    bool IsContainer() const {
        return m_isContainer;
    }

    /**
     * @brief remove a child from this node and free its memory
     * @param child
     */
    void DeleteChild(SFTPTreeModel_Item* child) {
        wxVector<SFTPTreeModel_Item*>::iterator iter = std::find(m_children.begin(), m_children.end(), child);
        if ( iter != m_children.end() ) {
            delete *iter;
            m_children.erase(iter);
        }
    }

    /**
     * @brief remove child from this node without freeing its memory
     * @param child
     */
    void RemoveChild(SFTPTreeModel_Item* child) {
        wxVector<SFTPTreeModel_Item*>::iterator iter = std::find(m_children.begin(), m_children.end(), child);
        if ( iter != m_children.end() ) {
            m_children.erase(iter);
        }
    }

    /**
     * @brief add child to this node
     */
    void AddChild(SFTPTreeModel_Item* child) {
        m_children.push_back(child);
        child->m_parent = this;
    }

    bool IsRoot() const {
        return m_parent == NULL;
    }

    // Setters / Getters
    void SetChildren(const wxVector<SFTPTreeModel_Item*>& children) {
        this->m_children = children;
    }
    void SetData(const wxVector<wxVariant>& data) {
        this->m_data = data;
    }
    void SetParent(SFTPTreeModel_Item* parent) {
        this->m_parent = parent;
    }
    const wxVector<SFTPTreeModel_Item*>& GetChildren() const {
        return m_children;
    }
    wxVector<SFTPTreeModel_Item*>& GetChildren() {
        return m_children;
    }
    const wxVector<wxVariant>& GetData() const {
        return m_data;
    }
    wxVector<wxVariant>& GetData() {
        return m_data;
    }
    SFTPTreeModel_Item* GetParent() {
        return m_parent;
    }

    void SetClientObject(wxClientData *data) {
        if ( m_clientData ) {
            delete m_clientData;
        }
        m_clientData = data;
    }

    wxClientData* GetClientObject() const {
        return m_clientData;
    }
};

//////////////////////////////////////////////
// The TreeListCtrl model
//////////////////////////////////////////////

class SFTPTreeModel : public wxDataViewModel
{
protected:
    wxVector<SFTPTreeModel_Item*> m_data;
    unsigned int m_colCount;

public:
    SFTPTreeModel();
    virtual ~SFTPTreeModel();
    
    /**
     * @brief a helper method creating a wxVariant containing both bitmap and text
     * this is useful when mostly when populating a column of type 'icontext'
     */
    static wxVariant CreateIconTextVariant(const wxString &text, const wxBitmap& bmp);
    
    void SetColCount(unsigned int colCount) {
        this->m_colCount = colCount;
    }
    void SetData(const wxVector<SFTPTreeModel_Item*> data) {
        this->m_data = data;
    }
    unsigned int GetColCount() const {
        return m_colCount;
    }
    const wxVector<SFTPTreeModel_Item*>& GetData() const {
        return m_data;
    }
    wxVector<SFTPTreeModel_Item*>& GetData() {
        return m_data;
    }

    virtual bool HasContainerColumns (const wxDataViewItem& item) const {
        return true;
    }

public:
    // Make the functions below 'virtual' so the user may override them
    virtual unsigned int GetColumnCount() const;
    virtual wxString GetColumnType(unsigned int col) const;
    virtual void GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const;
    virtual bool SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col);

protected:
    // Helpers
    virtual wxDataViewItem DoAppendItem(const wxDataViewItem& parent, const wxVector<wxVariant>& data, bool isContainer, wxClientData *clientData = NULL);
    virtual wxDataViewItem DoInsertItem(const wxDataViewItem& insertBeforeMe, const wxVector<wxVariant>& data, bool isContainer, wxClientData *clientData);
    virtual void DoChangeItemType(const wxDataViewItem& item, bool changeToContainer);
    
public:
    /**
     * @brief Append a line to the model
     * clientData will be owned by the model once added (i.e. the clientData must be allocated on the heap and it will be freed by the model)
     */
    virtual wxDataViewItem AppendItem(const wxDataViewItem& parent, const wxVector<wxVariant>& data, wxClientData *clientData = NULL);

    /**
     * @brief Append a lines to the model
     */
    virtual wxDataViewItemArray AppendItems(const wxDataViewItem& parent, const wxVector<wxVector<wxVariant> >& data);

    /**
     * @brief delete an item and all its children
     * @param parent
     */
    virtual void DeleteItem(const wxDataViewItem& item);

    /**
     * @brief delete an item
     * @param parent
     */
    virtual void DeleteItems(const wxDataViewItem& parent, const wxDataViewItemArray& items);

    /**
     * @brief update an item data + client-data
     */
    virtual void UpdateItem(const wxDataViewItem& item, const wxVector<wxVariant>& data);

    /**
     * @brief insert an item into the model before 'insertBeforeMe' item. Return the newly inserted item on success
     */
    virtual wxDataViewItem InsertItem     (const wxDataViewItem& insertBeforeMe, const wxVector<wxVariant>& data, wxClientData *clientData = NULL);

    /**
     * @brief clear the control and delete all its content
     */
    virtual void Clear();

    virtual bool IsEmpty() const;

    /**
     * @brief returns the client data associated with this item
     **/
    wxClientData* GetClientObject(const wxDataViewItem& item) const;

    /**
     * @brief set the client data for an item. The item data will be freed by the model
     */
    void SetClientObject(const wxDataViewItem& item, wxClientData *data);

    /**
     * @brief returns the item columns data (as passed to AppendItem(..) / InsertItem(...))
     */
    wxVector<wxVariant> GetItemColumnsData(const wxDataViewItem& item) const;

    /**
    * @brief return true if this node is a container (i.e. has children)
    */
    virtual bool IsContainer(const wxDataViewItem& item) const;

    /**
     * @brief return true if item has children
     */
    virtual bool HasChildren(const wxDataViewItem& item) const;

    /**
     * @brief return the item parent. Return an invalid item if this item has no parent (item.IsOk() = false)
     */
    virtual wxDataViewItem GetParent(const wxDataViewItem& item) const;

    /**
     * @brief return the item's children as an array.
     * @return children count
     */
    virtual unsigned int GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const;
};
#endif // __SFTPTreeModel_GUARD__H__
