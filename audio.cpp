  #include "audio.h"

Audio::Audio(QObject *parent) : QObject(parent)
{

}


//开始录音
void Audio::startAudio(QString filename)
{
    //1.获取默认音频输入设备
    QAudioDeviceInfo device =  QAudioDeviceInfo::defaultInputDevice();

    //判断设备是否存在
    if(device.isNull()){
        QMessageBox::warning(nullptr,"warning","录音设备不存在");
    }else{
        //设置音频编码格式
        QAudioFormat m_format;
        //设置采样率
        m_format.setSampleRate(16000);
        //设置通道数
        m_format.setChannelCount(1);
        //设置位深
        m_format.setSampleSize(16);
        //设置编码格式
        m_format.setCodec("audio/pcm");

        //判断设备是否支持格式
        if(!device.isFormatSupported(m_format))
            m_format = device.nearestFormat(m_format);

        //打开文件
        myfile = new QFile;
        myfile->setFileName(filename);
        myfile->open(QIODevice::WriteOnly);

        //创建录音对象
        myaudioInput = new QAudioInput(m_format,this);

        //开始录音
        myaudioInput->start(myfile);

    }


}

//停止录音
void Audio::stopAudio()
{
    //停止录音
    myaudioInput->stop();
    //关闭文件
    myfile->close();
    delete  myfile;
    myfile = nullptr;
}
