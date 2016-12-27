#include "t_parser.h"

t_parser::t_parser(QString fileName, QObject *parent) : QObject(parent)
{
    if (QFileInfo::exists(fileName))
    {
        fileWatcher = new QFileSystemWatcher(this);
        fileWatcher->addPath(fileName);
        QObject::connect(fileWatcher, &QFileSystemWatcher::fileChanged
                         , this, t_parser::processChanges);

        this->logFile = new QFile(fileName);
        this->logFile->open(QIODevice::ReadWrite);
//        this->logFile->seek(this->logFile->size());

    } else {
        QMessageBox *warning = new QMessageBox();
        warning->setText("File does not exist: "+fileName);
        warning->exec();
    }
}

void t_parser::processChanges(const QString fileName){
    if(fileName.toLower() == logFile->fileName().toLower()){
        QString line;
        while(!logFile->atEnd())
        {
            line = logFile->readLine();
            QRegularExpression parseRegex("\\[\".+?\",\"(.+?)\",\".*?\",(\\d+)](.+)");
            QRegularExpressionMatch matches = parseRegex.match(line);

            if(matches.hasMatch())
            {
                emit lineParsed(new t_logLine(matches.captured(2).toInt(), matches.captured(1), matches.captured(3)));
            } else {
                emit lineParsed(new t_logLine(-1, "Error", "Uparsed string: "+line));
            }
    #ifdef DEBUGMESSAGES
            LogLine * logLine = new LogLine(-1, "Debug", line);
            emit lineParsed(&logLine);
    #endif
        }
    }
}
