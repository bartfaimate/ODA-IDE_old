#include "Headers/tab.h"



void Tab::closeTab(int index)
{
    removeTab(index);

}

void Tab::undo()
{
    Editor *currentEditor = dynamic_cast<Editor*>(this->currentWidget());
    currentEditor->undo();
}

void Tab::redo()
{
    Editor *currentEditor = dynamic_cast<Editor*>(this->currentWidget());
    currentEditor->redo();
}

void Tab::copy()
{
    Editor *currentEditor = dynamic_cast<Editor*>(this->currentWidget());
    currentEditor->copy();
}

void Tab::cut()
{
    Editor *currentEditor = dynamic_cast<Editor*>(this->currentWidget());
    currentEditor->cut();
}

void Tab::paste()
{
    Editor *currentEditor = dynamic_cast<Editor*>(this->currentWidget());
    currentEditor->paste();
}

