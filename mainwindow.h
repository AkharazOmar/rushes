#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

#include "database.h"
#include "catalogmodel.h"
#include "catalogwidget.h"

#include "gui/mediainfowidget.h"
#include "gui/playerwidget.h"
#include "gui/tagswidget.h"

#include "proc/jobsmaster.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

public slots:
    void addVideo();
    void playVideo(const QString& filepath);

    void addTags();
    void transcode(const QString& command_preset);
    void faceRecognition();

    void onSelectionChanged();
    void onShowJobsProgress();

protected:
    void readSettings();
    void writeSettings();

    void createTranscodingActions();

private:

    void createMenus();

    QList<QAction *> m_context_actions;
    QList<QAction *> m_transcode_actions;

    Database m_db;
    CatalogModel *m_catalog;
    PlayerWidget *m_player;
    CatalogWidget *m_view;
    MediaInfoWidget *m_media_info;
    TagsWidget *m_tag_widget;

    JobsMaster m_job_master;

};

#endif // MAINWINDOW_H
