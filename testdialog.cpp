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
#include "testdialog.h"
#include "ui_testdialog.h"
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>


TestDialog::TestDialog(QWidget *parent, ReceiverInterface &Comm, QSettings &Settings, QString & dev) :
    QDialog(parent),
    ui(new Ui::TestDialog),
    m_Comm(&Comm),
    device(QString("Receiver")),
    m_PlayerComm(0),
    m_Settings(Settings),
    m_PositionSet(false),
    m_LogEnabled(false),
    m_InvertFilter(false)
{
    ui->setupUi(this);

    this->setWindowTitle(device.append(" Test"));
    // restore the position of the window
    if (m_Settings.value(QString("SaveTestWindowGeometry"), false).toBool())
    {
        m_PositionSet = restoreGeometry(m_Settings.value(QString("TestWindowGeometry").append(device)).toByteArray());
    }

    m_LogEnabled = m_Settings.value(QString("StartLoggingInTestWindow").append(device), false).toBool();

    connect((m_Comm), SIGNAL(DataReceived(QString)), this,  SLOT(NewDataReceived(QString)));
    connect((this),    SIGNAL(SendCmd(QString)), m_Comm, SLOT(SendCmd(QString)));
    connect((m_Comm),  SIGNAL(CmdToBeSend(QString)), this,  SLOT(LogSendCmd(QString)));
}

TestDialog::TestDialog(QWidget *parent, PlayerInterface &Comm, QSettings &Settings, QString & dev) :
    QDialog(parent),
    device(QString("Player")),
    ui(new Ui::TestDialog),
    m_PlayerComm(&Comm),
    m_Comm(0),
    m_Settings(Settings),
    m_PositionSet(false),
    m_LogEnabled(false),
    m_InvertFilter(false)
{
    ui->setupUi(this);
    this->setWindowTitle(device.append(" Test"));
    // restore the position of the window
    if (m_Settings.value(QString("SaveTestWindowGeometry"), false).toBool())
    {
        m_PositionSet = restoreGeometry(m_Settings.value(QString("TestWindowGeometry").append(device)).toByteArray());
    }

    m_LogEnabled = m_Settings.value(QString("StartLoggingInTestWindow").append(device), false).toBool();

    connect((m_PlayerComm), SIGNAL(DataReceived(QString)), this,  SLOT(NewDataReceived(QString)));
    connect((this),    SIGNAL(SendCmd(QString)), m_PlayerComm, SLOT(SendCmd(QString)));
    connect((m_PlayerComm),  SIGNAL(CmdToBeSend(QString)), this,  SLOT(LogSendCmd(QString)));
}

TestDialog::~TestDialog()
{
    delete ui;
}


void TestDialog::moveEvent(QMoveEvent* event)
{
    m_Settings.setValue(QString("TestWindowGeometry").append(device), saveGeometry());
    QDialog::moveEvent(event);
}


void TestDialog::ShowTestDialog()
{
    if (!this->isVisible())
    {
        if (!m_PositionSet || !m_Settings.value(QString("SaveTestWindowGeometry"), false).toBool())
        {
            QWidget* Parent = dynamic_cast<QWidget*>(parent());
            int x = Parent->pos().x() - 20 - this->width();
            QPoint pos;
            pos.setX(x);
            pos.setY(Parent->pos().y());
            this->move(pos);
        }
        this->show();
    }
}


void TestDialog::on_ClearButton_clicked()
{
    //ui->lineEdit->clear();
    ui->listWidget->clear();
}


void TestDialog::NewDataReceived(QString data)
{
    if (m_LogEnabled)
    {
        // filter
        bool found = false;
        for(int i = 0; i < m_FilterStrings.count(); i++)
        {
            if (data.startsWith(m_FilterStrings[i], Qt::CaseInsensitive))
            {
                found = true;
                break;
            }
        }
        if (m_InvertFilter && found)
            AddToList("<-- " + data);
        else if (!m_InvertFilter && !found)
            AddToList("<-- " + data);
    }
}


void TestDialog::LogSendCmd(QString data)
{
    if (m_LogEnabled)
    {
        // filter
        bool found = false;
        for(int i = 0; i < m_FilterStrings.count(); i++)
        {
            if (data.startsWith(m_FilterStrings[i], Qt::CaseInsensitive))
            {
                found = true;
                break;
            }
        }
        if (m_InvertFilter && found)
            AddToList("--> " + data);
        else if (!m_InvertFilter && !found)
            AddToList("--> " + data);
    }

}


void TestDialog::AddToList(const QString& str)
{
    if (ui->listWidget->count() > 1000)
    {
        delete ui->listWidget->item(0);
    }
    ui->listWidget->addItem(str);
    if (ui->AutoScrollingCheckBox->isChecked())
    {
        ui->listWidget->scrollToBottom();
    }
}


void TestDialog::on_SendButton_clicked()
{
    QString str = ui->lineEdit->text().trimmed();
    if (str != "")
    {
        if(ui->historyComboBox->findText(str)<0) {
          ui->historyComboBox->insertItem(0,str);
          ui->historyComboBox->setCurrentIndex(0);
          if(ui->historyComboBox->count()>20) {
              ui->historyComboBox->removeItem(ui->historyComboBox->count()-1);
          }
        }
        emit SendCmd(str);
    }
}


void TestDialog::on_SaveButton_clicked()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("Save as..."),
                                              QString(), tr("Log file (*.txt)"));
    if (fn.isEmpty())
        return;
    if (!(fn.endsWith(".txt", Qt::CaseInsensitive)))
        fn += ".txt";

    QFile file(fn);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QString msg = QString("Error: Cannot write file <%1>: %2").arg(fn).arg(file.errorString());
        Logger::Log(msg);
        return;
    }
    QTextStream ts(&file);
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        ts << ui->listWidget->item(i)->text() << endl;
    }
}


void TestDialog::on_LogCommunicationCheckBox_clicked()
{
    m_LogEnabled = ui->LogCommunicationCheckBox->isChecked();
}


void TestDialog::on_FilterLineEdit_textChanged(const QString &arg1)
{
    QString str = arg1.trimmed();
    if (str == "")
    {
        m_FilterStrings.clear();
        return;
    }
    m_FilterStrings = str.split(QRegExp("\\s+"));
}


void TestDialog::on_checkBox_clicked()
{
    m_InvertFilter = ui->checkBox->isChecked();
}

void TestDialog::on_historyComboBox_activated(const QString &arg1)
{
    ui->lineEdit->setText(arg1);
    on_SendButton_clicked();
}
