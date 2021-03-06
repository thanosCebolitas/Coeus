//
//  CoeusList.h
//  Coeus
//
//  Created by - on 8/10/14.
//
//

#ifndef __Coeus__CoeusList__
#define __Coeus__CoeusList__

class CoeusListRowComponent;

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"
#include <map>
#include <unordered_map>
#include "Theme.h"

namespace std {
    template <>
    struct hash<StringArray>
    {
        std::size_t operator()(const StringArray& k) const
        {
          using std::size_t;
          using std::hash;
          using std::string;

          // Compute individual hash values for first,
          // second and third and combine them using XOR
          // and bit shifting:

            size_t h = 0;
            int c = 0;
            for(auto ind = k.begin(); ind != k.end(); ind++) {
                h ^= hash<string>()(ind->toRawUTF8()) << c;
                c = c==1 ? -1 : 1;
            }

          return h;
        }
    };
}
//==============================================================================

class CoeusListLabel    :   public Label
{
public:
    CoeusListLabel (const String& componentName,
                    const String& labelText) : Label(componentName, labelText) {
        
    }
    
    void paint(Graphics &g) override {
        const int w = getWidth();
        const int h = getHeight();
        g.setColour(Colour(0xff008080));
        g.fillRoundedRectangle(1, 1, w+20, h-1, 10);
        g.setColour(Colours::white);
        g.drawFittedText(getText(), 0, 0, w, h, Justification::centred, 2);
    }
};


//==============================================================================

class CoeusListTextEditor    :   public TextEditor
{
public:
    CoeusListTextEditor (const String& componentName) : TextEditor(componentName) {
        setOpaque(false);
    }
    
};


//==============================================================================

class CoeusHeap
{
public:
    CoeusHeap();
    void update();
    int findIndexForSum(int sum) const;
    int findSumForIndex(int index) const;
    void setNewValueAtIndex(int value, int index);
    void setNewValues(int *values, int size);
    int getValueAt(int index);
    int getSum() const;
    
private:
    HeapBlock<int> heap;
    size_t heapSize;
    int numEl;
};

class CoeusList;

class CoeusListRowComponent :   public Component,
                                public ChangeBroadcaster,
                                public ButtonListener
{
public:
    CoeusListRowComponent(CoeusList &owner_, bool addComp_ = false);
    virtual int getCoeusListHeight() = 0;
    virtual void updateFromQueryForRow(QueryEntry *qe, int row, bool dView, bool edit);
    virtual void updateFromMapForRow(QueryEntry *qe, std::map<String, String>, int row, bool dView, bool edit);
    virtual int getMinRowSize() = 0;
    virtual int getMaxRowSize() = 0;
    virtual void resizeForSummary() = 0;
    virtual void resizeForDetailed() = 0;
    void resized() override;
    virtual void shouldShowControls(bool show);
    
    virtual void updateRow() = 0;
    virtual void insertRow() = 0;
    void setEdit(bool ed) { edit = ed; }
    bool isEditable() const { return edit; }
    
    // TODO : implement for insert/add
    // getValueForFieldName

    void buttonClicked (Button *btn) override;

    int getRow() const;
    void setRow(int r);

    bool isDetailed() const { return detailedView; }
    void setDetailedView(bool s, bool force=false);
    
protected:
    // control buttons
    Image imageNormal, imageMouseOver, imageMouseDown;
    ScopedPointer<ImageButton> details, editButton, saveButton;
    
	bool detailedView, edit, showControls, addComp;
    int row;

    CoeusList &owner;
};

class CoeusList :   public Component,
                    public ScrollBar::Listener,
                    public TextEditor::Listener,
                    public ChangeListener,
                    public ChangeBroadcaster
{
public:
    CoeusList(CacheSystemClient *ccc_);
    ~CoeusList();
    
    virtual int getNumRows() = 0;
    virtual int getRowSize(int rowNumber) = 0;
    
    void paint(Graphics &g) override;
    void repaintRow(int rowNumber);
    virtual void paintRowBackground(Graphics &/*g*/, int /*rowNumber*/, int /*x*/, int /*y*/,
                                    int /*width*/, int /*height*/,
                                    bool /*rowIsSelected*/) {}
    
    virtual CoeusListRowComponent * refreshComponentForRow(int rowNumber, bool isRowSelected,
                                               CoeusListRowComponent *existingComponentToUpdate) {
        return nullptr;
    };
    
    virtual int *getRowSizes(int *pointer) { return nullptr; }
    CoeusListRowComponent *getComponentForRow(int row) const;
    virtual Array<int> getKeyField() = 0;

    void rowChangedSize(int rowNumber, int newSize);
    void update();
    void resized() override;
    void selectRow(int rowNumber);
    void addSelectRow(int rowNumber);
    
    //
    void scrollBarMoved (ScrollBar *scrollBarThatHasMoved, double newRangeStart) override;
    
    //
    virtual int getRowIndexAt(int y);
    
    //
    void setQueryEntry(QueryEntry *qe_);
    
    //
    void wasSaved(StringArray &pk);
    
    //
    void changeListenerCallback(ChangeBroadcaster *source) override;
    void mouseMove(const MouseEvent &event) override;
    void mouseExit(const MouseEvent &event) override;
    void mouseDown (const MouseEvent &event) override;
    void mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) override;
    
    //
    virtual int getMinRowSize() = 0;
    virtual int getMaxRowSize() = 0;
    
    //
    void textEditorTextChanged (TextEditor &) override;
    void textEditorReturnKeyPressed (TextEditor &te) override;

    // refresh children
    virtual void positionComponents();
    virtual void updateComponents();
    
    // database updates
    bool updateDatabaseTable(const String &table, const StringArray &pkName, CacheSystemClient *ccc);
    bool updateDatabaseTableForEntry(const String &table, const StringArray &pkName, const StringArray &pk, CacheSystemClient *ccc);

	// database inserts
	bool insertIntoDatabaseTable(const String &table, CacheSystemClient *ccc, CoeusListRowComponent *contentComp);
    
    // database remove
    bool removeSelectedDatabaseTableEntries(CacheSystemClient *ccc);
    bool removeDatabaseTableEntry(const String &table, const StringArray &pkName, const StringArray &pk, CacheSystemClient *ccc);

    bool getWantsHeader() const { return wantsHeader; }
    std::unordered_map<StringArray, std::map<String, String>> &getChanges() { return rowsToUpdate; }

    String tableName;
    StringArray fieldNames;
    Array<int> editedRows;
    CacheSystemClient *ccc;
    WeakReference<QueryEntry> qe;
    Array<StringArray> savedpks;
    std::unordered_map<StringArray, Array<int>> numTransactions;
    
protected:
    std::unordered_map<StringArray, std::map<String, String>> rowsToUpdate;
    Array<int> selectedRow;
    virtual int getYStartForRow(int index) const;
    int getViewStartHeight() const;
    ScrollBar sb;
    
    int rowUnderMouse;
    HeapBlock<int> rowSizes;
    bool wantsHeader;
    
private:
    ThemeAlt themeAlt;
    template <typename PointerType, typename ExcludedType> PointerType getFirstAncestorOf(Component * component) const;

    Array<CoeusListRowComponent *> items;
    Array<CoeusListRowComponent *> pool;
    Array<int> itemsToRows;
    CoeusHeap heap;
    int viewFirstRow;
    int viewLastRow;
};


#endif /* defined(__Coeus__CoeusList__) */
