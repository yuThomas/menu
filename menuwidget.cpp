#include "menuwidget.h"
#include "ui_menuwidget.h"
#include <QIcon>
#include <QProcessEnvironment>
#include <QDirIterator>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTextStream>
#include <QProcess>

struct MenuWidget::APPINFO
{
    QString fileName;
    QString displayName;
    QString command;
    QString comment;
    QString iconName;
      QIcon icon;
};

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWidget)
{
    ui->setupUi(this);

    m_xdgDataDirs = QProcessEnvironment::systemEnvironment().value("XDG_DATA_DIRS").split(":");
    m_path = QProcessEnvironment::systemEnvironment().value("PATH").split(":");

    findAllDesktopFile();
    displayApplication();
}

MenuWidget::~MenuWidget()
{
    delete ui;
}


void MenuWidget::findAllDesktopFile()
{
    foreach (QString path, m_xdgDataDirs)
    {
        QDirIterator iter(path, QStringList("*.desktop"), QDir::Dirs|QDir::Files, QDirIterator::Subdirectories);
        while(iter.hasNext())
        {
            iter.next();
            QFileInfo file = iter.fileInfo();

            QSharedPointer<APPINFO> app(new APPINFO);
            app->fileName = file.absoluteFilePath();
            readDesktopFileWithKey(app->fileName, "Name",  app->displayName);
            readDesktopFileWithKey(app->fileName, "Exec",  app->command);
            readDesktopFileWithKey(app->fileName, "Icon",  app->iconName);
            readDesktopFileWithKey(app->fileName, "Comment", app->comment);
            QString terminal;
            readDesktopFileWithKey(app->fileName, "Terminal", terminal);

            if(!app->displayName.isEmpty() && !app->iconName.isEmpty() && (terminal == "false")
                    && isUnique(app) && isExecutable(app->command))
            {
                findIconWithName(app);
                if(app->iconName.startsWith("/"))//if find the specified image then show it
                     m_appVector.push_back(app);
            }
        }
    }
}


void MenuWidget::readDesktopFileWithKey(const QString &file, const QString &key, QString &result) const
{
    QFile f(file);
    if(!f.open(QIODevice::ReadOnly))
    {
        result = QString();
    }

    QString line;
    QTextStream stream(&f);
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if(line.contains(QRegExp("^"+key+"=")))
        {
            line = line.split("=")[1];
            line = line.split("%")[0];
            result = line;
            return;
        }
    }
    result = QString();
}

void MenuWidget::displaySingleApplication(const  QSharedPointer<APPINFO> &app) const
{
    QListWidgetItem *item = new QListWidgetItem(app->icon, app->displayName);
    item->setSizeHint(QSize(this->width(), 30));
    int row = ui->AppListWidget->currentRow();
    ui->AppListWidget->insertItem(row, item);
}

void MenuWidget::displayApplication() const
{
   foreach(QSharedPointer<APPINFO> app, m_appVector)
   {
        displaySingleApplication(app);
   }
}

void MenuWidget::findIconWithName(QSharedPointer<APPINFO> &app) const
{
    if(app->iconName.startsWith("/") && (app->iconName.endsWith(".svg")
            || app->iconName.endsWith(".png") || app->iconName.endsWith(".xpm")))
    {
        app->icon = QIcon(app->iconName);
        return;
    }

    QStringList fileFilters;
    fileFilters << app->iconName + ".svg" << app->iconName + ".png" << app->iconName + ".xpm";
    foreach(QString path, m_xdgDataDirs)
    {
        QDirIterator iter(path, fileFilters, QDir::Dirs|QDir::Files, QDirIterator::Subdirectories);
        while(iter.hasNext())
        {
            iter.next();
            QFileInfo info = iter.fileInfo();
            app->icon = QIcon(info.absoluteFilePath());
            app->iconName = info.absoluteFilePath();
            break;
        }

    }
}

bool MenuWidget::isUnique(const QSharedPointer<APPINFO> &app) const
{
    foreach (const QSharedPointer<APPINFO> tApp, m_appVector) {
        if(tApp->displayName == app->displayName)
            return false;
    }
    return true;
}


bool MenuWidget::isExecutable(const QString &command) const
{
  foreach(QString path, m_path)
  {
      QDirIterator iter(path, QStringList(command.split(' ')[0]), QDir::Dirs|QDir::Files, QDirIterator::Subdirectories);
      while(iter.hasNext())
      {
          iter.next();
          return true;
      }
  }
  return false;
}

void MenuWidget::on_condLineEdit_textChanged(const QString &arg1)
{
    ui->AppListWidget->clear();
    foreach(const QSharedPointer<APPINFO> app, m_appVector)
    {
        if(app->displayName.contains(arg1, Qt::CaseInsensitive))
        {
            displaySingleApplication(app);
        }
    }
}

void MenuWidget::on_AppListWidget_doubleClicked(const QModelIndex &index)
{
    QString command;
    QString appname = ui->AppListWidget->item(index.row())->text();
    foreach(const QSharedPointer<APPINFO> app, m_appVector)
    {
        if(app->displayName == appname)
        {
            command = app->command;
            break;
        }
    }

    QProcess *p = new QProcess(ui->AppListWidget);
    p->start(command);
}
