/****************************************************************************
 *
 * Rushes! is a video cataloger application based on QtAv, OpenCV and FFMpeg.
 * Copyright (C) 2017 Remy Ruttner
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

#include "exportjob.h"
#include "ffmpegparser.h"

#include <QDebug>
#include <QRegularExpression>

ExportJob::ExportJob(const Rush &rush, const QString &output_folder, const QString& ffmpeg_command_line)
    : m_rush(rush),
      m_output_folder(output_folder),
      m_command_line(ffmpeg_command_line)
{
    setDescription(QString("Export %1 to Prores. Output to %2").arg(rush.file_name, output_folder));
    m_export_process = 0;
    m_total_frames = rush.fps * (rush.length / 1000); // approximate but its ok
    setStatus(Job::PENDING);
}

void ExportJob::run()
{
    setStatus(Job::STARTED);
    emit progress(0, m_total_frames);
    m_export_process = FFMpegParser::transcode(m_rush.file_name, m_output_folder, m_command_line);

    connect(m_export_process, SIGNAL(readyReadStandardOutput()), this, SLOT(checkProgress()));
    connect(m_export_process, SIGNAL(readyReadStandardError()), this, SLOT(checkProgress()));

    m_export_process->waitForFinished();

    // emit progress complete
    emit progress(m_total_frames, m_total_frames);
    setStatus(Job::FINISHED);
}

void ExportJob::checkProgress()
{
    if (!m_export_process)
        return;

    // parse output and error lines wich look like this :
    // frame=   30 fps=0.0 q=-0.0 size=    7494kB time=00:00:00.68 bitrate=89930.3kbits/s speed=1.36x
    // and find frame progress
    QByteArray output = m_export_process->readAllStandardOutput();
    output.append(m_export_process->readAllStandardError());

    QRegularExpression re("frame= *([0-9]*) fps=");
    QRegularExpressionMatch match = re.match(output);

    if (match.captured(1).toInt() > 0)
        emit progress(match.captured(1).toInt(), m_total_frames);

    qDebug() << output;
}
