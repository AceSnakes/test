#include "mcacceqdialog.h"
#include "ui_mcacceqdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QThread>

const char* eqchannels[]={
    "L__",
    "R__",
    "C__",
    "SL_",
    "SR_",
    "SBL",
    "SBR",
    "LH_",
    "RH_",
    "LW_",
    "RW_",
};

MCACCEQDialog::MCACCEQDialog(QWidget *parent, QSettings& settings, ReceiverInterface& Comm) :
    QDialog(parent),
    ui(new Ui::MCACCEQDialog),
    m_Settings(settings),
    m_Comm(Comm),
    m_PositionSet(false),
    m_CurrentMcacc(0),
    m_SelectedChannel(0)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());

    // restore the position of the window
    if (m_Settings.value("SaveMCACCEQWindowGeometry", false).toBool())
    {
        m_PositionSet = restoreGeometry(m_Settings.value("MCACCEQWindowGeometry").toByteArray());
    }

    ui->MCACCcomboBox->setEnabled(false);

    m_Speakers.append(ui->RadioButtonFrontLeftCh);
    m_Speakers.append(ui->RadioButtonFrontRightCh);
    m_Speakers.append(ui->RadioButtonCenterCh);
    m_Speakers.append(ui->RadioButtonSurroundLeftCh);
    m_Speakers.append(ui->RadioButtonSurroundRightCh);
    m_Speakers.append(ui->RadioButtonSurroundBackLeftCh);
    m_Speakers.append(ui->RadioButtonSurroundBackRightCh);
    m_Speakers.append(ui->RadioButtonFrontHeightLeftCh);
    m_Speakers.append(ui->RadioButtonFrontHeightRightCh);
    m_Speakers.append(ui->RadioButtonFrontWideLeftCh);
    m_Speakers.append(ui->RadioButtonFrontWideRightCh);

    m_Slider.append(ui->Slider63Hz);
    m_Slider.append(ui->Slider125Hz);
    m_Slider.append(ui->Slider250Hz);
    m_Slider.append(ui->Slider500Hz);
    m_Slider.append(ui->Slider1kHz);
    m_Slider.append(ui->Slider2kHz);
    m_Slider.append(ui->Slider4kHz);
    m_Slider.append(ui->Slider8kHz);
    m_Slider.append(ui->Slider16kHz);

    m_Labels.append(ui->Label63Hz);
    m_Labels.append(ui->Label125Hz);
    m_Labels.append(ui->Label250Hz);
    m_Labels.append(ui->Label500Hz);
    m_Labels.append(ui->Label1kHz);
    m_Labels.append(ui->Label2kHz);
    m_Labels.append(ui->Label4kHz);
    m_Labels.append(ui->Label8kHz);
    m_Labels.append(ui->Label16kHz);

    m_EQData.resize(m_Speakers.size());
    for (int i = 0; i < (int)m_EQData.size(); i++)
    {
        m_EQData[i].resize(m_Slider.size());
        m_Speakers[i]->setEnabled(false);
        connect(m_Speakers[i],SIGNAL(clicked()),this,SLOT(SpeakerClicked()));
        for (int j = 0; j < (int)m_EQData[i].size(); j++)
        {
            m_EQData[i][j] = 50;
        }
    }

    for(int i = 0; i < (int)m_Slider.size(); i++)
    {
        m_Slider[i]->setEnabled(false);
        m_Slider[i]->setValue(50);
    }

    connect(this, SIGNAL(SendCmd(QString)), &m_Comm, SLOT(SendCmd(QString)));
    connect(&m_Comm,SIGNAL(MCACC(int)),this,SLOT(MCACC(int)));
    connect(&m_Comm,SIGNAL(MCACCEQ(int, QString, int, int)),this,SLOT(MCACCEQData(int, QString, int, int)));

    for (int i = 0; i < (int)m_Slider.size(); i++)
    {
        connect(m_Slider[i],SIGNAL(sliderReleased()),this,SLOT(SliderValueChanged()));
    }
}

MCACCEQDialog::~MCACCEQDialog()
{
    delete ui;
}

void MCACCEQDialog::moveEvent(QMoveEvent* event)
{
    m_Settings.setValue("MCACCEQWindowGeometry", saveGeometry());
    QDialog::moveEvent(event);
}

void MCACCEQDialog::ShowMCACCEQDialog()
{
    if (!isVisible())
    {
        if (!m_PositionSet || !m_Settings.value("SaveMCACCEQWindowGeometry", false).toBool())
        {
            QWidget* Parent = dynamic_cast<QWidget*>(parent());
            int x = Parent->pos().x() + Parent->width() + 20;
            //int x = Parent->pos().x() - Parent->width() - 100;
            QPoint pos;
            pos.setX(x);
            pos.setY(Parent->pos().y());
            this->move(pos);
            qDebug() << "SET POSITION";
        }
        this->show();
        emit SendCmd("?MC"); // MCACC MEMORY SET

/*         if (!m_Settings.value("TunerCompatibilityMode").toBool())
         {
         }*/
    }
    else
    {
        this->hide();
    }

}

void MCACCEQDialog::MCACC(int mcacc)
{
    if (!isVisible())
        return;
    if (m_CurrentMcacc == mcacc)
        return;
    m_CurrentMcacc = mcacc;
    ui->MCACCcomboBox->setEnabled(true);
    ui->MCACCcomboBox->setCurrentIndex(mcacc - 1);

    EnableSlider(false);

    for (int i = 0; i < m_Speakers.size(); i++)
    {
        RefreshSpeakerEq(eqchannels[i]);
    }
    m_Speakers[0]->setChecked(true);
}

void MCACCEQDialog::RefreshSpeakerEq(QString speaker)
{
    for (int i = 0; i < m_Slider.size(); i++)
        emit SendCmd("?SUW00" + speaker + "0" + QString("%1").arg(i));
}

void MCACCEQDialog::EnableSlider(bool enabled)
{
    for (int i = 0; i < (int)m_Slider.size(); i++)
    {
        m_Slider[i]->setEnabled(enabled);
    }
}

QString MCACCEQDialog::GetDBString(int dB)
{
    QString str;
    double eqValue = ((double)dB - 50.0) / 2.0;

    if (eqValue == 0.0)//eqValue > -0.1 && eqValue <= 0.1)
    {
        str = "0.0";
    }
    else if (eqValue < 0.0)
        str = QString("%1").arg(eqValue, 3, 'f', 1);
    else
        str = QString("+%1").arg(eqValue, 3, 'f', 1);
   return str;
}

void MCACCEQDialog::MCACCEQData(int /*mcacc*/, QString speaker, int eqidx, int value)
{
    if (!isVisible())
        return;
    int idx = -1;
    for (int i = 0; i < m_Speakers.size(); i++)
    {
        if (speaker == eqchannels[i])
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
        return;
    m_Speakers[idx]->setEnabled(true);
    m_EQData[idx][eqidx] = value;
    if (m_Speakers[idx]->isChecked())
    {
        m_Slider[eqidx]->setValue(value);
        m_Slider[eqidx]->setEnabled(true);
        m_Labels[eqidx]->setText(GetDBString(value));
    }
}

void MCACCEQDialog::SpeakerClicked()
{
    QString id;
    QObject* sender = QObject::sender();
    id = sender->objectName();
    for (int i = 0; i < (int)m_Speakers.size(); i++)
    {
        QString tempid = m_Speakers[i]->objectName();
        if (id == tempid)
        {
            m_SelectedChannel = i;
            EnableSlider(true);
            for (int j = 0; j < (int)m_Slider.size(); j++)
            {
                m_Slider[j]->setValue(m_EQData[i][j]);
                m_Labels[j]->setText(GetDBString(m_EQData[i][j]));
            }
            break;
        }
    }
}

void MCACCEQDialog::SliderValueChanged()
{
    QString id;
    QObject* sender = QObject::sender();
    id = sender->objectName();
    for (int i = 0; i < (int)m_Slider.size(); i++)
    {
        QString tempid = m_Slider[i]->objectName();
        if (id == tempid)
        {
            m_EQData[m_SelectedChannel][i] = m_Slider[i]->value();
            m_Labels[i]->setText(GetDBString(m_EQData[m_SelectedChannel][i]));
            QString cmd = QString("00%1%2%3SUW").arg(eqchannels[m_SelectedChannel]).arg(i, 2, 10, QChar('0')).arg(m_EQData[m_SelectedChannel][i]);
            SendCmd(cmd);
        }
    }
}

void MCACCEQDialog::on_MCACCcomboBox_activated(int index)
{
    EnableSlider(false);
    for(int i = 0; i < (int)m_Slider.size(); i++)
    {
        m_Slider[i]->setValue(50);
    }
    for (int i = 0; i < (int)m_Speakers.size(); i++)
    {
        m_Speakers[i]->setEnabled(false);
    }
    SendCmd(QString("%1MC").arg(index + 1));
}

void MCACCEQDialog::on_SaveToFilePushButton_clicked()
{
    int mcacc = ui->MCACCcomboBox->currentIndex() + 1;
    QString msg = tr("Beware: only the current MCACC memory (No %1) will be saved!").arg(mcacc);
    QMessageBox::warning(this, tr("Save to file"), msg);

    QString filename = QFileDialog::getSaveFileName(this, tr("Restore from..."),
                                              QString(), tr("Settings file (*.ini)"));
    if (filename.isEmpty())
        return;
    if (!(filename.endsWith(".ini", Qt::CaseInsensitive)))
        filename += ".ini";

    QSettings settings(filename, QSettings::IniFormat);
    settings.setValue("MCACC", mcacc);
    for (int i = 0; i < (int)m_EQData.size(); i++)
    {
        for( int j = 0; j < (int)m_EQData[i].size(); j++)
            settings.setValue(QString("CHANNEL%1_EQ%2").arg(i).arg(j), m_EQData[i][j]);
    }
}

void MCACCEQDialog::on_RestoreFromFilePushButton_clicked()
{
    int mcacc = ui->MCACCcomboBox->currentIndex() + 1;
    QString msg = tr("Beware: the current MCACC memory (No %1) will be overwritten!").arg(mcacc);
    int result = QMessageBox::question(this, tr("Restore from file"), msg, tr("Continue"), tr("Cancel"));

    if (result != 0)
        return;
    QString filename = QFileDialog::getOpenFileName(this, tr("Restore from..."),
                                              QString(), tr("Settings file (*.ini)"));
    if (filename.isEmpty())
        return;
    if (!(filename.endsWith(".ini", Qt::CaseInsensitive)))
        filename += ".ini";
    QSettings settings(filename, QSettings::IniFormat);
    for (int i = 0; i < (int)m_EQData.size(); i++)
    {
        for( int j = 0; j < (int)m_EQData[i].size(); j++)
        {
            m_EQData[i][j] = settings.value(QString("CHANNEL%1_EQ%2").arg(i).arg(j), 50).toInt();
            QString cmd = QString("00%1%2%3SUW").arg(eqchannels[i]).arg(j, 2, 10, QChar('0')).arg(m_EQData[i][j]);
            SendCmd(cmd);
        }
        //QThread::usleep(200);
    }
}
