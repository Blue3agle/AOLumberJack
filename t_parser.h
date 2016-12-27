#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QMessageBox>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QFile>
#include <QFileInfo>
#include <QFileSystemWatcher>


#include "t_logLine.h"

class t_parser : public QObject
{
    Q_OBJECT
public:
    explicit t_parser(QString fileName, QObject *parent = 0);

    void parseLine();

private:
    QFileSystemWatcher *fileWatcher;
    QFile *logFile;

signals:
    void lineParsed(t_logLine *line);
public slots:
    void processChanges(const QString fileName);

};

#endif // PARSER_H
