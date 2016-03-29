#ifndef DEBUG_H
#define DEBUG_H

#include <QMessageBox>

void ShowDebugMessage(const char* text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}

#endif // DEBUG_H
