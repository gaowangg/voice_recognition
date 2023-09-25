#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QMessageBox>
#include <QFile>
#include <QAudioInput>


class Audio : public QObject
{
    Q_OBJECT
public:
    explicit Audio(QObject *parent = nullptr);

    //开始录音
    void startAudio(QString filename);
    //停止录音
    void stopAudio();

private:
    QFile *myfile;
    QAudioInput *myaudioInput;

signals:

};

#endif // AUDIO_H
