#include "Headers/tab.h"

TabContent::TabContent(QWidget *parent) : QWidget(parent)
{

    editor = new Editor();
    highlighter = new Highlighter(editor->document());

}

TabContent::~TabContent()
{
    delete this;
}
