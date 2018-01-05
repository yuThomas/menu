#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QSharedPointer>

namespace Ui {
class MenuWidget;
}

class MenuWidget : public QWidget
{
    Q_OBJECT

    struct APPINFO;
public:
    explicit MenuWidget(QWidget *parent = 0);
    ~MenuWidget();

private slots:
    void on_condLineEdit_textChanged(const QString &arg1);

    void on_AppListWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MenuWidget *ui;

    QVector<QSharedPointer<APPINFO> >  m_appVector;
    QStringList m_xdgDataDirs;
    QStringList m_path;
    void readDesktopFileWithKey(const QString &file, const QString &key, QString &result) const;
    void findAllDesktopFile(); 
    bool isExecutable(const QString &command) const;
    void findIconWithName(QSharedPointer<APPINFO> &app) const;
    bool isUnique(const QSharedPointer<APPINFO> &app) const;
    void displaySingleApplication(const QSharedPointer<APPINFO> &app) const;
    void displayApplication() const;
};

#endif // MENUWIDGET_H
