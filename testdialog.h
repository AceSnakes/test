/*
 * AVRPioRemote
 * Copyright (C) 2013  Andreas Müller, Ulrich Mensfeld
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>
#include "receiverinterface.h"
#include <QMoveEvent>
#include <QSettings>

namespace Ui {
class TestDialog;
}

class TestDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TestDialog(QWidget *parent, ReceiverInterface& Comm, QSettings& Settings);
    ~TestDialog();
    
private slots:
    void on_ClearButton_clicked();
    void on_SendButton_clicked();
    void on_SaveButton_clicked();
    void on_LogCommunicationCheckBox_clicked();
    void on_FilterLineEdit_textChanged(const QString &arg1);
    void on_checkBox_clicked();

public slots:
    void ShowTestDialog();
    void NewDataReceived(QString data);
    void LogSendCmd(QString data);

private:
    Ui::TestDialog             *ui;
    ReceiverInterface&          m_Comm;
    QSettings&                  m_Settings;
    bool                        m_PositionSet;
    bool                        m_LogEnabled;
    QStringList                 m_FilterStrings;
    bool                        m_InvertFilter;

    void AddToList(const QString& str);

    void moveEvent(QMoveEvent*event);

signals:
    void SendCmd(QString);

};


#endif // TESTDIALOG_H
